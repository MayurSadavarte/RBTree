#include "rb_tree_node.h"

#include <sstream>
#include <assert.h>

namespace rbtree {
  using namespace std;
  extern shared_ptr<rbtreenode::RBTreeNode> root_;
}

namespace rbtree { namespace rbtreenode {

using namespace std;

/*****************************************************************************/

RBTreeNode::RBTreeNode(
  const bool is_nil,
  const int key_val,
  const int index,
  const int height,
  RBTreeNode *parent) :
  is_nil_(is_nil),
  key_val_(key_val),
  index_(index),
  color_(is_nil_ ? Color::BLACK : Color::RED),
  height_(height),
  parent_(parent) {

  if (!is_nil) {
    left_child_ = make_shared<RBTreeNode>(
                    true /* is_nil */,
                    -1,
                    -1,
                    height_ + 1,
                    this);
    right_child_ = make_shared<RBTreeNode>(
                     true /* is_nil */,
                     -1,
                     -1,
                     height_ + 1,
                     this);
  } else {
    assert(parent_);
  }
}

RBTreeNode::~RBTreeNode() {
  // TODO
}

/*****************************************************************************/

RBTreeNode *RBTreeNode::AttachChild(const RBTreeNodeInfo& child_info) {
  assert(child_info.key != key_val_);
  Ptr child_node = make_shared<RBTreeNode>(
                     false /* is_nil */,
                     child_info.key,
                     child_info.index,
                     height_ + 1,
                     this);

  cout << "Attaching " << child_node->ToString() << " to " << ToString()
       << '\n';
  if (child_node->key_val() < key_val_) {
    left_child_ = child_node;
    return left_child_.get();
  }

  assert(child_node->key_val() > key_val_);
  right_child_ = child_node;

  return right_child_.get();
}

/*****************************************************************************/

void RBTreeNode::RightRotate() {
  cout << "Right Rotating RBTree around: " << ToString() << '\n';

  RBTreeNode *current_parent = parent_;
  parent_ = left_child_.get();

  Ptr current_left_child = left_child_;
  current_left_child->DecrementHeight();
  left_child_ = current_left_child->right_child();
  left_child_->SetParent(this);

  current_left_child->SetParent(current_parent);
  current_left_child->SetRightChild(getptr());

  IncrementHeight();

  if (!current_parent) {
    cout << "Updating 'root_' of RBTree as node " << ToString()
         << " is a current 'root_'" << '\n';
    root_ = current_left_child;
    assert(!root_->IsNIL());
    return;
  }

  if (current_parent->left_child().get() == this) {
    current_parent->SetLeftChild(current_left_child);
  } else {
    assert(current_parent->right_child().get() == this);
    current_parent->SetRightChild(current_left_child);
  }
}

/*****************************************************************************/

void RBTreeNode::LeftRotate() {
  cout << "Left Rotating RBTree around: " << ToString() << '\n';

  RBTreeNode *current_parent = parent_;
  parent_ = right_child_.get();

  Ptr current_right_child = right_child_;
  current_right_child->DecrementHeight();
  right_child_ = current_right_child->left_child();
  right_child_->SetParent(this);

  current_right_child->SetParent(current_parent);
  current_right_child->SetLeftChild(getptr());
  IncrementHeight();

  if (!current_parent) {
    cout << "Updating 'root_' of RBTree as node " << ToString()
         << " is a current 'root_'" << '\n';
    root_ = current_right_child;
    assert(!root_->IsNIL());
    return;
  }

  if (current_parent->left_child().get() == this) {
    current_parent->SetLeftChild(current_right_child);
  } else {
    assert(current_parent->right_child().get() == this);
    current_parent->SetRightChild(current_right_child);
  }
}

/*****************************************************************************/

void RBTreeNode::IncrementHeight() {
  ++height_;
  cout << "Incremented height of " << ToString() << '\n';

  if (left_child_) {
    left_child_->IncrementHeight();
  }

  if (right_child_) {
    right_child_->IncrementHeight();
  }
}

/*****************************************************************************/

void RBTreeNode::DecrementHeight() {
  --height_;
  cout << "Decremented height of " << ToString() << '\n';

  if (left_child_) {
    left_child_->DecrementHeight();
  }

  if (right_child_) {
    right_child_->DecrementHeight();
  }
}

/*****************************************************************************/

int RBTreeNode::VerifySubtree(const int parent_height) {
  cout << "RBSubTree being verified for Node: " << ToString() << '\n';
  assert(parent_height >= 0);

  assert(height_ == parent_height + 1);
  if (parent_height == 0) {
    // Root of RBTree.
    assert(!parent_);
    assert(color_ == Color::BLACK);
  }

  if (is_nil_) {
    assert(color_ == Color::BLACK);
    assert(!left_child_ && !right_child_);
  }

  if (color_ == Color::RED) {
    assert(parent_);
    assert(parent_->color() == Color::BLACK);
  }

  int left_bh = 0;
  int right_bh = 0;
  if (left_child_) {
    left_bh = left_child_->VerifySubtree(height_);
  }

  if (right_child_) {
    right_bh = right_child_->VerifySubtree(height_);
  }

  assert(left_bh == right_bh);

  int my_bh = left_bh;
  if (color_ == Color::BLACK) {
    ++my_bh;
  }

  return my_bh;
}

/*****************************************************************************/

void RBTreeNode::SetColor(Color color) {
  color_ = color;
}

void RBTreeNode::SetParent(RBTreeNode *const parent) {
  parent_ = parent;
}

void RBTreeNode::SetLeftChild(const Ptr& left_child) {
  left_child_ = left_child;
}

void RBTreeNode::SetRightChild(const Ptr& right_child) {
  right_child_ = right_child;
}

/*****************************************************************************/

RBTreeNode *RBTreeNode::OtherChild(const RBTreeNode *const child) {
  assert(child == left_child_.get() || child == right_child_.get());

  if (child == left_child_.get()) {
    return right_child_.get();
  } else {
    return left_child_.get();
  }
}

/*****************************************************************************/

string RBTreeNode::ToString() const {
  stringstream ss;

  ss << "[ " << (is_nil_ ? "NIL, " : "")
     << key_val_ << ", "
     << index_ << ", "
     << (color_ == Color::RED ? "RED" : "BLACK")
     << ", " << height_
     << ", " << black_height_ << " ]";

  return ss.str();
}

/*****************************************************************************/

} } // namespace
