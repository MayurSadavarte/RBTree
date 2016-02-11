#include "rb_tree_node.h"
#include "rb_tree.h"

#include <assert.h>
#include <list>
#include <sstream>

using namespace std;

namespace rbtree {

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

    cout << '\n' << "Initialized RBTree with root node: " << root_->ToString()
         << '\n';
    return;
  }

  RBTreeNode *node = NULL;
  // CASE_2:
  // Node already exists in the tree.
  if (Lookup(node_info.key, &node)) {
    cout << '\n' << "Node " << node->ToString()
         << " already exists in the tree" << '\n';
    return;
  }

  assert(node);
  cout << '\n' << "Lookup found node: " << node->ToString() << '\n';

  // CASE_3:
  // Node's parent is black.
  if (node->color() == RBTreeNode::Color::BLACK) {
    node->AttachChild(node_info);
    return;
  }

  // CASE_4:
  // Node's parent is red and uncle is red.


  // CASE_5:
  // Node's parent is red and uncle is NIL.
}

bool RBTree::Lookup(
  const int key_val,
  RBTreeNode **const node_ptr) {

  if (!root_) {
    cout << '\n' << "RBTree is empty" << '\n';
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
      search_node = search_node->left_child().get();
      continue;
    }

    search_node = search_node->right_child().get();
  }

  *node_ptr = search_node->parent();
  return false;
}

void RBTree::Print() {
  // TODO
  cout << '\n' << "Printing RBTree: " << '\n';
  if (!root_) {
    cout << '\n' << "NULL" << '\n';
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

  cout << '\n' << "RBTree has " << node_list.size() << " elements" << '\n';
  cout << '\n' << ss.str() << '\n';
}

} // namespace rbtree

int main() {
  rbtree::RBTree::Ptr rbtree = make_shared<rbtree::RBTree>();

  int keys[] = {7, 18, 10, 3, 8, 22, 26};
  int num_keys = sizeof(keys) / sizeof(int);

  for (int ii = 0; ii < num_keys; ++ii) {
    cout << '\n' << "Inserting: [" << keys[ii] << ", " << ii << " ]";
    rbtree::rbtreenode::RBTreeNodeInfo info(keys[ii], ii);
    rbtree->Insert(info);
  }

  rbtree->Print();
}
