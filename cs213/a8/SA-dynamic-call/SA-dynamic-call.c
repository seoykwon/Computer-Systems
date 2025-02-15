#include <stdlib.h>
#include <stdio.h>

/*
 * Class A
 public class A {
    void ping () { out.printf ("A.ping %d\n", this.i); }
    void pong () { out.printf ("A.pong %d\n", this.i); }
    int i;
    public A(int i) {
      this.i = i;
    }
  }
 */

//Declaration of Class
struct A_class {
  void *super;
  void (*ping)(void*);
  void (*pong)(void*);
};

//Object template
struct A {
  struct A_class *class;
  int    i;
};

//Declaration of Instance Methods
void A_ping(void *thisv) {
  struct A *this = thisv;
  printf("A_ping %d\n", this->i);
}

void A_pong(void *thisv) {
  struct A *this = thisv;
  printf("A_pong %d\n", this->i);
}

//Static Allocation and Initialization of Class object
struct A_class A_class = {NULL, A_ping, A_pong};

//Constructor Method
struct A *new_A(int i) {
  struct A *obj = malloc(sizeof(struct A));
  obj->class = &A_class;
  obj->i     = i;
  return obj;
}


/*
 * Class B extends A
 */

//the class struct is a super set of A's
struct B_class {
  struct A_class *super;
  void (*ping)(void*);
  void (*pong)(void*);
  void (*wiff)(void*);
};

struct B {
  struct B_class *class;
  int    i;
};

//B's methods
void B_ping(void *thisv) {
  struct B *this = thisv;
  printf ("B_ping %d\n", this->i);
}
void B_wiff(void *thisv) {
  struct B *this = thisv;
  printf ("B_wiff %d\n", this->i);
}

//B's class object
struct B_class B_class = {&A_class, B_ping, A_pong, B_wiff};

struct B *new_B(i) {
  struct B *obj = malloc(sizeof(struct B));
  obj->class = &B_class;
  obj->i = i;
  return obj;
}


/*
 * Class C extends B
 */

struct C_class {
  struct B_class *super;
  void (*ping)(void*);
  void (*pong)(void*);
  void (*wiff)(void*);
};

struct C {
  struct C_class *class;
  int    i;
  int    id;
};

void C_ping(void *thisv) {
  struct C *this = thisv;
  printf("C_ping (%d,%d) calls ", this->i, this->id);
  this->class->super->ping(this);
}

struct C_class C_class = {&B_class, C_ping, A_pong, B_wiff};

struct C *new_C(int i, int id) {
  struct C *obj = malloc(sizeof(struct C));
  obj->class = &C_class;
  obj->i     = i;
  obj->id    = id;
  return obj;
}


/*
 * Main
 */

void foo(void *av) {
  //allocating an instance
  struct A *a = av;
  //calling instance methods
  a->class->ping(a);
  a->class->pong(a);
}

void bar() {
  foo(new_A(10));
  foo(new_B(20));
  foo(new_C(30, 100));
}

int main (int argc, char** argv) {
  bar();
}
