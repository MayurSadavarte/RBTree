#include "rb_tree_node.h"

#include <sstream>
#include <assert.h>

namespace rbtree { namespace rbtreenode {

using namespace std;

RBTreeNode::RBTreeNode(
  const bool is_nil,
  const int key_val,
  const int index,
  const int height) :
  is_nil_(is_nil),
  key_val_(key_val),
  index_(index),
  color_(is_nil_ ? Color::BLACK : Color::RED),
  height_(height) {
  // TODO
}


RBTreeNode::~RBTreeNode() {
  // TODO
}

void RBTreeNode::SetColor(Color color) {
  color_ = color;
}

void RBTreeNode::SetParent(const Ptr& parent) {
  parent_ = parent;
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
