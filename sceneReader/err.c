/*
 * A n t l r  S e t s / E r r o r  F i l e  H e a d e r
 *
 * Generated from: sceneReader.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
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
#define zzSET_SIZE 4
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "err.h"

ANTLRChar *zztokens[15]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"MATERIALS",
	/* 03 */	"SCENE",
	/* 04 */	"LPAREN",
	/* 05 */	"RPAREN",
	/* 06 */	"LBRACE",
	/* 07 */	"RBRACE",
	/* 08 */	"COLON",
	/* 09 */	"EQUAL",
	/* 10 */	"COMMA",
	/* 11 */	"ID",
	/* 12 */	"FLOAT",
	/* 13 */	"INT",
	/* 14 */	"SPACE"
};
SetWordType zzerr1[4] = {0xc,0x0,0x0,0x0};
SetWordType zzerr2[4] = {0x40,0x1,0x0,0x0};
SetWordType zzerr3[4] = {0x80,0x8,0x0,0x0};
SetWordType zzerr4[4] = {0x10,0x38,0x0,0x0};
SetWordType setwd1[15] = {0x0,0x65,0x0,0x4a,0x0,0x0,0x10,
	0x0,0x0,0x0,0x0,0x68,0x80,0x80,0x0};
SetWordType zzerr5[4] = {0x0,0x30,0x0,0x0};
SetWordType setwd2[15] = {0x0,0x0,0x0,0x0,0x0,0x2,0x0,
	0x7,0x0,0x0,0x7,0x0,0x0,0x0,0x0};
