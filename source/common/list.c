#include "common/list.h"

#include <stdlib.h>
#include <string.h>

list*
new_list(int datatype_size) {
    list *_list = malloc(sizeof(list));
    _list->_datatype_size = datatype_size;
    _list->_data = malloc(datatype_size * 4);
    _list->capacity = 4;
    _list->size = 0;
    return _list;
}

void
delete_list(list *_list) {
    free(_list->_data);
    _list->_data = NULL;
    _list->capacity = 0;
    _list->size = 0;
    _list->_datatype_size = 0;
    free(_list);
    _list = NULL;
}

void
list_add_item(list *_list, void *element) {
    if(_list->size == _list->capacity) {
        realloc(_list->_data, _list->capacity * 2);
        _list->capacity = _list->capacity * 2;
    }
    _list->_data[0] = element;
    _list->size = _list->size + 1;
}