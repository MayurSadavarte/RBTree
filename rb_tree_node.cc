#include "rb_tree_node.h"

#include <sstream>
#include <assert.h>

namespace rbtree { namespace rbtreenode {

using namespace std;

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
  // TODO
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

void RBTreeNode::AttachChild(const RBTreeNodeInfo& child_info) {
  assert(child_info.key != key_val_);
  Ptr child_node = make_shared<RBTreeNode>(
                     false /* is_nil */,
                     child_info.key,
                     child_info.index,
                     height_ + 1,
                     this);

  if (child_node->key_val() < key_val_) {
    left_child_ = child_node;
    return;
  }

  assert(child_node->key_val() > key_val_);
  right_child_ = child_node;
}

void RBTreeNode::SetColor(Color color) {
  color_ = color;
}

void RBTreeNode::SetParent(const Ptr& parent) {
  assert(parent);
  parent_ = parent.get();
}

void RBTreeNode::SetLeftChild(const Ptr& left_child) {
  left_child_ = left_child;
}

void RBTreeNode::SetRightChild(const Ptr& right_child) {
  right_child_ = right_child;
}

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

} } // namespace
