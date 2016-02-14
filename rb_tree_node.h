#ifndef RBTREE_NODE_H
#define RBTREE_NODE_H

#include <iostream>
#include <memory>

namespace rbtree { namespace rbtreenode {

typedef struct RBTreeNodeInfo {
  explicit RBTreeNodeInfo(int in_key, int in_index) {
    key = in_key;
    index = in_index;
  }

  int key;
  int index;
} RBTreeNodeInfo;

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
    int height,
    RBTreeNode *parent = NULL);

  ~RBTreeNode();

  RBTreeNode *AttachChild(const RBTreeNodeInfo& child_info);

  void RightRotate();
  void LeftRotate();

  void IncrementHeight();
  void DecrementHeight();

  int VerifySubtree(int parent_height);

  void SetColor(Color color);
  void SetParent(RBTreeNode *parent);
  void SetLeftChild(const Ptr& left_child);
  void SetRightChild(const Ptr& right_child);

  string ToString() const;

  RBTreeNode *OtherChild(const RBTreeNode *child);

  bool IsNIL() const { return is_nil_; }
  int key_val() const { return key_val_; }
  Color color() const { return color_; }
  int height() const { return height_; }
  RBTreeNode *parent() const { return parent_; }
  Ptr left_child() const { return left_child_; }
  Ptr right_child() const { return right_child_; }
  RBTreeNode *raw_left_child() const { return left_child_.get(); }
  RBTreeNode *raw_right_child() const { return right_child_.get(); }

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

  RBTreeNode *parent_;

  Ptr left_child_;

  Ptr right_child_;
};

} } // namespace rbtree, rbtreenode

#endif // RBTREE_NODE_H
