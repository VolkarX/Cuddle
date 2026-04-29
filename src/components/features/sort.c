/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Sorting function
*/

#include "../../../include/dataframe.h"

static void swap_rows(dataframe_t *df, int r1, int r2)
{
    void *tmp;

    for (int c = 0; c < df->nb_columns; c++) {
        tmp = df->columns[c]->data[r1];
        df->columns[c]->data[r1] = df->columns[c]->data[r2];
        df->columns[c]->data[r2] = tmp;
    }
}

static void check_and_swap(dataframe_t *new, int idx, int j,
    bool (*f)(void *, void *))
{
    if (f(new->columns[idx]->data[j], new->columns[idx]->data[j + 1]))
        swap_rows(new, j, j + 1);
}

static void do_sort(dataframe_t *new, int idx, bool (*f)(void *, void *))
{
    for (int i = 0; i < new->nb_rows - 1; i++) {
        for (int j = 0; j < new->nb_rows - i - 1; j++) {
            check_and_swap(new, idx, j, f);
        }
    }
}

dataframe_t *df_sort(dataframe_t *df, const char *col,
    bool (*f)(void *, void *))
{
    int idx = -1;
    dataframe_t *new;

    if (df == NULL || f == NULL)
        return (NULL);
    new = df_copy(df);
    for (int i = 0; i < new->nb_columns; i++) {
        if (strcmp(new->columns[i]->title, col) == 0)
            idx = i;
    }
    if (idx != -1)
        do_sort(new, idx, f);
    return (new);
}
