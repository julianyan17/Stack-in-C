#include "cutest/CuTest.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


// Tests for integer equals
void TestOne(CuTest *tc) {
  int two = 2;
  int four = 4;
  CuAssertIntEquals(tc, four, two+two);
}

// Test for string equals
void TestTwo(CuTest *tc) {
  char* lol = "lol";
  char* alsoLol = "lol";
  CuAssertStrEquals(tc, lol, alsoLol);
}

/*
Tests for True and False
pay attention to cleanStack function call as
you will be using it in your every test case
*/
void TestTrueFalse(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertTrue(tc, isEmpty(s));
  push(s, 1, "black");
  CuAssertIntEquals(tc, s->top, 1);
  CuAssertFalse(tc, isEmpty(s));
  cleanStack(s);
}


// Tests for Pointer equals
void TestPtrEquals(CuTest *tc) {
  Element* e = NULL;
  CuAssertPtrEquals(tc, NULL, e);
}

// Tests for push and pop
void TestPushPop(CuTest *tc) {
    Stack* s = makeStack(10);
    CuAssertTrue(tc, isEmpty(s));
    push(s, 1, "black");
    CuAssertFalse(tc, isEmpty(s));
    Element* popElement = pop(s);
    CuAssertIntEquals(tc, popElement->key, 1);
    CuAssertStrEquals(tc, popElement->value,"black");
    CuAssertTrue(tc, isEmpty(s));
    cleanStack(s);
}

// Test pushUnique
void TestPushUniqueFalse(CuTest *tc) {
    Stack* s = makeStack(10);
    CuAssertTrue(tc, isEmpty(s));
    push(s, 1, "black");
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, pushUnique(s,1,"black"));
    cleanStack(s);
}

// Test pushUnique
void TestPushUniqueFull(CuTest *tc) {
    Stack* s = makeStack(1);
    CuAssertTrue(tc, isEmpty(s));
    push(s, 1, "black");
    CuAssertFalse(tc, isEmpty(s));
    CuAssertTrue(tc, isFull(s));
    cleanStack(s);
}

// Test getCapacity
void TestGetCapacity(CuTest *tc) {
    Stack* s = makeStack(10);
    CuAssertTrue(tc, isEmpty(s));
    CuAssertIntEquals(tc, getCapacity(s), 10);
}

// Test pushFull
void TestPushFull(CuTest *tc) {
    Stack* s = makeStack(1);
    CuAssertTrue(tc, isEmpty(s));
    push(s, 1, "black");
    CuAssertFalse(tc, isEmpty(s));
    CuAssertTrue(tc, isFull(s));
    CuAssertFalse(tc, push(s,2,"red"));
    cleanStack(s);
}

// Test pushFullGrow
void TestPushFullGrow(CuTest *tc) {
    Stack* s = makeStackG(1,1.0f);
    CuAssertTrue(tc, isEmpty(s));
    push(s, 1, "black");
    CuAssertFalse(tc, isEmpty(s));
    CuAssertTrue(tc, isFull(s));
    CuAssertTrue(tc, push(s,2,"red"));
    CuAssertIntEquals(tc, currentSize(s),2);
    cleanStack(s);
}

// Test pushLoadFactorEqual
void TestPushLoadFactorEqual(CuTest *tc) {
    Stack* s = makeStackG(10,0.5f);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, isFull(s));
    CuAssertIntEquals(tc, getCapacity(s),20);
    cleanStack(s);
}

// Test pushLoadFactor
void TestPushLoadFactor(CuTest *tc) {
    Stack* s = makeStackG(10,0.5f);
    for(int i = 0; i < 7; i++) {
        push(s,i,"red");
    }
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, isFull(s));
    CuAssertIntEquals(tc, getCapacity(s),20);
    cleanStack(s);
}

// Test popShrinkFactor
void TestPopShrinkFactor(CuTest *tc) {
    Stack* s = makeStackGnS(6,0,0.5f);
    for(int i = 0; i < 2; i++) {
        push(s,i,"red");
    }
    Element* popElement = pop(s);
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, isFull(s));
    CuAssertIntEquals(tc,popElement->key, 1);
    CuAssertStrEquals(tc,popElement->value,"red");
    CuAssertIntEquals(tc, getCapacity(s),3);
    CuAssertIntEquals(tc, currentSize(s),1);
    cleanStack(s);
}

// Test popShrinkFactorEqual
void TestPopShrinkFactorEqual(CuTest *tc) {
    Stack* s = makeStackGnS(6,0,0.5f);
    for(int i = 0; i < 3; i++) {
        push(s,i,"red");
    }
    Element* popElement = pop(s);
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, isFull(s));
    CuAssertIntEquals(tc,popElement->key, 2);
    CuAssertStrEquals(tc,popElement->value,"red");
    CuAssertIntEquals(tc, getCapacity(s),3);
    CuAssertIntEquals(tc, currentSize(s),2);
    cleanStack(s);
}

// Test popOddShrinkFactor
void TestPopOddShrinkFactor(CuTest *tc) {
    Stack* s = makeStackGnS(7,0,0.5f);
    for(int i = 0; i < 3; i++) {
        push(s,i,"red");
    }
    Element* popElement = pop(s);
    CuAssertFalse(tc, isEmpty(s));
    CuAssertFalse(tc, isFull(s));
    CuAssertIntEquals(tc,popElement->key, 2);
    CuAssertStrEquals(tc,popElement->value,"red");
    CuAssertIntEquals(tc, getCapacity(s),3);
    CuAssertIntEquals(tc, currentSize(s),2);
    cleanStack(s);
}

// Test peekEmpty
void TestPeekEmpty(CuTest *tc) {
    Stack* s = makeStack(1);
    CuAssertTrue(tc, NULL == peek(s));
    cleanStack(s);
}

