#include <iostream>
#include <string>
#include <unordered_map>
#include "../include/BinaryTree.h"
#include "../include/ExpressionBinaryTree.h"
#include "../include/HuffmanTree.h"

using namespace std;

void testBinaryTreeTraversal() {
    // 测试从中序和前序构建二叉树
    vector<string> inorder = {"H", "D", "R", "N", "S", "I", "O", "B", "J", "E", "K", "A", "F", "C", "T", "P", "U", "L", "Q", "G","M"}
;
    vector<string> preorder = {"A", "B", "D", "H", "I", "N", "R", "S", "O", "E", "J", "K", "C", "F", "G", "L", "P", "T", "U", "Q", "M"}
;
    BinaryTreeNode* treeFromPreIn = BinaryTreeNode::buildTreeFromInorderPreorder(inorder, preorder);

    cout << "\nBuilt Tree from Inorder and Preorder:" << endl;
    cout << "PostOrder Traversal: "<<endl;
    treeFromPreIn->PostOrderTraverse(treeFromPreIn);
    cout << endl;

    // 测试从中序和后序构建二叉树
    vector<string> postorder = {"H", "R", "S", "N", "O", "I", "D", "J", "K", "E", "B", "F", "T", "U", "P", "Q", "L", "M", "G", "C", "A"}
;
    BinaryTreeNode* treeFromInPost = BinaryTreeNode::buildTreeFromInorderPostorder(inorder, postorder);

    cout << "\nBuilt Tree from Inorder and Postorder:" << endl;
    cout << "PreOrder Traversal: "<<endl;
    treeFromInPost->PreOrderTraverse(treeFromInPost);
    cout << endl;
}

void testExpressionBinaryTree() {
    // 创建后缀表达式并构建表达式二叉树
    string postfix = "45+32*+84/-";
    ExpressionBinaryTreeNode* expTreePostfix = ExpressionBinaryTreeNode::buildFromPostfix(postfix);
    cout << "Expression Tree from Postfix 45+32*+84/-:" << endl;
    expTreePostfix->InOrderTraverse(expTreePostfix);
    cout << " = " << expTreePostfix->evaluate() << endl;

    // 创建前缀表达式并构建表达式二叉树
    string prefix = "+*+52-63/24";
    ExpressionBinaryTreeNode* expTreePrefix = ExpressionBinaryTreeNode::buildFromPrefix(prefix);
    cout << "Expression Tree from Prefix +*+52-63/24:" << endl;
    expTreePrefix->InOrderTraverse(expTreePrefix);
    cout << " = " << expTreePrefix->evaluate() << endl;

    // 创建中缀表达式并构建表达式二叉树
    string infix = "2*3+5*4";
    ExpressionBinaryTreeNode* expTreeInfix = ExpressionBinaryTreeNode::buildFromInfix(infix);
    cout << "Expression Tree from Infix (2*3+5*4):" << endl;
    expTreeInfix->InOrderTraverse(expTreeInfix);
    cout << " = " << expTreeInfix->evaluate() << endl;
}

void testHuffmanTree() {
    // 字符和频率的映射
    unordered_map<char, int> freqMap = {{'a', 6}, {'b', 4}, {'c', 7}, {'d', 11}, {'e', 8}, {'f', 13}, {'g', 3}, {'h', 17}, {'i', 12}, {'j', 4}, {'k', 15}
};
    
    // 构建哈夫曼树
    HuffmanTreeNode huffmanTree;
    HuffmanTreeNode* root = huffmanTree.buildHuffmanTree(freqMap);
    
    // 打印哈夫曼编码
    cout << "Huffman Codes:" << endl;
    huffmanTree.printHuffmanCodes(root);
}

int main() {
    cout << "Testing Binary Tree Traversal:" << endl;
    testBinaryTreeTraversal();
    cout << endl;

    cout << "Testing Expression Binary Tree:" << endl;
    testExpressionBinaryTree();
    cout << endl;

    cout << "Testing Huffman Tree:" << endl;
    testHuffmanTree();
    cout << endl;

    return 0;
}
