#header
<<
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

typedef std::tuple<int, int, int> i3tuple;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr,  int type,  char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as, attr, ttype, textt) as=createASTnode(attr, ttype, textt)
AST* createASTnode(Attrib* attr, int ttype,  char *textt);
>>

<<
#include <cstdlib>
#include <cmath>

//global structures: AST
AST *root;

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

//get nth child of a tree. Count starts at 0.
//if no such child,  returns NULL
AST* child(AST *a, int n) 
{
  AST *c=a->down;
  for (int i = 0; c != NULL && i < n; i++ ) c = c->right;
  return c;
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

int main() 
{
  root = NULL;
  ANTLR(program(&root),  stdin);
  ASTPrint(root);
}
>>

//////////////

#lexclass START

#token SCENE "SCENE"

#token SPHERE "Sphere"
#token CUBE "Cube"

//General stuff
  #token LPAREN "\("
  #token RPAREN "\)"
  #token COMMA ","
  #token ID "[a-zA-Z]"
  #token FLOAT "[0-9]+.[0-9]+"
  #token INT "[0-9]+"
  #token SPACE "[\ \n]" << zzskip();>>
//


/////////////
program: SCENE^ (object)*;

object: primitive;
  primitive: (cube | sphere);
    cube: CUBE^ vec3 vec3;
    sphere: SPHERE^ vec3 number;
    
    
number: (FLOAT | INT);
vec3: LPAREN^ number COMMA! number COMMA! number RPAREN!;






