#include "../include/BinaryTree.h"
#include <iostream>
#include <queue>

using namespace std;

// 构造函数的实现，初始化左右孩子为 nullptr
BinaryTreeNode::BinaryTreeNode() : left(nullptr), right(nullptr) {}

// 先序遍历的实现：访问根节点，然后先序遍历左子树，再先序遍历右子树
void BinaryTreeNode::PreOrderTraverse(BinaryTreeNode* root) {
    if(!root) return;
    cout<<root->name<<endl;
    PreOrderTraverse(root->left);
    PreOrderTraverse(root->right);
}

// 中序遍历的实现：先中序遍历左子树，再访问根节点，最后中序遍历右子树
void BinaryTreeNode::InOrderTraverse(BinaryTreeNode* root) {
    if(!root) return;
    InOrderTraverse(root->left);
    cout<<root->name<<endl;
    InOrderTraverse(root->right);
}

// 后序遍历的实现：先后序遍历左子树，再后序遍历右子树，最后访问根节点
void BinaryTreeNode::PostOrderTraverse(BinaryTreeNode* root) {
    if(!root) return;
    auto left = root->left;
    auto right = root->right;
    PostOrderTraverse(left);
    PostOrderTraverse(right);
    cout<<root->name<<endl;
}

// 层次遍历的实现：使用队列，按层级从上到下、从左到右遍历树
void BinaryTreeNode::LevelOrderTraverse(BinaryTreeNode* root) {
    queue<BinaryTreeNode*> level;
    level.push(root);
    while(!level.empty()){
        cout<<root->name<<endl;
        auto node = level.front();
        level.pop();
        if(node->left) level.push(node->left);
        if(node->right) level.push(node->right);
    }
}

// 辅助函数：通过中序和后序遍历构建树（递归实现）
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPostorderHelper(const std::vector<std::string>& inorder, int inStart, int inEnd,
                                                                    const std::vector<std::string>& postorder, int postStart, int postEnd,
                                                                    std::unordered_map<std::string, int>& inorderMap) {
    if(inStart>inEnd||postStart>postEnd){
        return nullptr;
    }
    BinaryTreeNode* root = new BinaryTreeNode;
    root->name = postorder[postEnd];
    int root_index = inorderMap[root->name];
    int leftsize = root_index-inStart;
    root->left = buildTreeFromInorderPostorderHelper(inorder,inStart,root_index-1,postorder,postStart,postStart+leftsize-1,inorderMap);
    root->right = buildTreeFromInorderPostorderHelper(inorder,root_index+1,inEnd,postorder,postStart+leftsize,postEnd-1,inorderMap);
    return root;

}

// 构建树的函数，调用辅助函数来构建二叉树
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPostorder(const std::vector<std::string>& inorder, const std::vector<std::string>& postorder) {
    std::unordered_map<std::string, int> inorderMap;
    // 构建中序遍历值到索引的映射，方便快速查找
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }

    // 调用辅助函数开始构建树
    return buildTreeFromInorderPostorderHelper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1, inorderMap);
}

// 辅助函数：通过中序和前序遍历构建树（递归实现）
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPreorderHelper(const vector<string>& inorder, int inStart, int inEnd, 
                                                                     const vector<string>& preorder, int preStart, int preEnd, 
                                                                     unordered_map<string, int>& inorderMap) {
    // 递归终止条件
    if(inStart>inEnd||preStart>preEnd) return nullptr;
    // 前序遍历的第一个元素是根节点
    BinaryTreeNode* root = new BinaryTreeNode;
    // BinaryTreeNode rt = BinaryTreeNode();
    // BinaryTreeNode* root = &rt;
    root->name = preorder[preStart];
    int root_index = inorderMap[root->name];
    int leftsize = root_index-inStart;
    root->left = buildTreeFromInorderPreorderHelper(inorder,inStart,root_index-1,preorder,preStart+1,preStart+leftsize,inorderMap);
    root->right = buildTreeFromInorderPreorderHelper(inorder,root_index+1,inEnd,preorder,preStart+leftsize+1,preEnd,inorderMap); 
    return root;
}

// 构建树的函数，调用辅助函数来构建二叉树
BinaryTreeNode* BinaryTreeNode::buildTreeFromInorderPreorder(const vector<string>& inorder, const vector<string>& preorder) {
    unordered_map<string, int> inorderMap;
    // 构建中序遍历值到索引的映射
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }

    // 调用辅助函数开始构建树
    return buildTreeFromInorderPreorderHelper(inorder, 0, inorder.size() - 1, preorder, 0, preorder.size() - 1, inorderMap);
}

// getValue 虚函数的实现，返回当前节点的名字
string BinaryTreeNode::getValue() {
    return this->name;
}
