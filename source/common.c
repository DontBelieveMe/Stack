#include "common.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void 
str_replace(char *str, const char *delim, const char *replace) {
    char *sp;

    if ((sp = strstr(str, delim)) == NULL) {
        return;
    }

    int search_len = strlen(delim);
    int replace_len = strlen(replace);
    int tail_len = strlen(sp + search_len);

    memmove(sp + replace_len, sp + search_len, tail_len + 1);
    memcpy(sp, replace, replace_len);
}

char*
str_trimwhitespace(char *str) {
    char *end;
	while(isspace(*str)) str++;

	if(*str == 0)
		return str;
	end = str + strlen(str) - 1;
	
	while(end > str && isspace(*end)) end--;

	*(end + 1) = 0;
	return str;
}


char*
str_dup(const char *str) {
    size_t len = strlen(str) + 1;
    char *s = malloc(len);
    if (s == NULL)
        return NULL;
    return (char *) memcpy(s, str, len);
}