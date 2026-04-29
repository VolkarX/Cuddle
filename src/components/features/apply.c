/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Apply function
*/

#include "../../../include/dataframe.h"

dataframe_t *df_apply(dataframe_t *df, const char *col, void *(*f)(void *))
{
    dataframe_t *new;
    int idx = -1;

    if (df == NULL || col == NULL || f == NULL)
        return (NULL);
    new = df_copy(df);
    if (new == NULL)
        return (NULL);
    for (int i = 0; i < new->nb_columns; i++) {
        if (strcmp(new->columns[i]->title, col) == 0)
            idx = i;
    }
    if (idx == -1) {
        df_free(new);
        return (NULL);
    }
    for (int r = 0; r < new->nb_rows; r++)
        new->columns[idx]->data[r] = f(new->columns[idx]->data[r]);
    return (new);
}
