/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   antlr -gt sceneReader.g
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// struct to store information about tokens
typedef struct 
{
  string kind;
  string text;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr,  int type,  char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as, attr, ttype, textt) as=createASTnode(attr, ttype, textt)
AST* createASTnode(Attrib* attr, int ttype,  char *textt);
#define GENAST

#include "ast.h"

#define zzSET_SIZE 4
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "ast.c"
zzASTgvars

ANTLR_INFO

#include <cstdlib>
#include <cmath>
AST* root;

//global structures: AST
// function to fill token information
void zzcr_attr(Attrib *attr,  int type,  char *text) 
{
  if (type == ID) 
  {
    attr->kind = "id";
    attr->text = text;
  }
  else 
  {
    attr->kind = text;
    attr->text = "";
  }
}

//function to create a new AST node
AST* createASTnode(Attrib* attr,  int type,  char* text) 
{
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->right = NULL; 
  as->down = NULL;
  return as;
}


//create a new "list" AST node with one element
AST* createASTlist(AST *child) 
{
  AST *as = new AST;
  as->kind = "list";
  as->right = NULL;
  as->down = child;
  return as;
}

AST *findDefinition(string id) 
{
  AST *n = root->down->right->right->down;
  while (n != NULL and (n->down->text != id)) n = n->right;
  if (n == NULL) {cout << "NOT FOUND: " << id << " " << endl;}
  return n->down->right;
}

//print AST,  recursively,  with indentation
void ASTPrintIndent(AST *a, string s)
{
  if (a == NULL) return;
  
  cout << a->kind;
  if (a->text != "") cout << "(" << a->text << ")";
  cout << endl;
  
  AST *i = a->down;
  while (i != NULL && i->right != NULL) 
  {
    cout << s + "  \\__";
    ASTPrintIndent(i, s + "  |" + string(i->kind.size() + i->text.size(), ' '));
    i = i->right;
  }
  
  if (i != NULL) 
  {
    cout << s + "  \\__";
    ASTPrintIndent(i, s + "   " + string(i->kind.size() + i->text.size(), ' '));
    i = i->right;
  }
}

//print AST 
void ASTPrint(AST *a)
{
  while (a != NULL) 
  {
    cout << " ";
    ASTPrintIndent(a, "");
    a = a->right;
  }
}

#ifndef MEC
#define MEC
#include "../src/SceneReader.cpp"
#endif

/*
int main() 
{
  root = NULL;
  ANTLR(program(&root),  stdin);
  ASTPrint(root);
}
*/

void
#ifdef __USE_PROTOS
program(AST**_root)
#else
program(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(SCENE); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==ID) ) {
      object(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x1);
  }
}

void
#ifdef __USE_PROTOS
object(AST**_root)
#else
object(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(ID); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  propertyList(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x2);
  }
}

void
#ifdef __USE_PROTOS
propertyList(AST**_root)
#else
propertyList(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(LBRACE);  zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==ID) ) {
      property(zzSTR); zzlink(_root, &_sibling, &_tail);
      {
        zzBLOCK(zztasp3);
        zzMake0;
        {
        while ( (LA(1)==COMMA) ) {
          zzmatch(COMMA);  zzCONSUME;
          property(zzSTR); zzlink(_root, &_sibling, &_tail);
          zzLOOP(zztasp3);
        }
        zzEXIT(zztasp3);
        }
      }
    }
    else {
      if ( (LA(1)==RBRACE) ) {
      }
      else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(RBRACE);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x4);
  }
}

void
#ifdef __USE_PROTOS
property(AST**_root)
#else
property(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(ID); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(EQUAL);  zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (setwd1[LA(1)]&0x8) ) {
      number(zzSTR); zzlink(_root, &_sibling, &_tail);
    }
    else {
      if ( (LA(1)==LPAREN) ) {
        vec3(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x10);
  }
}

void
#ifdef __USE_PROTOS
number(AST**_root)
#else
number(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==FLOAT) ) {
      zzmatch(FLOAT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {
      if ( (LA(1)==INT) ) {
        zzmatch(INT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {zzFAIL(1,zzerr3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x20);
  }
}

void
#ifdef __USE_PROTOS
vec3(AST**_root)
#else
vec3(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(LPAREN); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  number(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(COMMA);  zzCONSUME;
  number(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(COMMA);  zzCONSUME;
  number(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(RPAREN);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x40);
  }
}
