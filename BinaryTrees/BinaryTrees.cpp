#include <iostream>

struct Node {
  Node* left;
  Node* right;
  Node* parent;
  Node() : left(nullptr), right(nullptr), parent(nullptr) {}
};

int depth(Node* root, Node* u) {
  if (u == nullptr) return -1;

  int d = 0;
  while (u != root) {
    u = u->parent;
    d++;
    if (u == nullptr) return -1;
  }
  return d;
}


int main()
{
  Node* rootNode = new Node(); // root
  Node* child1 = new Node();
  Node* child2 = new Node();

  rootNode->left = child1;
  child1->parent = rootNode;

  child1->right = child2;
  child2->parent = child1;

  std::cout << "Depth child1: " << depth(rootNode, child1) << '\n';
  std::cout << "Depth child2: " << depth(rootNode, child2) << '\n';

  delete rootNode;
  delete child1;
  delete child2;
}
