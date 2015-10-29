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
#define MATERIALS 2
#define SCENE 3
#define LPAREN 4
#define RPAREN 5
#define LBRACE 6
#define RBRACE 7
#define COLON 8
#define EQUAL 9
#define COMMA 10
#define ID 11
#define FLOAT 12
#define INT 13
#define SPACE 14

#ifdef __USE_PROTOS
void program(AST**_root);
#else
extern void program();
#endif

#ifdef __USE_PROTOS
void materials(AST**_root);
#else
extern void materials();
#endif

#ifdef __USE_PROTOS
void scene(AST**_root);
#else
extern void scene();
#endif

#ifdef __USE_PROTOS
void material(AST**_root);
#else
extern void material();
#endif

#ifdef __USE_PROTOS
void inheritance(AST**_root);
#else
extern void inheritance();
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
extern SetWordType zzerr4[];
extern SetWordType setwd1[];
extern SetWordType zzerr5[];
extern SetWordType setwd2[];
