#pragma once

#include <map>

struct ConfigNode {
    ~ConfigNode();
    void Cleanup();

    bool HasKey(const char* key);
    const ConfigNode& GetChild(const char* key);
    const ConfigNode& GetChildOrDefault(const char* key, const ConfigNode& defaultNode);
    const ConfigNode& GetArrayByIndex(const char* key, int index);

    enum Type { Null = 0, Bool = 1, Int = 2, String = 4, Array = 5, Object = 6 };

    struct Array {
        ConfigNode* data;  // pointer to the first element
        ConfigNode* end;   // pointer to one past the last element
    };

    Type type;
    union {
        bool boolValue;
        int intValue;
        const char* stringValue;
        struct Array* arrayValue;
        std::map<std::string, ConfigNode>* objectValue;
    } data;
};

class Config {
public:
};
