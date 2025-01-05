#include <criterion/criterion.h>
#include <string.h>
#include "../../../DataStructures/List.h"

List* list;

void setup(void) {
    list = createList();
}

void takedown(void) {
    freeList(list);
}


Test(ListTest, TestListCreation) {
    cr_assert_not_null(list, "createList() should return a non-null pointer.");
    cr_assert_not_null(list->list, "List->list should not be null.");
    cr_assert_null(list->list->head, "The head of the list should be null initially.");
    cr_assert_null(list->list->tail, "The tail of the list should be null initially.");
    cr_assert_eq(list->list->size, 0, "The size of the list should be 0 initially.");
}

Test(ListTest, TestAddingToLeft) {
    LPUSH(list, "element1");
    cr_assert_not_null(list->list->head, "The head should not be null after LPUSH.");
    cr_assert_str_eq(list->list->head->elem, "element1", "The head's element should match the pushed value.");
    cr_assert_eq(list->list->size, 1, "The list size should be 1 after one LPUSH.");
}

Test(ListTest, TestAddingToRight) {
    RPUSH(list, "element1");
    cr_assert_not_null(list->list->tail, "The tail should not be null after RPUSH.");
    cr_assert_str_eq(list->list->tail->elem, "element1", "The tail's element should match the pushed value.");
    cr_assert_eq(list->list->size, 1, "The list size should be 1 after one RPUSH.");
}

Test(ListTest, TestRemovingFromLeft) {
    LPUSH(list, "element1");
    LPUSH(list, "element2");
    char* removed = LPOP(list);
    cr_assert_str_eq(removed, "element2", "LPOP should return the most recently pushed element.");
    cr_assert_eq(list->list->size, 1, "The list size should decrease by 1 after LPOP.");
    free(removed);
}

Test(ListTest, TestRemovingFromRight) {
    RPUSH(list, "element1");
    RPUSH(list, "element2");
    char* removed = RPOP(list);
    cr_assert_str_eq(removed, "element2", "RPOP should return the most recently RPUSHed element.");
    cr_assert_eq(list->list->size, 1, "The list size should decrease by 1 after RPOP.");
    free(removed);
}

Test(ListTest, TestFreeList) {
    LPUSH(list, "element1");
    LPUSH(list, "element2");
    freeList(list);
    cr_assert(true, "freeList() should execute without segmentation faults or memory leaks.");
}


TestSuite(ListTest, .init = setup, .fini = takedown);