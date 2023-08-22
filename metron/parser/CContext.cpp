// SPDX-FileCopyrightText:  2023 Austin Appleby <aappleby@gmail.com>
// SPDX-License-Identifier: MIT License

#include "CContext.hpp"

#include "CParser.hpp"
#include <assert.h>

#include "metrolib/core/Log.h"

using namespace matcheroni;

using namespace matcheroni::utils;

TokenSpan match_translation_unit(CContext& ctx, TokenSpan body);









//------------------------------------------------------------------------------

CContext::CContext() {
  type_scope = new CScope();
  tokens.reserve(65536);
}

//------------------------------------------------------------------------------

void CContext::reset() {
  NodeContext::reset();

  source.clear();
  lexemes.clear();
  tokens.clear();
  while (type_scope->parent) pop_scope();
  type_scope->clear();
  root_node = nullptr;
}

//------------------------------------------------------------------------------

TokenSpan CContext::parse() {

  // Skip over BOF, stop before EOF
  //printf("tokens.size() %d\n", int(tokens.size()));

  TokenSpan body(tokens.data() + 1, tokens.data() + tokens.size() - 1);

  auto tail = match_translation_unit(*this, body);

  if (tail.is_valid() && tail.is_empty()) {
    if (top_head == top_tail) {
      root_node = top_head;
    }
  }

  return tail;
}

//------------------------------------------------------------------------------

TokenSpan CContext::match_class_name(TokenSpan body) {
  return type_scope->has_class(*this, body) ? body.advance(1) : body.fail();
}

TokenSpan CContext::match_struct_name(TokenSpan body) {
  return type_scope->has_struct(*this, body) ? body.advance(1) : body.fail();
}

TokenSpan CContext::match_union_name(TokenSpan body) {
  return type_scope->has_union(*this, body) ? body.advance(1) : body.fail();
}

TokenSpan CContext::match_enum_name(TokenSpan body) {
  return type_scope->has_enum(*this, body) ? body.advance(1) : body.fail();
}

TokenSpan CContext::match_typedef_name(TokenSpan body) {
  return type_scope->has_typedef(*this, body) ? body.advance(1) : body.fail();
}

void CContext::add_class  (const CToken* a) { type_scope->add_class(*this, a); }
void CContext::add_struct (const CToken* a) { type_scope->add_struct(*this, a); }
void CContext::add_union  (const CToken* a) { type_scope->add_union(*this, a); }
void CContext::add_enum   (const CToken* a) { type_scope->add_enum(*this, a); }
void CContext::add_typedef(const CToken* a) { type_scope->add_typedef(*this, a); }

//----------------------------------------------------------------------------

void CContext::push_scope() {
  CScope* new_scope = new CScope();
  new_scope->parent = type_scope;
  type_scope = new_scope;
}

void CContext::pop_scope() {
  CScope* old_scope = type_scope->parent;
  if (old_scope) {
    delete type_scope;
    type_scope = old_scope;
  }
}

//----------------------------------------------------------------------------

TokenSpan CContext::match_builtin_type_base(TokenSpan body) {
  if (!body.is_valid() || body.is_empty()) return body.fail();
  if (SST<builtin_type_base>::match(body.begin->lex->text_begin, body.begin->lex->text_end)) {
    return body.advance(1);
  }
  else {
    return body.fail();
  }
}

TokenSpan CContext::match_builtin_type_prefix(TokenSpan body) {
  if (!body.is_valid() || body.is_empty()) return body.fail();

  auto lex = body.begin->lex;
  if (SST<builtin_type_prefix>::match(lex->text_begin, lex->text_end)) {
    return body.advance(1);
  }
  else {
    return body.fail();
  }
}

TokenSpan CContext::match_builtin_type_suffix(TokenSpan body) {
  if (!body.is_valid() || body.is_empty()) return body.fail();

  auto lex = body.begin->lex;
  if (SST<builtin_type_suffix>::match(lex->text_begin, lex->text_end)) {
    return body.advance(1);
  }
  else {
    return body.fail();
  }
}

//------------------------------------------------------------------------------
