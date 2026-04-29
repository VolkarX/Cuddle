/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Groupby placeholder (Deep copy)
*/

#include "../../../include/dataframe.h"

dataframe_t *df_groupby(dataframe_t *df, const char *by,
    const char **to, void *(*f)(void **, int))
{
    if (df == NULL || by == NULL || to == NULL || f == NULL)
        return (NULL);
    return (df_copy(df));
}
