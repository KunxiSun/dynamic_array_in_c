#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include "../../src/withoutlock/dynamic-array.c"

int setup(void** state){
    struct dynamic_array* ary = dynamic_array_new(10);
    assert_non_null(ary);
    *state = ary;
    return 0;
}

int teardown(void** state){
    dynamic_array_destroy(*state);
    return 0;
}

/*
    add 1 test
*/
void add1(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value = "value1";
    dynamic_array_add(ary,value);
    char* res = (char*)dynamic_array_get(ary,0);

    //assert
    assert_true(strcmp(res, value)==0);
}

/*
    add more than 1 test
*/
void add2(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value0 = "value0";
    char* value1 = "value1";
    char* value2 = "value2";
    char* value3 = "value3";
    char* value4 = "value4";

    dynamic_array_add(ary,value0);
    dynamic_array_add(ary,value1);
    dynamic_array_add(ary,value2);
    dynamic_array_add(ary,value3);
    dynamic_array_add(ary,value4);

    char* res0 = (char*)dynamic_array_get(ary,0);
    char* res1 = (char*)dynamic_array_get(ary,1);
    char* res2 = (char*)dynamic_array_get(ary,2);
    char* res3 = (char*)dynamic_array_get(ary,3);
    char* res4 = (char*)dynamic_array_get(ary,4);

    //assert
    assert_true(strcmp(res0, value0)==0);
    assert_true(strcmp(res1, value1)==0);
    assert_true(strcmp(res2, value2)==0);
    assert_true(strcmp(res3, value3)==0);
    assert_true(strcmp(res4, value4)==0);
}

/*
    resize test
*/
void add3(void** state) {
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value0 = "value0";
    char* value1 = "value1";
    char* value2 = "value2";
    char* value3 = "value3";
    char* value4 = "value4";
    char* value5 = "value5";
    char* value6 = "value6";
    char* value7 = "value7";
    char* value8 = "value8";
    char* value9 = "value9";
    char* value10 = "value10";


    dynamic_array_add(ary,value0);
    dynamic_array_add(ary,value1);
    dynamic_array_add(ary,value2);
    dynamic_array_add(ary,value3);
    dynamic_array_add(ary,value4);
    dynamic_array_add(ary,value5);
    dynamic_array_add(ary,value6);
    dynamic_array_add(ary,value7);
    dynamic_array_add(ary,value8);
    dynamic_array_add(ary,value9);
    dynamic_array_add(ary,value10);


    char* res0 = (char*)dynamic_array_get(ary,0);
    char* res1 = (char*)dynamic_array_get(ary,1);
    char* res2 = (char*)dynamic_array_get(ary,2);
    char* res3 = (char*)dynamic_array_get(ary,3);
    char* res4 = (char*)dynamic_array_get(ary,4);
    char* res5 = (char*)dynamic_array_get(ary,5);
    char* res6 = (char*)dynamic_array_get(ary,6);
    char* res7 = (char*)dynamic_array_get(ary,7);
    char* res8 = (char*)dynamic_array_get(ary,8);
    char* res9 = (char*)dynamic_array_get(ary,9);
    char* res10 = (char*)dynamic_array_get(ary,10);

    //assert
    assert_true(strcmp(res0, value0)==0);
    assert_true(strcmp(res1, value1)==0);
    assert_true(strcmp(res2, value2)==0);
    assert_true(strcmp(res3, value3)==0);
    assert_true(strcmp(res4, value4)==0);
    assert_true(strcmp(res5, value5)==0);
    assert_true(strcmp(res6, value6)==0);
    assert_true(strcmp(res7, value7)==0);
    assert_true(strcmp(res8, value8)==0);
    assert_true(strcmp(res9, value9)==0);
    assert_true(strcmp(res10, value10)==0);
}

/*
    remove the first, and the rest will move forward
*/
void remove1(void** state){
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value0 = "value0";
    char* value1 = "value1";
    char* value2 = "value2";
    char* value3 = "value3";
    char* value4 = "value4";

    dynamic_array_add(ary,value0);
    dynamic_array_add(ary,value1);
    dynamic_array_add(ary,value2);
    dynamic_array_add(ary,value3);
    dynamic_array_add(ary,value4);

    dynamic_array_get(ary,0);
    dynamic_array_get(ary,1);
    dynamic_array_get(ary,2);
    dynamic_array_get(ary,3);
    dynamic_array_get(ary,4);

    char* remove0 = (char*)dynamic_array_remove(ary,0);
    assert_true(strcmp(remove0, value0)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,0), value1)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,1), value2)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,2), value3)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,3), value4)==0);
}

/*
    remove the last, and nothing happen with other
*/
void remove2(void** state){
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value0 = "value0";
    char* value1 = "value1";
    char* value2 = "value2";
    char* value3 = "value3";
    char* value4 = "value4";

    dynamic_array_add(ary,value0);
    dynamic_array_add(ary,value1);
    dynamic_array_add(ary,value2);
    dynamic_array_add(ary,value3);
    dynamic_array_add(ary,value4);

    dynamic_array_get(ary,0);
    dynamic_array_get(ary,1);
    dynamic_array_get(ary,2);
    dynamic_array_get(ary,3);
    dynamic_array_get(ary,4);

    char* remove4 = (char*)dynamic_array_remove(ary,4);

    assert_true(strcmp(remove4, value4)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,0), value0)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,1), value1)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,2), value2)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,3), value3)==0);
}

/*remove and then add*/
void add_remove1(void** state){
    //get ary from setup
    struct dynamic_array* ary = *state;

    char* value0 = "value0";
    char* value1 = "value1";
    char* value2 = "value2";
    char* value3 = "value3";
    char* value4 = "value4";

    dynamic_array_add(ary,value0);
    dynamic_array_add(ary,value1);
    dynamic_array_add(ary,value2);
    dynamic_array_add(ary,value3);
    dynamic_array_add(ary,value4);

    dynamic_array_get(ary,0);
    dynamic_array_get(ary,1);
    dynamic_array_get(ary,2);
    dynamic_array_get(ary,3);
    dynamic_array_get(ary,4);

    char* remove4 = (char*)dynamic_array_remove(ary,4);

    assert_true(strcmp(remove4, value4)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,0), value0)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,1), value1)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,2), value2)==0);
    assert_true(strcmp((char*)dynamic_array_get(ary,3), value3)==0);

    char* value5 = "value5";
    dynamic_array_add(ary,value5);
    assert_true(strcmp((char*)dynamic_array_get(ary,4), value5)==0);
}

int main() {
    
    struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(add1,setup,teardown),
        cmocka_unit_test_setup_teardown(add2,setup,teardown),
        cmocka_unit_test_setup_teardown(add3,setup,teardown),
        cmocka_unit_test_setup_teardown(remove1,setup,teardown),
        cmocka_unit_test_setup_teardown(remove2,setup,teardown),
        cmocka_unit_test_setup_teardown(add_remove1,setup,teardown)
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}