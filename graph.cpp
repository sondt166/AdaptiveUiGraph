#include "graph.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "appservice/appmanagerservice.h"

#ifdef ENABLE_SERVICE
#include "utils/statisticlogger.h"
#endif

std::string dropPrefix(const std::string &in)
{
    if (in.find("/role/") == std::string::npos)
        return in;
    return in.substr(6); // /role/
}

void Graph::clearEdges(const std::string &_from)
{
    int id = getId(_from);

    if (id < 0) {
        return;
    }

    m_graph[id].edges.clear();
}

void Graph::addEdge(const std::string &_from, const Edge &_to)
{
    int fromId = getOrCreateId(_from);
    int toId = getOrCreateId(_to.next);

    if (fromId < 0 || toId < 0) {
        return;
    }

    __Edge newEdge { toId, _to.opt };

    auto &edges = m_graph[fromId].edges;

    const auto item = std::find(edges.begin(), edges.end(), newEdge);
    if (item != edges.end()) {
        // don't add duplicated link
        return;
    }

    edges.push_back(newEdge);
}

Graph::Map Graph::rawGraph() const
{
    Map result {};

    /*
    qDebug("---------");
    for (const auto &i : m_roleInfoLookupTable) {
        qDebug() << qstr(i.first);
    }
    qDebug("---------");
    */
    // for each node...
    for (int i = 0; i < (int)m_graph.size(); i++) {
        auto role = getNameFromId(i);

        if (role.empty())
            continue;

        if (m_roleInfoLookupTable.at(i).appName.empty()) {
            qWarning() << "Role info not found, maybe the app didn't register: "
                       << qstr(role);
        }

        auto &currentNode = m_graph[i];

        auto &outNode = result[role];
        auto &edgeList = outNode.edges;

        outNode.appName = m_roleInfoLookupTable.at(i).appName;
        outNode.windowName = m_roleInfoLookupTable.at(i).windowName;
        outNode.typeInfo = currentNode.typeInfo;

        // for each edge...
        for (int j = 0; j < (int)currentNode.edges.size(); j++) {
            edgeList.push_back({
                                    getNameFromId(currentNode.edges[j].next),
                                    currentNode.edges[j].opt
                                });
        }
    }
    return result;
}

void Graph::clear()
{
    m_graph.clear();
    m_idLookupTable.clear();
    m_roleInfoLookupTable.clear();
    // m_staticNodes.clear();
    m_currentUniqueId = 0;
}

bool Graph::hasPath(const std::string &_from, const std::string &_to) const
{
    // use BFS implementation to find the path

    const int fromId = getId(_from);
    const int toId = getId(_to);

    if (fromId < 0 || toId < 0) {
        // vertex not found
        return false;
    }

    std::vector<int> visited(vertexCount(), false);
    std::list<int> queue {};

    int current = fromId;

    visited[current] = true;
    queue.push_back(current);

    while (!queue.empty()) {
        current = queue.front();
        queue.pop_front();

        if (current == toId) {
            // found
            return true;
        }

        for (const auto &adjecent : m_graph[current].edges) {
            int next = adjecent.next;
            if (!visited[next]) {
                visited[next] = true;
                queue.push_back(next);
            }
        }
    }

    return false;
}

std::vector<int> Graph::relatives(const std::vector<int> &_origins) const
{
    // use BFS implementation to find the path
    std::vector<int> result {};
    result.reserve(vertexCount());
    std::vector<int> visited(vertexCount(), false);

    std::list<int> queue {};

    for (int id : _origins) {
        if (id < 0 || visited[id])
            continue; // don't push duplicated items
        visited[id] = true;
        queue.push_back(id);
    }

    std::fill(visited.begin(), visited.end(), false);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for (const auto &adjecent : m_graph[current].edges) {
            int next = adjecent.next;
            if (!visited[next]) {
                visited[next] = true;
                queue.push_back(next);
                result.push_back(next);
            }
        }
    }

    return result;
}

int Graph::vertexCount() const
{
    return m_graph.size();
}

/*
void Graph::setStaticNodeList(const std::vector<std::string> &_list)
{
    for (auto &node : m_graph) {
        node.typeInfo.data.isStatic = false;
    }

    for (const auto &item : _list) {
        const int id = getOrCreateId(item);
        if (id < 0) continue;

        m_graph[id].typeInfo.data.isStatic = true;
    }
}
*/

void Graph::dump() const
{
    std::stringstream ss {};
    for (const auto &node : rawGraph())  {
        ss << node.first << " -> \n";
        for (const auto &adj : node.second.edges)  {
            ss << "    " << adj.next << " - " << adj.opt << "\n";
        }
    }
    std::cout << ss.str() << std::endl;
}

