#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <vector>

#include "WindowNameDef.h"
#include "AppMsgDef.h"


/*
 * This class represents a directed graph using adjacency list representation.
 *
 * The underlying graph use integer ID as indexer, and will be exported to
 * string represented one to HMI (internal indexer can't be understood by HMI app)
 */
class AppManagerService;

class Graph
{
public:
    /* === SECTION Exported data types === */
    enum NodeFlags {
        IsStatic             , // = 0x01, // roles that won't be destroyed, like Home, Camera,...
        IsMostFrequentlyUsed , // = 0x02, // not implemented
        IsPotential          , // = 0x04, // related roles to app stack
        IsActive             , // = 0x08, // roles that are currently in app stack
        IsForeground         , // = 0x10, // current foreground
        IsCreated              // = 0x20  // window created
    };

    union NodeInfo {
        uint8_t raw;
        struct {
            bool isStatic : 1;
            bool isActive : 1;
            bool isPotential : 1;
            bool isMostFrequentlyUsed : 1;
            bool isForeground : 1;
            bool isCreated : 1;
        } data;
    };

    struct Edge;
    struct Node {
        std::string         appName;
        std::string         windowName;
        NodeInfo            typeInfo;
        std::vector<Edge>   edges;
    };
    struct Edge {
        std::string next;
        E_SHOW_OPT  opt;
    };
    using Map = std::map<std::string, Node>;
    //                   ^role        ^node info
    /* === SECTION exported data types === */

    /**
     * @brief Get the same map but with ID replaced by string
     */
    Map rawGraph() const;

    void clear();
    void clearEdges(const std::string &_from);
    /**
     * @brief add edge
     * @param _from (role) source vertex
     * @param _to (role) target vertex, with the show option
     */
    void addEdge(const std::string &_from, const Graph::Edge &_to);
    /**
     * @brief Check if there is a path from _from to _to
     * @param _from Source node
     * @param _to Target node
     * @return true if the path exists
     */
    bool hasPath(const std::string &_from, const std::string &_to) const;
    /**
     * @brief Get a list of related nodes
     */
    std::vector<int> relatives(const std::vector<int> &_origins) const;
    int vertexCount() const;

    // void setStaticNodeList(const std::vector<std::string> &_list);
    bool isStaticNode(int _id);

    /**
     * @brief Create a markdown file in mermaid format
     * This file will be used to generate graph by mkdocs
     */
    void dumpMermaid() const;
    void dump() const;
    void dumpGraphInfo() const;

    /**
     * @brief Helper functions to send data over IPC
     * @return A json object contains all private properties
     */
    QJsonObject serialize() const;
    /**
     * @brief Helper functions to send data over IPC
     * @return A graph with all private properties copied from the json
     */
    static Graph deserialize(const QJsonObject &o);

private:
    struct __Edge;
    struct __Node {
        NodeInfo              typeInfo;
        std::vector<__Edge>   edges;
    };
    struct __Edge {
        int         next;
        E_SHOW_OPT  opt;

        bool operator==(const __Edge &_rhs) const {
            return next == _rhs.next && opt == _rhs.opt;
        }
    };

    /**
     * @brief Get integer ID from ID table
     */
    int getId(const std::string &_name) const;
    /**
     * @brief Get integer ID from ID table
     * @param If _name is new, add it to the list
     */
    int getOrCreateId(const std::string &_name);
    /**
     * @brief Get role string from ID table
     */
    std::string getNameFromId(int _id) const;

private:
    // used for internal indexing
    std::map<std::string, int> m_idLookupTable {};
    // used to create unique ID
    int m_currentUniqueId {0};
    // graph using integer ID
    std::vector<__Node> m_graph {};
    // std::vector<int> m_staticNodes {};

    /* === SECTION used for Demo only ===*/
    friend class AppManagerService;
    struct __RoleStaticInfo {
        std::string appName;
        std::string windowName;
    };
    std::vector<__RoleStaticInfo> m_roleInfoLookupTable {};

    std::string appName(const std::string &_role) const;
    std::string windowName(const std::string &_role) const;
    void updateNode(int _id, NodeFlags _type, bool _value);
    bool getNodeFlag(int _id, NodeFlags _type) const;
    /* === ENDSECTION used for Demo only ===*/
};

#endif // GRAPH_H
