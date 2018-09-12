#include "common/list.h"

#include <stdlib.h>
#include <string.h>

error_code
list_new(List **list, int datatype_size) {
    List *new_list = malloc(sizeof(List));

    if(!new_list)
        return BAD_MEMORY_ALLOC;

    new_list->_datatype_size = datatype_size;
    new_list->_data = malloc(datatype_size * 4);

    if(!new_list->_data)
    {
        free(new_list);
        return BAD_MEMORY_ALLOC;
    }

    new_list->capacity = 4;
    new_list->size = 0;

    *list = new_list;

    return OK;
}

error_code
list_delete(List *list) {
    free(list->_data);

    list->_data = NULL;
    list->capacity = 0;
    list->size = 0;
    list->_datatype_size = 0;
    
    free(list);
    list = NULL;

    return OK;
}

error_code
list_add_item(List *list, void *element) {
    if(list->size == list->capacity) {
        list->_data = realloc(list->_data, list->capacity * 2);

        if(!list->_data)
            return BAD_MEMORY_ALLOC;

        list->capacity = list->capacity * 2;
    }

    list->_data[0] = element;
    list->size = list->size + 1;

    return OK;
}