void Graph::dumpGraphInfo() const
{
    int edgesCount = 0;

    for (const auto &node : m_graph) {
        edgesCount += node.edges.size();
    }

    qDebug("Vertices: %d, Edges: %d", vertexCount(), edgesCount);
}

QJsonObject Graph::serialize() const
{
    QJsonObject result {};
    QJsonObject idLookupTable {};
    QJsonArray infoLookupTable {};
    QJsonArray graph {};

    // copy lookup tables
    for (const auto &iter : m_idLookupTable) {
        idLookupTable.insert(qstr(iter.first), iter.second);
    }

    for (const auto &iter : m_roleInfoLookupTable) {
        QJsonObject t;
        t["app"] =qstr(iter.appName);
        t["win"] =qstr(iter.windowName);
        infoLookupTable.append(t);
    }

    // copy internal graph
    for (const auto &in : m_graph) {
        QJsonObject nodeInfo {};
        QJsonArray edgeList {};

        for (const auto &out : in.edges) {
            QJsonObject edge {};
            edge["next"] = out.next;
            edge["opt"] = out.opt;
            edgeList.append(edge);
        }

        nodeInfo["type"] = in.typeInfo.raw;
        nodeInfo["edges"] = edgeList;

        graph.append(nodeInfo);
    }

    result.insert("idLookupTable", idLookupTable);
    result.insert("infoLookupTable", infoLookupTable);
    result.insert("internalGraph", graph);
    result.insert("currentUniqueId", m_currentUniqueId);

    return result;
}

Graph Graph::deserialize(const QJsonObject &o)
{
    Graph g {};

    g.clear();

    QJsonObject idLookupTable = o["idLookupTable"].toObject();
    QJsonArray infoLookupTable = o["infoLookupTable"].toArray();
    QJsonArray graph = o["internalGraph"].toArray();
    g.m_currentUniqueId = o["currentUniqueId"].toInt();

    // copy lookup tables
    for (const auto &k : idLookupTable.keys()) {
        g.m_idLookupTable[k.toStdString()] = idLookupTable[k].toInt();
    }
    for (const auto &iter : qAsConst(infoLookupTable)) {
        const auto t = iter.toObject();
        g.m_roleInfoLookupTable.push_back(__RoleStaticInfo {
                                              t["app"].toString().toStdString(),
                                              t["win"].toString().toStdString(),
                                          });
    }
    // copy internal graph
    for (const auto &in: qAsConst(graph)) {
        g.m_graph.push_back({});
        auto &out = g.m_graph[g.m_graph.size() - 1];

        auto _in = in.toObject();

        out.typeInfo.raw = _in["type"].toInt();

        for (const auto &edge : _in["edges"].toArray()) {
            auto _e = edge.toObject();
            out.edges.push_back(__Edge {
                                     _e["next"].toInt(),
                                     (E_SHOW_OPT)_e["opt"].toInt()
                                 });
        }
    }

    return g;
}

int Graph::getId(const std::string &_name) const
{
    int id = -1;

    if (_name.empty()) {
        qCritical() << "Bad name:" << qstr(_name);
        return id;
    }

    const auto iter = m_idLookupTable.find(_name);

    if (iter != m_idLookupTable.cend()) {
        // already have the record? return it
        id = iter->second;
    }

    return id;
}

int Graph::getOrCreateId(const std::string &_name)
{
    if (_name.empty()) {
        qWarning("Name is empty!");
        return -1;
    }

    int id = getId(_name);

    if (id < 0) {
        // no record? now create one
        id = m_currentUniqueId;
        m_currentUniqueId++;

        m_idLookupTable.insert({_name, id});
        // Create a node so that the graph is safe to access with _id
        m_graph.resize(m_currentUniqueId, {});
        m_roleInfoLookupTable.resize(m_graph.size(), {});
    }

    return id;
}

std::string Graph::getNameFromId(int _id) const
{
    const auto iter = std::find_if(m_idLookupTable.cbegin(), m_idLookupTable.cend(),
                                   [_id](const std::pair<std::string, int> i) {
        return i.second == _id;
    });

    if (iter == m_idLookupTable.cend()) {
        qCritical() << "ID " << _id << " is not found";
        return std::string();
    }

    return iter->first; // key
}

std::string Graph::appName(const std::string &_role) const
{
    int id = getId(_role);
    if (id == -1) {
        return std::string();
    }
    return m_roleInfoLookupTable[id].appName;
}

std::string Graph::windowName(const std::string &_role) const
{
    int id = getId(_role);
    if (id == -1) {
        return std::string();
    }
    return m_roleInfoLookupTable[id].windowName;
}

