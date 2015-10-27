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
#define SPHERE 3
#define CUBE 4
#define LPAREN 5
#define RPAREN 6
#define COMMA 7
#define ID 8
#define FLOAT 9
#define INT 10
#define SPACE 11

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
void primitive(AST**_root);
#else
extern void primitive();
#endif

#ifdef __USE_PROTOS
void cube(AST**_root);
#else
extern void cube();
#endif

#ifdef __USE_PROTOS
void sphere(AST**_root);
#else
extern void sphere();
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
extern SetWordType setwd1[];
