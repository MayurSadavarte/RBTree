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

  void Insert(const rbtreenode::RBTreeNodeInfo& node_info);

  bool Lookup(int key_val, rbtreenode::RBTreeNode **node_ptr);

  void Print();

 private:
  shared_ptr<rbtreenode::RBTreeNode> root_;
};

} // namespace rbtree

#endif // RBTREE_H
