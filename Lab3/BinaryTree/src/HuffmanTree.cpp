#include "../include/HuffmanTree.h"

// 构造函数
HuffmanTreeNode::HuffmanTreeNode(char ch, int freq) : character(ch), frequency(freq) {
    left = right = nullptr;
}

// 重写 getValue 方法，返回字符
string HuffmanTreeNode::getValue() {
    return string(1, character);  // 返回字符
}

// 获取节点频率
int HuffmanTreeNode::getFrequency() const {
    return frequency;
}

// 构建哈夫曼树
HuffmanTreeNode* HuffmanTreeNode::buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    // 创建最小堆
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, freq_cmp> minHeap;

    // 将所有字符和频率加入堆中
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanTreeNode(pair.first, pair.second));
    }

    // 合并最小的两个节点，直到堆中只剩下一个节点
    while (minHeap.size() > 1) {
        HuffmanTreeNode* left = minHeap.top();
        minHeap.pop();
        HuffmanTreeNode* right = minHeap.top();
        minHeap.pop();
        // 创建新的父节点，频率是两个子节点的频率之和
        HuffmanTreeNode* parent = new HuffmanTreeNode('t',left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    return minHeap.top();
}

// 打印哈夫曼树的编码（先序遍历）
void HuffmanTreeNode::printHuffmanCodes(HuffmanTreeNode* root, string code) {
    if (!root) {
        return;
    }

    if (!root->left && !root->right) {
        cout << root->character << ": " << code << endl;
    }

    if (root->left) {
        printHuffmanCodes((HuffmanTreeNode*)root->left, code + "0");
    }

    if (root->right) {
        printHuffmanCodes((HuffmanTreeNode*)root->right, code + "1");
    }
}
