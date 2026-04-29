/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** filter.c
*/

#include "../../../include/dataframe.h"

static void set_cell(dataframe_t *new, int c, int *nr, void *v)
{
    column_type_t t = new->columns[c]->type;

    if (t == INT) {
        new->columns[c]->data[*nr] = malloc(sizeof(int));
        *(int *)new->columns[c]->data[*nr] = *(int *)v;
    } else if (t == FLOAT) {
        new->columns[c]->data[*nr] = malloc(sizeof(float));
        *(float *)new->columns[c]->data[*nr] = *(float *)v;
    } else {
        new->columns[c]->data[*nr] = strdup((char *)v);
    }
}

static void copy_row_to_filter(dataframe_t *new, dataframe_t *df,
    int r, int *nr)
{
    for (int c = 0; c < df->nb_columns; c++) {
        set_cell(new, c, nr, df->columns[c]->data[r]);
    }
    (*nr)++;
}

static void alloc_filter(dataframe_t *new, dataframe_t *df, int count)
{
    new->nb_rows = count;
    new->nb_columns = df->nb_columns;
    new->columns = malloc(sizeof(column_t *) * (new->nb_columns + 1));
    for (int i = 0; i < df->nb_columns; i++) {
        new->columns[i] = malloc(sizeof(column_t));
        new->columns[i]->title = strdup(df->columns[i]->title);
        new->columns[i]->type = df->columns[i]->type;
        new->columns[i]->data = malloc(sizeof(void *) * count);
    }
    new->columns[new->nb_columns] = NULL;
}

static void fill_filter(dataframe_t *new, dataframe_t *df, int idx,
    bool (*f)(void *))
{
    int nr = 0;

    for (int r = 0; r < df->nb_rows; r++) {
        if (f(df->columns[idx]->data[r]))
            copy_row_to_filter(new, df, r, &nr);
    }
}

dataframe_t *df_filter(dataframe_t *df, const char *col, bool (*f)(void *))
{
    int idx = -1;
    int count = 0;
    dataframe_t *new;

    if (!df || !f)
        return (NULL);
    for (int i = 0; i < df->nb_columns; i++)
        if (strcmp(df->columns[i]->title, col) == 0)
            idx = i;
    if (idx == -1)
        return (NULL);
    for (int r = 0; r < df->nb_rows; r++)
        if (f(df->columns[idx]->data[r]))
            count++;
    new = malloc(sizeof(dataframe_t));
    alloc_filter(new, df, count);
    fill_filter(new, df, idx, f);
    return (new);
}
