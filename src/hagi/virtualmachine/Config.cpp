#include "hagi/virtualmachine/Config.h"

#include <string>

const ConfigNode defaultConfigNode = {ConfigNode::Null, {0}};

// NON_MATCHING
const ConfigNode& ConfigNode::GetChild(const char* key) {
    if (type != Object)
        return defaultConfigNode;

    const std::map<std::string, ConfigNode>* map = this->data.objectValue;
    std::string tmp = key;

    auto it = map->find(tmp);
    if (it != map->end())
        return it->second;

    return defaultConfigNode;
}

// NON_MATCHING
const ConfigNode& ConfigNode::GetArrayByIndex(const char* key, int index) {
    if (type != Array)
        return defaultConfigNode;

    auto it = data.arrayValue;
    const ConfigNode& element = (*it).data[index];

    if (index < (it->end - it->data))
        return element;

    return defaultConfigNode;
}
