#include <string.h>
#include <criterion/criterion.h>
#include "../../../DataStructures/Hashmap.h"
#define DEFAULT_BUCKET_COUNT 256

Hashmap *map;

void setup(void)
{
    map = createHashmap(DEFAULT_BUCKET_COUNT);
}

void takedown(void)
{
    freeHashmap(map);
}

Test(HashmapTest, TestCreateHashmap)
{
    cr_assert_not_null(map);
    cr_assert_eq(map->size, 0);
    cr_assert_eq(map->bucket_count, DEFAULT_BUCKET_COUNT);
}

Test(HashmapTest, TestInsertion)
{
    int result = insert(map, "key", "value");
    cr_assert_eq(result, 1);
    cr_assert_eq(map->size, 1);
    cr_assert_str_eq(get(map, "key"), "value");
}

Test(HashmapTest, TestDuplicateKeys)
{
    insert(map, "key1", "value1");
    int result = insert(map, "key1", "value2");
    cr_assert_eq(result, 1);
    cr_assert_eq(map->size, 1);
    cr_assert_str_eq(get(map, "key1"), "value2");
}

Test(HashmapTest, TestRetrieval)
{
    insert(map, "key1", "value1");
    insert(map, "key2", "value2");
    insert(map, "key3", "value3");
    cr_assert_str_eq(get(map, "key1"), "value1");
    cr_assert_str_eq(get(map, "key2"), "value2");
    cr_assert_str_eq(get(map, "key3"), "value3");
}

Test(HashmapTest, TestNonexistientKeyRetrieval)
{
    insert(map, "key1", "value1");
    cr_assert_null(get(map, "key2"));
}

Test(HashmapTest, TestExists)
{
    insert(map, "key1", "value1");
    cr_assert_eq(exists(map, "key1"), 1);
}

Test(HashmapTest, TestNonexistientKey)
{
    cr_assert_eq(exists(map, "key1"), 0);
}

Test(HashmapTest, TestDeletion)
{
    insert(map, "key1", "value1");
    cr_assert_eq(deleteKey(map, "key1"), 1);
    cr_assert_eq(map->size, 0);
}

Test(HashmapTest, TestNonexistientDeletion)
{
    insert(map, "key2", "value2");
    cr_assert_eq(deleteKey(map, "key1"), -1);
}

TestSuite(HashmapTest, .init = setup, .fini = takedown);
