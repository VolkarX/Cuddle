/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** type_detector.c
*/

#include "../../include/dataframe.h"

static column_type_t get_numeric(char *str)
{
    int dots = 0;
    int i = (str[0] == '-') ? 1 : 0;

    if (str[i] == '\0')
        return (STRING);
    for (; str[i]; i++) {
        if (str[i] == '.') {
            dots++;
            continue;
        }
        if (!isdigit(str[i]))
            return (STRING);
    }
    if (dots == 1)
        return (FLOAT);
    if (dots == 0)
        return (str[0] == '-' ? INT : UINT);
    return (STRING);
}

column_type_t detect_type(char *str)
{
    if (str == NULL || *str == '\0')
        return (UNDEFINED);
    if (strcasecmp(str, "true") == 0 || strcasecmp(str, "false") == 0)
        return (BOOL);
    return (get_numeric(str));
}
