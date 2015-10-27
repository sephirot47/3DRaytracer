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

ANTLRChar *zztokens[18]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"SCENE",
	/* 03 */	"LPAREN",
	/* 04 */	"RPAREN",
	/* 05 */	"LBRACE",
	/* 06 */	"RBRACE",
	/* 07 */	"EQUAL",
	/* 08 */	"COMMA",
	/* 09 */	"ID",
	/* 10 */	"FLOAT",
	/* 11 */	"INT",
	/* 12 */	"SPACE",
	/* 13 */	"CUBE",
	/* 14 */	"SPHERE",
	/* 15 */	"DLIGHT",
	/* 16 */	"PLIGHT",
	/* 17 */	"MATERIAL"
};
SetWordType zzerr1[4] = {0x40,0x2,0x0,0x0};
SetWordType zzerr2[4] = {0x8,0xc,0x0,0x0};
SetWordType zzerr3[4] = {0x0,0xc,0x0,0x0};
SetWordType setwd1[18] = {0x0,0x7,0x0,0x0,0x20,0x0,0x70,
	0x0,0x70,0x6,0x8,0x8,0x0,0x0,0x0,
	0x0,0x0,0x0};
