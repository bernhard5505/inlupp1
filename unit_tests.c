#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

//function from lab 5.5
/*
void test_is_number(void) {
  CU_ASSERT_TRUE(is_number("42"));
  CU_ASSERT_TRUE(is_number("-10"));
  CU_ASSERT_TRUE(is_number("foo"));
  CU_ASSERT_TRUE(is_number(""));
  CU_ASSERT_TRUE(is_number("-"));
  CU_ASSERT_TRUE(is_number("--10"));
  CU_ASSERT_TRUE(is_number("-0"));
  CU_ASSERT_TRUE(is_number("10100101101099993"));

}
*/

void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}
void test_hash_table_insert(ioopm_hash_table_t *ht, int key)
{
  
  ioopm_hash_table_lookup(ht,key);
}

void test_insert_once()
{

  ioopm_hash_table_t *h = ioopm_hash_table_create();
  ioopm_hash_table_lookup(h, 10);
  ioopm_hash_table_insert(h, 10, "val1");
  ioopm_hash_table_insert(h, 10, "val2");
  ioopm_hash_table_lookup(h, 10);
  ioopm_hash_table_destroy(h);
}

void test_lookup()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_lookup(ht, 1);
  ioopm_hash_table_destroy(ht);
}

void test_insert(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  option_t lookup_return_pre = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_EQUAL(lookup_return_pre.success, false);
  CU_ASSERT_PTR_NULL(lookup_return_pre.value);

  ioopm_hash_table_insert(ht, 1, "Test");
  option_t lookup_return_1 = ioopm_hash_table_lookup(ht, 1);
  CU_ASSERT_EQUAL(lookup_return_1.success, true);
  CU_ASSERT_STRING_EQUAL(lookup_return_1.value, "Test");

  ioopm_hash_table_insert(ht, 2, "Another test");
  option_t lookup_return_2 = ioopm_hash_table_lookup(ht, 2);
  CU_ASSERT_EQUAL(lookup_return_2.success, true);
  CU_ASSERT_STRING_EQUAL(lookup_return_2.value, "Another test");

  ioopm_hash_table_insert(ht, 18, "Same bucket test");
  option_t lookup_return_3 = ioopm_hash_table_lookup(ht, 18);
  CU_ASSERT_EQUAL(lookup_return_3.success, true);
  CU_ASSERT_STRING_EQUAL(lookup_return_3.value, "Same bucket test");

  ioopm_hash_table_destroy(ht);
}



int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    //(CU_add_test(my_test_suite, "Basic tests of test_create_destroy", test_create_destroy) == NULL) ||
    //(CU_add_test(my_test_suite, "Basic tests of test insert once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "tests of test insert", test_insert) == NULL) ||
    //(CU_add_test(my_test_suite, "tests of lookup", test_lookup) == NULL) ||
    0

  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 