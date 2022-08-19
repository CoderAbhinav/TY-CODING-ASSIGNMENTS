#include <string>
#include <unordered_map>

class NetworkNode
{
private:
    std::string mac_address = "";
    std::unordered_map<std::string, NetworkNode*> childrenMap;

public:
    NetworkNode(std::string);
    NetworkNode(std::string, std::vector<NetworkNode*>);

    void connectChild(NetworkNode&);
    
};

void NetworkNode::connectChild(NetworkNode& node) {
    childrenMap[node.mac_address] = &node;
}