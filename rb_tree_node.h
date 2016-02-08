#ifndef RBTREE_NODE_H
#define RBTREE_NODE_H

#include <iostream>
#include <memory>

using namespace std;

namespace rbtree { namespace rbtreenode {

class RBTreeNode {
 public:
  typedef shared_ptr<RBTreeNode> Ptr;
  typedef shared_ptr<RBTreeNode> ConstPtr;

  RBTreeNode(
    bool is_nil,
    int key_val);
  ~RBTreeNode();

 private:
  bool is_nil_;

  unique_ptr<int> key_val_;
};

} } // namespace rbtree, rbtreenode

#endif // RBTREE_NODE_H
