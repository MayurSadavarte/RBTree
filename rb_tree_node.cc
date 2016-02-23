#include "rb_tree_node.h"

#include <list>
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

void RBTreeNode::Delete() {
  cout << "Deleting node: " << ToString() << '\n';
  assert(!is_nil_);

  // Create a temporary shared_ptr to keep outselves alive until the
  // function is executing.
  Ptr temporary = getptr();

  if (left_child_->IsNIL() && right_child_->IsNIL()) {
    if (!parent_) {
      assert(this == root_.get());
      // Looks like we are deleting the 'root_'.
      root_.reset();
      return;
    }

    // TODO: case to be handled.
    assert(color_ != Color::BLACK);

    // Internal node.
    parent_->DetachChild(this);
    return;
  }

  bool one_child_nil = false;
  RBTreeNode::Ptr non_nil_child = nullptr;
  if (left_child_->IsNIL()) {
    one_child_nil = true;
    non_nil_child = right_child_;
  }
  if (right_child_->IsNIL()) {
    assert(!one_child_nil);
    one_child_nil = true;
    assert(!non_nil_child);
    non_nil_child = left_child_;
  }

  if (one_child_nil) {
    assert(color_ == Color::BLACK);
    if (!parent_) {
      assert(this == root_.get());
      non_nil_child->DecrementHeight();
      root_ = non_nil_child;
      if (root_->color() == Color::RED) {
        root_->SetColor(Color::BLACK);
      }
      return;
    }

    non_nil_child->DecrementHeight();
    non_nil_child->SetColor(color_);
    if (parent_->raw_left_child() == this) {
      parent_->SetLeftChild(non_nil_child);
    } else {
      assert(parent_->raw_right_child() == this);
      parent_->SetRightChild(non_nil_child);
    }
    return;
  }

  RBTreeNode *const successor = MySuccessor();
  CopyFieldsFrom(successor);

  // TODO
  PrintSubtree();
  // TODO
  successor->Delete();
}

/*****************************************************************************/

void RBTreeNode::DetachChild(const RBTreeNode *child) {
  if (left_child_.get() == child) {
    left_child_.reset();
    return;
  }

  assert(right_child_.get() == child);
  right_child_.reset();
}

/*****************************************************************************/

RBTreeNode *RBTreeNode::MySuccessor() {
  assert(!right_child_->IsNIL());

  Ptr node = right_child_;
  while (!node->IsNIL()) {
    node = node->left_child();
  }

  return node->parent_;
}

/*****************************************************************************/

void RBTreeNode::CopyFieldsFrom(const RBTreeNode *const successor) {
  assert(!is_nil_);

  key_val_ = successor->key_val();
  index_ = successor->index();
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

void RBTreeNode::PrintSubtree() {
  cout << "Printing RBSubTree rooted at: " << ToString() << '\n';;
  typedef list<RBTreeNode::Ptr> NodeList;
  NodeList node_list;

  stringstream ss;

  node_list.emplace_back(getptr());

  int prev_height = height_;
  NodeList::const_iterator cnliter = node_list.begin();
  while (cnliter != node_list.end()) {
    const RBTreeNode::Ptr& node_ptr = *cnliter;
    assert(node_ptr);

    if (prev_height < node_ptr->height()) {
      ss << '\n';
    }
    ss << node_ptr->ToString() << ", ";
    prev_height = node_ptr->height();

    if (node_ptr->left_child()) {
      node_list.emplace_back(node_ptr->left_child());
    }

    if (node_ptr->right_child()) {
      node_list.emplace_back(node_ptr->right_child());
    }

    ++cnliter;
  }

  cout << "RBSubTree has " << node_list.size() << " elements" << '\n';
  cout << ss.str() << '\n';
}

/*****************************************************************************/

} } // namespace
