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

ANTLRChar *zztokens[16]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"MATERIALS",
	/* 03 */	"CAMERA",
	/* 04 */	"SCENE",
	/* 05 */	"LPAREN",
	/* 06 */	"RPAREN",
	/* 07 */	"LBRACE",
	/* 08 */	"RBRACE",
	/* 09 */	"COLON",
	/* 10 */	"EQUAL",
	/* 11 */	"COMMA",
	/* 12 */	"ID",
	/* 13 */	"FLOAT",
	/* 14 */	"INT",
	/* 15 */	"SPACE"
};
SetWordType zzerr1[4] = {0x1c,0x0,0x0,0x0};
SetWordType zzerr2[4] = {0x14,0x0,0x0,0x0};
SetWordType zzerr3[4] = {0x80,0x2,0x0,0x0};
SetWordType zzerr4[4] = {0x0,0x11,0x0,0x0};
SetWordType setwd1[16] = {0x0,0x92,0x5,0x0,0x2d,0x0,0x0,
	0x40,0x0,0x0,0x0,0x0,0xa0,0x0,0x0,
	0x0};
SetWordType zzerr5[4] = {0x20,0x70,0x0,0x0};
SetWordType zzerr6[4] = {0x0,0x60,0x0,0x0};
SetWordType setwd2[16] = {0x0,0x1,0x1,0x0,0x1,0x0,0x8,
	0x0,0x1c,0x0,0x0,0x1c,0x1,0x2,0x2,
	0x0};
