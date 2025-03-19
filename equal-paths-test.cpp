#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;

Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;
Node* g;
Node* h;
Node* i;

void setNode(Node* n, Node* left=NULL, Node* right=NULL)
{
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
  setNode(a,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
  setNode(b,NULL,NULL);
  setNode(a,b,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
  setNode(c,NULL,NULL);
  setNode(b,NULL,c);
  setNode(a,b,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
  setNode(c,NULL,NULL);
  setNode(a,NULL,c);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test5(const char* msg)
{
  setNode(d,NULL,NULL);
  setNode(b,NULL,d);
  setNode(c,NULL,NULL);
  setNode(a,b,c);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test6(const char* msg)
{
    Node a(1);
    Node b(3);
    Node c(2);
    Node d(8);
    Node e(6);
    Node f(9);
    Node g(5);
    Node h(7);
    Node i(4);
    setNode(&a,NULL,&b);
    setNode(&b,&c,&d);
    setNode(&c,NULL,NULL);
    setNode(&d,&e,&f);
    setNode(&e,&g,&h);
    setNode(&f,NULL,NULL);
    setNode(&g,&i,NULL);
    setNode(&h,NULL,NULL);
    setNode(&i,NULL,NULL);

    cout << msg << ": " << equalPaths(&a) << endl;
}

int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4);

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
  test5("Test5");
  test6("Test6");

 //expected: t, t,t,t, f, f
  delete a;
  delete b;
  delete c;
  delete d;
}
