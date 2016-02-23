#ifndef RBTREE_NODE_H
#define RBTREE_NODE_H

#include <iostream>
#include <memory>

namespace rbtree { namespace rbtreenode {

// Data structure which encapsulates '[key, data]' kept inside single node of
// RBTree.
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

  // Add a child with 'child_info'.
  RBTreeNode *AttachChild(const RBTreeNodeInfo& child_info);

  // Tree rotation methods.
  void RightRotate();
  void LeftRotate();

  // Height adjustment methods.
  void IncrementHeight();
  void DecrementHeight();

  // Verify integrity of RBSubTree rooted at this node.
  int VerifySubtree(int parent_height);

  // Delete node.
  void Delete();

  // TODO
  void DetachChild(const RBTreeNode *child);

  // TODO
  RBTreeNode *MySuccessor();

  // TODO
  void CopyFieldsFrom(const RBTreeNode *const successor);

  // Setter methods.
  void SetColor(Color color);
  void SetParent(RBTreeNode *parent);
  void SetLeftChild(const Ptr& left_child);
  void SetRightChild(const Ptr& right_child);

  // Return string version of this node.
  string ToString() const;

  // TODO
  void PrintSubtree();

  // Return child other than 'child'.
  RBTreeNode *OtherChild(const RBTreeNode *child);

  // Getter methods.
  bool IsNIL() const { return is_nil_; }
  int key_val() const { return key_val_; }
  int index() const { return index_; }
  Color color() const { return color_; }
  int height() const { return height_; }
  RBTreeNode *parent() const { return parent_; }
  Ptr left_child() const { return left_child_; }
  Ptr right_child() const { return right_child_; }
  RBTreeNode *raw_left_child() const { return left_child_.get(); }
  RBTreeNode *raw_right_child() const { return right_child_.get(); }

  // Get the shared_ptr.
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
