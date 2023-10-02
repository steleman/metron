#pragma once

#include <string>
#include "metrolib/core/Err.h"

struct CNode;
struct Cursor;

struct CNodeAccess;
struct CNodeAssignment;
struct CNodeBuiltinType;
struct CNodeCall;
struct CNodeCase;
struct CNodeClass;
struct CNodeClassType;
struct CNodeCompound;
struct CNodeConstant;
struct CNodeConstructor;
struct CNodeDeclaration;
struct CNodeDefault;
struct CNodeDoWhile;
struct CNodeEnum;
struct CNodeExpStatement;
struct CNodeField;
struct CNodeFieldExpression;
struct CNodeFunction;
struct CNodeIdentifier;
struct CNodeIf;
struct CNodeKeyword;
struct CNodeNamespace;
struct CNodePrefixExp;
struct CNodePreproc;
struct CNodeQualifiedIdentifier;
struct CNodeReturn;
struct CNodeStruct;
struct CNodeSuffixExp;
struct CNodeSwitch;
struct CNodeTemplate;
struct CNodeTypedef;
struct CNodeUsing;

//==============================================================================

struct Emitter {
  Emitter(Cursor& c) : cursor(c) {}

  Err emit_everything();
  Err emit_default(CNode* node);
  Err emit_children(CNode* node);
  Err emit_dispatch(CNode* node);
  Err emit_dispatch2(CNode* node);

  Err emit(CNodeAssignment* node);
  Err emit(CNodeBuiltinType* node);
  Err emit(CNodeCall* node);
  Err emit(CNodeCase* node);
  Err emit(CNodeClass* node);
  Err emit(CNodeClassType* node);
  Err emit(CNodeCompound* node);
  Err emit(CNodeConstant* node);
  Err emit(CNodeConstructor* node);
  Err emit(CNodeDeclaration* node);
  Err emit(CNodeDefault* node);
  Err emit(CNodeEnum* node);
  Err emit(CNodeExpStatement* node);
  Err emit(CNodeField* node);
  Err emit(CNodeFieldExpression* node);
  Err emit(CNodeFunction* node);
  Err emit(CNodeIdentifier* node);
  Err emit(CNodeIf* node);
  Err emit(CNodeKeyword* node);
  Err emit(CNodeNamespace* node);
  Err emit(CNodePrefixExp* node);
  Err emit(CNodePreproc* node);
  Err emit(CNodeQualifiedIdentifier* node);
  Err emit(CNodeReturn* node);
  Err emit(CNodeStruct* node);
  Err emit(CNodeSuffixExp* node);
  Err emit(CNodeSwitch* node);
  Err emit(CNodeTemplate* node);
  Err emit(CNodeUsing* node);

  Err emit(const char* fmt, ...);
  Err emit_splice(CNode* n);

  Err emit_template_parameter_list(CNodeClass* node);
  Err emit_block(CNodeCompound* node, std::string ldelim, std::string rdelim);
  Err emit_bit_extract(CNodeCall* node);
  Err emit_hoisted_decls(CNodeCompound* node);
  Err emit_call_arg_bindings(CNodeCompound* node, CNode* child);
  Err emit_component(CNodeField* node);
  Err emit_module_ports(CNodeClass* node);
  Err emit_function_ports(CNodeFunction* f);
  Err emit_field_ports(CNodeField* f, bool is_output);
  Err emit_init(CNodeFunction* node);
  Err emit_always_comb(CNodeFunction* node);
  Err emit_always_ff(CNodeFunction* node);
  Err emit_func(CNodeFunction* node);
  Err emit_task(CNodeFunction* node);
  Err emit_func_binding_vars(CNodeFunction* node);

  Cursor& cursor;
};

//==============================================================================
