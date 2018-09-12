#ifndef _LIST_
#define _LIST_

#include "../stack.h"

#define NEW_LIST(T) \
    new_list(sizeof(T))

#define LIST_ADD_ITEM(LIST, T, ITEM) \
    {T _i = ITEM; \
    list_add_item(LIST, &_i); }

#define LIST_GET_AT(LIST, T, IDX) \
    *((T*)LIST->_data[IDX])

typedef struct _List {
    void **_data;
    int   _datatype_size;
    int   size;
    int   capacity;
} List;

error_code list_new        (List **list, int datatype_size);
error_code list_delete     (List *list);
error_code list_add_item   (List *list, void *element);
error_code list_remove_item(List *list, int index);

#endif