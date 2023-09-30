#pragma once

#include "metron/nodes/CNodeStatement.hpp"

//==============================================================================

struct CNodeUsing : public CNodeStatement {
  uint32_t debug_color() const override;
  std::string_view get_name() const override;
  CHECK_RETURN Err trace(CInstance* inst, call_stack& stack) override;
};

//==============================================================================