void Graph::updateNode(int _id, NodeFlags _type, bool _value)
{
    auto &data  = m_graph[_id].typeInfo.data;
    // raw ^= (-_value ^ raw) & (1UL << _type);
    switch (_type) {
    case NodeFlags::IsStatic:             data.isStatic             = _value; break;
    case NodeFlags::IsMostFrequentlyUsed: data.isMostFrequentlyUsed = _value; break;
    case NodeFlags::IsPotential:          data.isPotential          = _value; break;
    case NodeFlags::IsActive:             data.isActive             = _value; break;
    case NodeFlags::IsForeground:         data.isForeground         = _value; break;
    case NodeFlags::IsCreated:            data.isCreated            = _value; break;
    default: break;
    }
}

bool Graph::getNodeFlag(int _id, NodeFlags _type) const
{
    if (_id < 0) return false;

    auto data  = m_graph[_id].typeInfo.data;
    bool value = false;
    switch (_type) {
    case NodeFlags::IsStatic:             value = data.isStatic             ; break;
    case NodeFlags::IsMostFrequentlyUsed: value = data.isMostFrequentlyUsed ; break;
    case NodeFlags::IsPotential:          value = data.isPotential          ; break;
    case NodeFlags::IsActive:             value = data.isActive             ; break;
    case NodeFlags::IsForeground:         value = data.isForeground         ; break;
    case NodeFlags::IsCreated:            value = data.isCreated            ; break;
    default: break;
    }
    return value;
}

void Graph::dumpMermaid() const
{
    std::stringstream ss {};

    ss << "---\r\nhide:\r\n  - navigation\r\n  - toc\r\n---\r\n";
    ss << "# Graph\r\n";
    ss << "```mermaid\r\nflowchart LR\r\n";

    /*
    for (const auto &node : rawGraph())  {
        for (const auto &adj : node.second.edges)  {
            ss << "    " <<  dropPrefix(node.first) << " -->|"
               << adj.opt << "| " << dropPrefix(adj.next) << "\r\n";
        }
    }
    */
    const std::string TAB = "    ";
    const std::string NL = "\r\n";

    const char * const nodeFillColor[] = {
        " fill:#ddd,color:black", // not created
        " fill:#385ff0,color:white"  // created
    };
    const char * const nodeStrokeColor[] = {
        ",stroke:black,stroke-width:2px",  // Inactive
        ",stroke:gold,stroke-width:5px",  // ActiveInStack
        ",stroke:#00cc99,stroke-width:3px",  // InactivePotential
        ",stroke:deepskyblue,stroke-width:7px"   // Foreground
    };
    const char * const nodeStrokeStyle[] = {
        "",
        ",stroke-dasharray:5 5" // MostFrequentlyUsed
    };

    // list participants
    for (size_t i = 0; i < m_graph.size(); ++i) {
        const auto &node = m_graph[i];
        const auto nodeInfo = node.typeInfo.data;

        if (nodeInfo.isStatic) {
            ss << TAB << i << "((" << dropPrefix(getNameFromId(i)) << "))" << NL;
        } else {
            ss << TAB << i << "([" << dropPrefix(getNameFromId(i)) << "])" << NL;
        }
        ss << TAB << "style " << i << nodeFillColor[(int)node.typeInfo.data.isCreated];

        const char * strokeColor = nodeStrokeColor[0]; // Inactive

        // order: most important last
        if (!nodeInfo.isActive) strokeColor = nodeStrokeColor[0];   // Inactive
        if (nodeInfo.isPotential) strokeColor = nodeStrokeColor[2]; // Potential
        if (nodeInfo.isActive) strokeColor = nodeStrokeColor[1];    // ActiveInStack
        if (nodeInfo.isForeground) strokeColor = nodeStrokeColor[3];// Foreground

        ss << strokeColor;
        ss << nodeStrokeStyle[nodeInfo.isMostFrequentlyUsed];

        ss << NL;
    }

    ss << NL;

    // list edges
    const std::string arrowType[] = {
        "==>|0|", // E_SHOW_OPT_ADD = 0, thick line
        "-->|1|", // E_SHOW_OPT_ADD_OVERLAY, slim line
        "-.->|2|", // E_SHOW_OPT_CLEAR_AND_ADD, dotted line
        "-..->|3|"  // E_SHOW_OPT_CLEAR_DUPLICATE_AND_ADD, thick dotted line
    };
    for (size_t i = 0; i < m_graph.size(); ++i) {
        for (const auto j : m_graph[i].edges) {
            ss << TAB << i << arrowType[j.opt] << j.next << NL;
        }
    }

    ss << "```";
    // std::cout << ss.str() << std::endl;

#ifdef ENABLE_SERVICE
    StatisticLogger::instance()->updateGraph(ss.str());
#endif
}
