#ifndef _LIST_
#define _LIST_

#define NEW_LIST(T) \
    new_list(sizeof(T))

#define LIST_ADD_ITEM(LIST, T, ITEM) \
    {T _i = ITEM; \
    list_add_item(LIST, &_i); }

#define LIST_GET_AT(LIST, T, IDX) \
    *((T*)LIST->_data[IDX])

typedef struct _list {
    void **_data;
    int   _datatype_size;
    int   size;
    int   capacity;
} list;

list *new_list(int datatype_size);
void delete_list(list *_list);
void list_add_item(list *_list, void *element);

void list_remove_item(list *_list, int index);

#endif