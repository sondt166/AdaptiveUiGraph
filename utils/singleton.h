#ifndef SINGLETON_H
#define SINGLETON_H

#define MAKE_SINGLETON(classname) \
private: \
    classname() {} \
    classname(const classname &) = delete; \
public: \
    static classname *instance() { \
        static classname *_instance {}; \
        if (!_instance) { \
            _instance = new classname(); \
        } \
        return _instance; \
    }

#endif // SINGLETON_H
