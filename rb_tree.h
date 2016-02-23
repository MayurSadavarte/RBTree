#ifndef RBTREE_H
#define RBTREE_H

#include "rb_tree_node.h"

namespace rbtree {

using namespace std;

class RBTree {
 public:
  typedef shared_ptr<RBTree> Ptr;
  typedef shared_ptr<const RBTree> ConstPtr;

  RBTree();
  ~RBTree();

  // Construct and insert 'node_info' in the RBTree.
  void Insert(const rbtreenode::RBTreeNodeInfo& node_info);

  // Search a node with 'key_val' and set it's pointer in '*node_ptr'.
  // If the node with 'key_val' doesn't exist in the RBTree, return its
  // parent's raw pointer instead.
  bool Lookup(int key_val, rbtreenode::RBTreeNode **node_ptr);

  // Delete a node with 'key_val'.
  // Returns 'true' if the RBTree has a node with 'key_val' in the first place.
  bool Delete(int key_val);

  // Print the RBTree breadthwise.
  void Print();

  // Verify the RBTree correctness, especially following two rules:
  // 1. Parent of a RED node has to be BLACK.
  // 2. BLACK height of any leaf node is same.
  void VerifyIntegrity();

 private:
  // RBTree rules are broken during insertion algorithm. Reinstate the
  // correctness by a series of color changes and tree rotations.
  void ReadjustTree(rbtreenode::RBTreeNode *node);
};

} // namespace rbtree

#endif // RBTREE_H