// Test peek
void TestPeek(CuTest *tc) {
    Stack* s = makeStack(1);
    push(s,1,"red");
    Element* peekedElement = peek(s);
    CuAssertIntEquals(tc,peekedElement->key, 1);
    CuAssertStrEquals(tc,peekedElement->value,"red");
    CuAssertIntEquals(tc, currentSize(s),1);
    cleanStack(s);
}

// Test clear
void TestClear(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    clear(s);
    CuAssertTrue(tc,isEmpty(s));
    cleanStack(s);
}

// Test multiPop
void TestMultiPop(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    Element** multiPopped = multiPop(s,3);
    CuAssertFalse(tc,isEmpty(s));
    CuAssertIntEquals(tc,currentSize(s),3);
    Element* peekedElement = peek(s);
    CuAssertIntEquals(tc,peekedElement->key, 2);
    CuAssertStrEquals(tc,peekedElement->value,"red");
    free(multiPopped);
    cleanStack(s);
}

// Test multiPopBig
void TestMultiPopBig(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    Element** multiPopped = multiPop(s,7);
    CuAssertTrue(tc,isEmpty(s));
    free(multiPopped);
    cleanStack(s);
}

// Test multiPopExact
void TestMultiPopExact(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    Element** multiPopped = multiPop(s,6);
    CuAssertTrue(tc,isEmpty(s));
    free(multiPopped);
    cleanStack(s);
}

// Test searchTop
void TestSearchTop(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    int searched = search(s,5,"red");
    CuAssertIntEquals(tc,searched,1);
    cleanStack(s);
}

// Test searchExist
void TestSearchExist(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    int searched = search(s,2,"red");
    CuAssertIntEquals(tc,searched,4);
    cleanStack(s);
}

// Test searchNotExist
void TestSearchNotExist(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    int searched = search(s,7,"red");
    CuAssertIntEquals(tc,searched,-1);
    cleanStack(s);
}

// Test reverse
void TestReverse(CuTest *tc) {
    Stack* s = makeStack(10);
    for(int i = 0; i < 6; i++) {
        push(s,i,"red");
    }
    reverse(s);
    Element* peekedElement = peek(s);
    CuAssertIntEquals(tc,peekedElement->key, 0);
    CuAssertStrEquals(tc,peekedElement->value,"red");
    cleanStack(s);
}

void TestClearPush(CuTest *tc) {
    Stack* s = makeStack(10);
    push(s,1,"red");
    clear(s);
    push(s,2,"red");
    Element* peekedElement = peek(s);
    CuAssertIntEquals(tc,peekedElement->key, 2);
    CuAssertStrEquals(tc,peekedElement->value,"red");
    CuAssertIntEquals(tc, currentSize(s),1);
    cleanStack(s);
}

void TestGrowAndShrink(CuTest *tc) {
    Stack* s = makeStackGnS(10,0.7f,0.5f);
    for(int i = 0; i < 8; i++) {
        push(s,i,"red");
    }
    CuAssertFalse(tc,isEmpty(s));
    CuAssertIntEquals(tc,currentSize(s),8);
    CuAssertIntEquals(tc, getCapacity(s),20);
    Element* returned = pop(s);
    CuAssertIntEquals(tc,currentSize(s),7);
    CuAssertIntEquals(tc, getCapacity(s),10);
    free(returned);
    push(s,2,"red");
    CuAssertIntEquals(tc,currentSize(s),8);
    CuAssertIntEquals(tc, getCapacity(s),20);
    cleanStack(s);
}

void TestFreePop(CuTest *tc) {
    Stack* s = makeStack(5);
    for(int i = 0; i < 4; i++) {
        push(s,i,"red");
    }
    pop(s);
    cleanStack(s);
}

CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  /** ADD YOUR TESTS HERE **/
  SUITE_ADD_TEST(suite, TestOne);
  SUITE_ADD_TEST(suite, TestTwo);
  SUITE_ADD_TEST(suite, TestTrueFalse);
  SUITE_ADD_TEST(suite, TestPtrEquals);
  SUITE_ADD_TEST(suite, TestPushPop);
  SUITE_ADD_TEST(suite, TestPushFull);
  SUITE_ADD_TEST(suite, TestPushFullGrow);

  SUITE_ADD_TEST(suite, TestPushUniqueFalse);
  SUITE_ADD_TEST(suite, TestPushUniqueFull);
  SUITE_ADD_TEST(suite, TestPushLoadFactorEqual);
  SUITE_ADD_TEST(suite, TestPushLoadFactor);
  SUITE_ADD_TEST(suite, TestPopShrinkFactor);
  SUITE_ADD_TEST(suite, TestPopShrinkFactorEqual);
  SUITE_ADD_TEST(suite, TestPopOddShrinkFactor);
  SUITE_ADD_TEST(suite, TestPeekEmpty);
  SUITE_ADD_TEST(suite, TestPeek);
  SUITE_ADD_TEST(suite, TestClear);
  SUITE_ADD_TEST(suite, TestMultiPop);
  SUITE_ADD_TEST(suite, TestMultiPopBig);
  SUITE_ADD_TEST(suite, TestMultiPopExact);
  SUITE_ADD_TEST(suite, TestSearchTop);  
  SUITE_ADD_TEST(suite, TestSearchExist);
  SUITE_ADD_TEST(suite, TestSearchNotExist);
  SUITE_ADD_TEST(suite, TestReverse);
  SUITE_ADD_TEST(suite, TestClearPush);
  SUITE_ADD_TEST(suite, TestGrowAndShrink);
  SUITE_ADD_TEST(suite, TestFreePop);

  return suite;
}

// Don't edit anything below this line

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();

  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}
