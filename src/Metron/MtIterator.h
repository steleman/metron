#pragma once

#include "tree_sitter/api.h"

//------------------------------------------------------------------------------

struct MtHandle {
  TSNode node;
  TSSymbol sym;
  int field;
  int index;

  operator TSNode() const { return node; }
};

//------------------------------------------------------------------------------

struct MtIterator {

  MtIterator& operator++() {
    index++;
    return *this;
  }

  bool operator != (const MtIterator& n) {
    if (parent.context[0] != n.parent.context[0]) return true;
    if (parent.context[1] != n.parent.context[1]) return true;
    if (parent.context[2] != n.parent.context[2]) return true;
    if (parent.context[3] != n.parent.context[3]) return true;
    if (parent.id != n.parent.id)         return true;
    if (parent.tree != n.parent.tree)       return true;

    if (index != n.index) return true;

    return false;
  }

  MtHandle operator*() const {
    auto child = ts_node_child(parent, index);
    return {
      child,
      ts_node_symbol(child),
      ts_node_field_id_for_child(parent, index),
      index
    };
  }

  TSNode parent;
  int index;
};

inline MtIterator begin(TSNode& parent) {
  return { parent, 0 };
}

inline MtIterator end(TSNode& parent) {
  return { parent, (int)ts_node_child_count(parent) };
}

//------------------------------------------------------------------------------
