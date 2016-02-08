#ifndef RBTREE_H
#define RBTREE_H

#include "rb_tree_node.h"

namespace rbtree {

typedef struct RBTreeNodeInfo {
  int key;
  int index;
} RBTreeNodeInfo;

class RBTree {
 public:
  typedef shared_ptr<RBTree> Ptr;
  typedef shared_ptr<RBTree> ConstPtr;

  RBTree();
  ~RBTree();

  void Insert(const RBTreeNodeInfo& node_info);

  bool Lookup(int key_val, rbtreenode::RBTreeNode **node_ptr);

  void Print();

 private:
  unique_ptr<rbtreenode::RBTreeNode> root_;
};

} // namespace rbtree

#endif // RBTREE_H
