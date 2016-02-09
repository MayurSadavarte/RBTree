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
  // TODO
  if (!root_) {
    root_ = make_shared<RBTreeNode>(
              false /* is_nil */,
              node_info.key,
              node_info.index,
              1 /* height */);

    RBTreeNode::Ptr left_child = make_shared<RBTreeNode>(
                                   true /* is_nil */,
                                   -1,
                                   -1,
                                   root_->height() + 1);
    RBTreeNode::Ptr right_child = make_shared<RBTreeNode>(
                                    true /* is_nil */,
                                    -1,
                                    -1,
                                    root_->height() + 1);
    root_->SetColor(RBTreeNode::Color::BLACK);
    root_->SetLeftChild(left_child);
    root_->SetRightChild(right_child);

    left_child->SetParent(root_);
    right_child->SetParent(root_);

    cout << '\n' << "Initialized RBTree with root node: " << root_->ToString()
         << '\n';
    return;
  }
}

bool RBTree::Lookup(
  const int key_val,
  RBTreeNode **const node_ptr) {
  // TODO
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
    rbtree::RBTreeNodeInfo info(keys[ii], ii);
    rbtree->Insert(info);
  }

  rbtree->Print();
}
