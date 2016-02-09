#ifndef RBTREE_NODE_H
#define RBTREE_NODE_H

#include <iostream>
#include <memory>

namespace rbtree { namespace rbtreenode {

using namespace std;

class RBTreeNode : public enable_shared_from_this<RBTreeNode> {
 public:
  typedef shared_ptr<RBTreeNode> Ptr;
  typedef shared_ptr<const RBTreeNode> ConstPtr;

  enum class Color {
    RED,
    BLACK,
  };

  RBTreeNode(
    bool is_nil,
    int key_val,
    int index,
    int height);

  ~RBTreeNode();

  void SetColor(Color color);
  void SetParent(const Ptr& parent);
  void SetLeftChild(const Ptr& left_child);
  void SetRightChild(const Ptr& right_child);

  bool IsNIL() const { return is_nil_; }

  string ToString() const;

  int height() const { return height_; }
  Ptr parent() const { return parent_; }
  Ptr left_child() const { return left_child_; }
  Ptr right_child() const { return right_child_; }

  Ptr getptr() {
    return enable_shared_from_this<RBTreeNode>::shared_from_this();
  }

 private:
  bool is_nil_;

  int key_val_;

  int index_;

  Color color_;

  int height_;

  int black_height_;

  Ptr parent_;

  Ptr left_child_;

  Ptr right_child_;
};

} } // namespace rbtree, rbtreenode

#endif // RBTREE_NODE_H
