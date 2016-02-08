#include "rb_tree_node.h"
#include "rb_tree.h"

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
}

bool RBTree::Lookup(
  const int key_val,
  RBTreeNode **const node_ptr) {
  // TODO
}

void RBTree::Print() {
  // TODO
}

} // namespace rbtree

int main() {
  rbtree::RBTree::Ptr rbtree = make_shared<rbtree::RBTree>();
}
