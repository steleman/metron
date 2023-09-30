#pragma once

#include <assert.h>

#include <vector>

#include "metron/CNode.hpp"
#include "metron/Cursor.hpp"
#include "metron/nodes/CNodeType.hpp"

struct CSourceRepo;
struct CSourceFile;
struct CInstance;
struct CInstClass;
struct CNodeField;
struct CNodeFunction;
struct CNodeDeclaration;
struct CNodeEnum;
struct CNodeKeyword;
struct CNodeIdentifier;
struct CNodeList;
struct CNodeConstructor;

//==============================================================================

struct CNodeClass : public CNode {
  void init(const char* match_tag, SpanType span, uint64_t flags);

  //----------

  uint32_t debug_color() const override;
  std::string_view get_name() const override;
  virtual void dump() const override;

  CSourceRepo* get_repo() override {
    return repo;
  }

  //----------

  CNodeField*       get_field(CNode* node_name);
  CNodeField*       get_field(std::string_view name);
  CNodeFunction*    get_function(std::string_view name);
  CNodeDeclaration* get_modparam(std::string_view name);
  CNodeEnum*        get_enum(std::string_view name);

  bool needs_tick();
  bool needs_tock();

  Err collect_fields_and_methods();
  Err build_call_graph(CSourceRepo* repo);
  void dump_call_graph();

  Err emit_module_ports(Cursor& cursor);
  Err emit_template_parameter_list(Cursor& cursor);
  Err emit_function_ports(CNodeFunction* f, Cursor& cursor);
  Err emit_field_ports(CNodeField* f, bool is_output, Cursor& cursor);

  void dump_fields();

  //----------------------------------------

  std::string name;

  CNodeKeyword*    node_class = nullptr;
  CNodeIdentifier* node_name = nullptr;
  CNodeList*       node_body = nullptr;

  CSourceRepo* repo = nullptr;
  CSourceFile* file = nullptr;
  int refcount = 0;

  std::vector<CNode*> ports;

  std::vector<CNodeFunction*>    top_functions;


  CNodeConstructor* constructor = nullptr;
  std::vector<CNodeFunction*>    all_functions;
  std::vector<CNodeField*>       all_fields;
  std::vector<CNodeDeclaration*> all_modparams;
  std::vector<CNodeField*>       all_localparams;
  std::vector<CNodeEnum*>        all_enums2;

  std::vector<CNodeField*> input_signals;
  std::vector<CNodeField*> output_signals;
  std::vector<CNodeField*> output_registers;

  std::vector<CNodeField*> components;
  std::vector<CNodeField*> private_signals;
  std::vector<CNodeField*> private_registers;
  std::vector<CNodeField*> dead_fields;
};

//==============================================================================

struct CNodeClassType : public CNodeType {
  std::string_view get_name() const override {
    return child("name")->get_text();
  }
};

//==============================================================================
