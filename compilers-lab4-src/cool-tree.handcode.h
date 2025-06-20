//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include "tree.h"
#include "stringtab.h"

#define yylineno curr_lineno

/* a type renaming */
typedef int Boolean;
class Entry;
typedef Entry *Symbol;

extern int yylineno;

inline Boolean copy_Boolean(Boolean b) {return b; }
inline void assert_Boolean(Boolean) {}
inline void dump_Boolean(std::ostream &  stream, int padding, Boolean b)
	{ stream << pad(padding) << (int) b << "\n"; }

void dump_Symbol(std::ostream &  stream, int padding, Symbol b);
void assert_Symbol(Symbol b);
Symbol copy_Symbol(Symbol b);

class Program_class;
typedef Program_class *Program;
class Class__class;
typedef Class__class *Class_;
class Feature_class;
typedef Feature_class *Feature;
class Formal_class;
typedef Formal_class *Formal;
class Expression_class;
typedef Expression_class *Expression;
class Case_class;
typedef Case_class *Case;

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

#define Program_EXTRAS                          \
virtual void dump_with_types(std::ostream & , int) = 0; 

#define Program_SHARED_EXTRAS                           \
void dump_with_types(std::ostream & , int);            

#define Class__EXTRAS                   \
virtual Symbol get_filename() = 0;      \
virtual void dump_with_types(std::ostream & ,int) = 0;


#define class__EXTRAS                                 \
Symbol get_filename() { return filename; }             \
void dump_with_types(std::ostream & ,int);                    


#define Feature_EXTRAS                                        \
virtual void dump_with_types(std::ostream & ,int) = 0; 


#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(std::ostream & ,int);    





#define Formal_EXTRAS                              \
virtual void dump_with_types(std::ostream & ,int) = 0;


#define formal_EXTRAS                           \
void dump_with_types(std::ostream & ,int);


#define Case_EXTRAS                             \
virtual void dump_with_types(std::ostream &  ,int) = 0;


#define branch_EXTRAS                                   \
void dump_with_types(std::ostream &  ,int);


#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void dump_with_types(std::ostream & ,int) = 0;  \
void dump_type(std::ostream & , int);               \
Expression parent; \
virtual void set_body(const Expression e) {  }\
Expression_class() { type = (Symbol) NULL; }

#define let_EXTRAS \
void set_body(const Expression e) override {\
	e->parent = this; \
	body = e;\
}

#define Expression_SHARED_EXTRAS           \
void dump_with_types(std::ostream & ,int);


#endif

