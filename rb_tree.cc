#include "rb_tree_node.h"
#include "rb_tree.h"

#include <assert.h>
#include <list>
#include <sstream>

using namespace std;

namespace rbtree {

shared_ptr<rbtreenode::RBTreeNode> root_;

using namespace rbtreenode;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////    RBTree  /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RBTree::RBTree() {
  // TODO
}

RBTree::~RBTree() {
  // TODO
}

/*****************************************************************************/

void RBTree::Insert(const RBTreeNodeInfo& node_info) {
  // CASE_1:
  // Tree doesn't exist.
  if (!root_) {
    root_ = make_shared<RBTreeNode>(
              false /* is_nil */,
              node_info.key,
              node_info.index,
              1 /* height */);

    root_->SetColor(RBTreeNode::Color::BLACK);

    cout << "Initialized RBTree with root node: " << root_->ToString()
         << '\n';
    return;
  }

  RBTreeNode *node = NULL;
  // CASE_2:
  // Node already exists in the tree.
  if (Lookup(node_info.key, &node)) {
    cout << "Node " << node->ToString()
         << " already exists in the tree" << '\n';
    return;
  }

  assert(node);
  RBTreeNode *parent = node;
  cout << "Lookup found node: " << parent->ToString() << '\n';

  // Attach the node to the appropriate parent.
  node = parent->AttachChild(node_info);

  ReadjustTree(node);
}

/*****************************************************************************/

void RBTree::ReadjustTree(RBTreeNode *const node) {
  assert(node);
  assert(node->color() == RBTreeNode::Color::RED);

  if (!root_) {
    cout << "RBTree is empty." << '\n';
    return;
  }

  // CASE_1:
  // Node itself is a current root_.
  if (node == root_.get()) {
    cout << "Node " << node->ToString() << " itself is a root, will just "
         << "change a color to RED" << '\n';
    node->SetColor(RBTreeNode::Color::BLACK);
    return;
  }

  assert(node->parent());
  RBTreeNode *const parent = node->parent();

  // CASE_3:
  // Node's parent is black.
  if (parent->color() == RBTreeNode::Color::BLACK) {
    cout << "Node's " << node->ToString() << " current parent is BLACK "
         << "No change needed" << '\n';
    return;
  }

  if (parent->color() == RBTreeNode::Color::RED) {
    assert(parent->parent());
    RBTreeNode *grandparent = parent->parent();
    RBTreeNode *uncle = grandparent->OtherChild(parent);

    if (uncle->color() == RBTreeNode::Color::RED) {
      // CASE_4:
      // Node's parent is red and uncle is red.
      // Uncle is a RED root of a subtree.

      parent->SetColor(RBTreeNode::Color::BLACK);
      uncle->SetColor(RBTreeNode::Color::BLACK);

      assert(grandparent->color() == RBTreeNode::Color::BLACK);
      grandparent->SetColor(RBTreeNode::Color::RED);

      ReadjustTree(grandparent);
      return;
    }

    assert(grandparent->color() == RBTreeNode::Color::BLACK);
    // CASE_5 and CASE_6:
    // Node's parent is red and uncle is NIL/BLACK.
    //
    // CASE_5:
    // Node is parent's left child and parent is grandparent's right child.
    // Node is parent's right child and parent is grandparent's left child.
    if ((parent->raw_left_child() == node &&
         grandparent->raw_right_child() == parent)) {
      parent->RightRotate();
      ReadjustTree(parent);
      return;
    }

    if ((parent->raw_right_child() == node &&
         grandparent->raw_left_child() == parent)) {
      parent->LeftRotate();
      ReadjustTree(parent);
      return;
    }
    //
    // CASE_6:
    // Node is parent's left child and parent is grandparent's left child.
    // Node is parent's right child and parent is grandparent's right child.
    if (parent->raw_left_child() == node) {
      assert(grandparent->raw_left_child() == parent);
      grandparent->RightRotate();

      grandparent->SetColor(RBTreeNode::Color::RED);
      parent->SetColor(RBTreeNode::Color::BLACK);
      assert(node->color() == RBTreeNode::Color::RED);
      return;
    }

    assert(grandparent->raw_right_child() == parent);
    grandparent->LeftRotate();

    grandparent->SetColor(RBTreeNode::Color::RED);
    parent->SetColor(RBTreeNode::Color::BLACK);
    assert(node->color() == RBTreeNode::Color::RED);
    return;
  }
}

/*****************************************************************************/

bool RBTree::Lookup(
  const int key_val,
  RBTreeNode **const node_ptr) {

  if (!root_) {
    cout << "RBTree is empty" << '\n';
    *node_ptr = NULL;
    return false;
  }

  RBTreeNode *search_node = root_.get();
  while (!search_node->IsNIL()) {
    if (search_node->key_val() == key_val) {
      *node_ptr = search_node;
      return true;
    }

    if (key_val < search_node->key_val()) {
      search_node = search_node->raw_left_child();
      continue;
    }

    search_node = search_node->raw_right_child();
  }

  *node_ptr = search_node->parent();
  return false;
}

/*****************************************************************************/

void RBTree::Print() {
  cout << '\n' << "Printing RBTree: " << '\n';
  if (!root_) {
    cout << "NULL" << '\n';
    return;
  }

  typedef list<RBTreeNode::Ptr> NodeList;
  NodeList node_list;

  stringstream ss;

  node_list.emplace_back(root_);

  NodeList::const_iterator cnliter = node_list.begin();
  while (cnliter != node_list.end()) {
    const RBTreeNode::Ptr& node_ptr = *cnliter;
    assert(node_ptr);

    ss << node_ptr->ToString() << ", ";

    if (node_ptr->left_child()) {
      node_list.emplace_back(node_ptr->left_child());
    }

    if (node_ptr->right_child()) {
      node_list.emplace_back(node_ptr->right_child());
    }

    ++cnliter;
  }

  cout << "RBTree has " << node_list.size() << " elements" << '\n';
  cout << ss.str() << '\n';
}

/*****************************************************************************/

void RBTree::VerifyIntegrity() {
  if (!root_) {
    cout << "RBTree is empty. Verification successful." << '\n';
    return;
  }

  const int bh = root_->VerifySubtree(0 /* parent's height */);
}

/*****************************************************************************/

} // namespace rbtree

int main() {
  rbtree::RBTree::Ptr rbtree = make_shared<rbtree::RBTree>();

  int keys[] = {7, 18, 10, 3, 8, 22, 26, 15};
  int num_keys = sizeof(keys) / sizeof(int);

  for (int ii = 0; ii < num_keys; ++ii) {
    cout << "Inserting: [" << keys[ii] << ", " << ii << " ]" << '\n';
    rbtree::rbtreenode::RBTreeNodeInfo info(keys[ii], ii);
    rbtree->Insert(info);

    rbtree->VerifyIntegrity();
  }

  rbtree->Print();
}
