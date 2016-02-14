#ifndef RBTREE_ROOT_H
#define RBTREE_ROOT_H

#include <memory>

namespace rbtree {
  using namespace std;

  namespace rbtreenode {
    class RBTreeNode;
  }

  extern shared_ptr<rbtreenode::RBTreeNode> root_;
} // namespace rbtree

#endif // RBTREE_ROOT_H
