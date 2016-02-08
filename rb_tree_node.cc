#include "rb_tree_node.h"

#include <sstream>

using namespace std;

namespace rbtree { namespace rbtreenode {

RBTreeNode::RBTreeNode(
  const bool is_nil,
  const int height,
  const int black_height,
  const int key_val,
  const int index) :
  is_nil_(is_nil),
  key_val_(key_val),
  index_(index),
  color_(Color::RED),
  height_(height),
  black_height_(black_height) {

  // TODO
}


RBTreeNode::~RBTreeNode() {
  // TODO
}

string RBTreeNode::PrintString() {
  stringstream ss;

  ss << "[ " << is_nil_ << ", " << key_val_ << ", "
     << index_ << ", "
     << (color_ == Color::RED ? "RED" : "BLACK")
     << ", " << height_
     << ", " << black_height_ << " ]";

  return ss.str();
}

} } // namespace
