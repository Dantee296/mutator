
/*first line intentionally left blank*/
/*********************************************************************************************************************/
/*inclusion directives*/
#include "testFuncs2.h"
#if 0
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <time.h>
#endif
/*********************************************************************************************************************/
/*macro and definitions*/
typedef const* INTPTR;
/*clang wont let it through*/
#if 0
typedef int dummytypedef;
#endif

#if 0
/*clang wont let it through*/
/*for 5.3*/
typedef gaga incompletearr1;
#endif

#define XMACRO Y

#define ABSOLUTE(X) (((X) >= 0) ? (X) : -(X))
#define ABSOLUTE2(X) ((X >= 0) ? X : -X)
#define ABSOLUTE3(XMACRO) (((XMACRO) <= 0) ? (XMACRO) : -(XMACRO))
#define MINUS(X,Y) ((X) - (Y))
#define PRINT(bubba) printf(#bubba "%d\n", bubba)
#define LOCO i##nt
#define LOCO2 #LOCO2
#define LOCO3(bubba) printf(#bubba "%d\n", bu##bba)
#define DEFINEVAR(X,Y) int X##Y
#define PI 3.14
#define PI2 (a)

#define __FILE__
#define __DATE__
#define __TIME__
#undef __STDC__
#undef __FILE__

#define int int
#undef int

#if defined PI2
#endif

#if 0
#if defined LOCO2
#endif
#endif

#if defined LOCOLUPO
#endif

#if defined LOCO
#endif

#if defined(LOCO)
#endif

#define DEFINED defined
#if DEFINED(X)
#endif

#if defined LOCOLUPO || LOCO
#endif


#define LOCOLUPO
#if 1
#undef LOCOLUPO
#endif
/*********************************************************************************************************************/
/*Globals*/
int incompletearr1[];
int incompletearr2[];

int dudu;
int bubu;
int fufu;
double badboy = 0.0;

int incompletearr1[10];

union u3;
union u4;

union u3
{
  int ua;
  char ub;
};

union yizzy
{
  int ua;
  char ub;
};

double yizzy;

double u3;
double ua;

int s10;

struct s10;
struct s11;

struct s10
{
  int sa[10];
  char sb;
  int sc;
};

/*********************************************************************************************************************/
/*functions go here.*/
static void test33(void)
{

  short int a;
  long int b;
  int sum;

  sum = dudu + bubu + fufu;

  MINUS(a, b);
  //MINUS(a);

  b = (int)a;
}

void testfunc1(void)
{
  unsigned char a;
  unsigned char b;
  char c;
  int sum;

  sum = sum + dudu + fufu;

  b =  a;
  c = 123;
  c = 'c';
  c = "c";
  c = '\n';

  ;;;;
  ;/*comment*/
  ; /*comment*/

  c = '5';
}

#if CRAZYMACRO < 0
#endif

testfunc2(void)
{
  int a;
  int b;
  int sum;

  sum = a + b + dudu;
}

void testfunc3()
{
  int a;
  int b;
  int c;

#define LUPO wolf

#if 1
  int abcdefghijklmnopqrstuvwxyz1234567890;
  int abcdefghijklmnopqrstuvwxyz12345678902;
#endif

  /*do stuff*/
}

int testfunc6(void)
{
  int a;
  int b;
  //return ();
}

int testfunc7(void)
{
  int a;
  int b;
  //return;
}

int testfunc8(void)
{
  int a[10];
  int b[10];

  int* p;

  p = &a[0];

#undef LUPO

  int i;
  int sum;
  int sum2;
  int garbage;
  int garbage2;

  for (i = 0; i < 10; ++i)
  {
    sum += *(a + i);
    sum2 += *(p + i);
    //garbage = *(a - b);
  }

  for (i = 10; i < 1; i++)
  {
    sum += *(a - i);
    sum2 += *(p - i);
    //garbage2 = *(p - a);
  }
}

void testfunc9(void)
{
  int** p1;
  int*** p2;

  int* pointer1;
  double d2;

  pointer1 = &d2;

  struct
  {
    int* sp1;
    int** sp2;
    int*** sp3;
  };

  struct s* ps1;
  /*these two should not be tagged by 18.1 since they are pointers(to pointers) to an incomplete type. the pointer itself is a complete type.*/
  struct s** ps2;
  struct s*** ps3;

  INTPTR *const* const fedupp1;

  int ** (*pfunc1)();
  int crazycast1 = (int)pfunc1;
  int crazycast2;
  pfunc1 = (int ** (*)())crazycast2;
  int ** (**pfunc2)();
  pfunc2 = pfunc1;
  pfunc2 = (int ** (*)())pfunc1;
  int ** (***pfunc3)();
  int *** (**pfunc4)();
  int ** (**pfunc5)(int**, int**);
  int ** (**pfunc6)(int**, int***);
}

void testfunc10 (int ** (**p5)(int**, int**), int ** (**p6)(int**, int***))
{

}

void testfunc11(void)
{
  long int a;
  double dd;
  short unsigned int b;
  short int* p1;
  long int* p2;

  p2 = (long int*)p1;
  p1 = (short int*)p2;
  b = a;
  dd = b;
}

void testfunc12(void)
{
  const char* stringlit = "date should be in the form ??-??-??";

  short int port = 0x5aU;
  short int resultshort;
  int resultlong;
  int mode;
  resultshort = (~port) >> 4;
  resultshort = ((short int)(~port)) >> 4;
  /*should not be tagged by 10.1\2*/
  resultlong = ((int)(~(int)port)) >> 4;

  resultlong = ((port << 4) & mode) >> 6;
  resultlong = ((int)((int)port << 4) & mode) >> 6;
}

/*the test are from the misrac doc for 11.5*/
void testfunc13(void)
{
  int x;
  int * const cpi = &x; /* const pointer */
  int * const * pcpi; /* pointer to const pointer */
  const int * * ppci; /* pointer to pointer to const */
  int * * ppi;
  const int * pci; /* pointer to const */
  volatile int * pvi; /* pointer to volatile */
  int * pi;
  pi = cpi; /* Compliant - no conversion
no cast required */
  pi = (int *)pci; /* Not compliant */
  pi = (int *)pvi; /* Not compliant */
  ppi = (int * *)pcpi; /* Not compliant */
  ppi = (int * *)ppci; /* Not compliant */
}

void testfunc14(void)
{
  char a;
  long int b;
  long int b2;
  double c;
  float d;
  long double e;
  a = (int)b;
  a = (int)(b + b2);
  a = b + b2;
  a = b++;
  if ((int)(b + b2))
  {
    /*something*/
  }

  a = c;
  c = b;
  d = c;
  d = e;
}

void testfunc15 (void)
{
  int a[10];

  a[1] = 041;
  a[2] = 052;
}

/*********************************************************************************************************************/
/*last line intentionally left blank.*/
