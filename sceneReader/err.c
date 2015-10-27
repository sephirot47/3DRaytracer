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
#include "../include/Scene.h"
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

ANTLRChar *zztokens[12]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"SCENE",
	/* 03 */	"SPHERE",
	/* 04 */	"CUBE",
	/* 05 */	"LPAREN",
	/* 06 */	"RPAREN",
	/* 07 */	"COMMA",
	/* 08 */	"ID",
	/* 09 */	"FLOAT",
	/* 10 */	"INT",
	/* 11 */	"SPACE"
};
SetWordType zzerr1[4] = {0x18,0x0,0x0,0x0};
SetWordType zzerr2[4] = {0x0,0x6,0x0,0x0};
SetWordType setwd1[12] = {0x0,0xfe,0x0,0xfd,0xfd,0x80,0x40,
	0x40,0x0,0x80,0x80,0x0};
