#ifndef RBTREE_H
#define RBTREE_H

#include "rb_tree_node.h"

namespace rbtree {

class RBTree {
 public:
  typedef shared_ptr<RBTree> Ptr;
  typedef shared_ptr<RBTree> ConstPtr;

  RBTree();
  ~RBTree();

 private:
  unique_ptr<rbtreenode::RBTreeNode> root_;
};

} // namespace rbtree

#endif // RBTREE_H
