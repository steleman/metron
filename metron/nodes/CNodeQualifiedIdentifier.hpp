#pragma once

#include "metron/CNode.hpp"

struct CNodePunct;

//==============================================================================

struct CNodeQualifiedIdentifier : public CNode {
  void init(const char* match_tag, SpanType span, uint64_t flags);
  uint32_t debug_color() const override;
  std::string_view get_name() const override;
  CHECK_RETURN Err trace(CInstance* inst, call_stack& stack) override;

  CNode* node_scope = nullptr;
  CNodePunct* node_colon = nullptr;
  CNode* node_name  = nullptr;
};

//==============================================================================
