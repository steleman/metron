#pragma once

#include "metron/CNode.hpp"

//==============================================================================

struct CNodePreproc : public CNode {
  uint32_t debug_color() const override;
  std::string_view get_name() const override;
  CHECK_RETURN Err trace(CInstance* inst, call_stack& stack) override;
};

//==============================================================================
