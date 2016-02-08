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

  enum class Color {
    RED,
    BLACK,
  };

  RBTreeNode(
    bool is_nil,
    int height = -1,
    int black_height = -1,
    int key_val = -1,
    int index = -1);

  ~RBTreeNode();

  bool IsNIL() const { return is_nil_; }

  string PrintString();

 private:
  bool is_nil_;

  int key_val_;

  int index_;

  Color color_;

  int height_;

  int black_height_;
};

} } // namespace rbtree, rbtreenode

#endif // RBTREE_NODE_H
