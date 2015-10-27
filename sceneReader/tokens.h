#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: sceneReader.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define SCENE 2
#define LPAREN 3
#define RPAREN 4
#define LBRACE 5
#define RBRACE 6
#define EQUAL 7
#define COMMA 8
#define ID 9
#define FLOAT 10
#define INT 11
#define SPACE 12
#define CUBE 13
#define SPHERE 14
#define DLIGHT 15
#define PLIGHT 16
#define MATERIAL 17

#ifdef __USE_PROTOS
void program(AST**_root);
#else
extern void program();
#endif

#ifdef __USE_PROTOS
void object(AST**_root);
#else
extern void object();
#endif

#ifdef __USE_PROTOS
void propertyList(AST**_root);
#else
extern void propertyList();
#endif

#ifdef __USE_PROTOS
void property(AST**_root);
#else
extern void property();
#endif

#ifdef __USE_PROTOS
void number(AST**_root);
#else
extern void number();
#endif

#ifdef __USE_PROTOS
void vec3(AST**_root);
#else
extern void vec3();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType zzerr3[];
extern SetWordType setwd1[];
