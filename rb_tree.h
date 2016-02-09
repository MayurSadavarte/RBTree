#ifndef RBTREE_H
#define RBTREE_H

#include "rb_tree_node.h"

namespace rbtree {

using namespace std;

typedef struct RBTreeNodeInfo {
  explicit RBTreeNodeInfo(int in_key, int in_index) {
    key = in_key;
    index = in_index;
  }

  int key;
  int index;
} RBTreeNodeInfo;

class RBTree {
 public:
  typedef shared_ptr<RBTree> Ptr;
  typedef shared_ptr<const RBTree> ConstPtr;

  RBTree();
  ~RBTree();

  void Insert(const RBTreeNodeInfo& node_info);

  bool Lookup(int key_val, rbtreenode::RBTreeNode **node_ptr);

  void Print();

 private:
  shared_ptr<rbtreenode::RBTreeNode> root_;
};

} // namespace rbtree

#endif // RBTREE_H
