/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Head function
*/

#include "../../../include/dataframe.h"

static void *copy_val_node(void *v, column_type_t t)
{
    void *new = NULL;

    if (t == INT || t == UINT || t == BOOL) {
        new = malloc(sizeof(int));
        *(int *)new = *(int *)v;
    } else if (t == FLOAT) {
        new = malloc(sizeof(float));
        *(float *)new = *(float *)v;
    } else {
        new = strdup((char *)v);
    }
    return (new);
}

static void copy_cols(dataframe_t *new, dataframe_t *df, int limit)
{
    for (int c = 0; c < df->nb_columns; c++) {
        new->columns[c] = malloc(sizeof(column_t));
        new->columns[c]->title = strdup(df->columns[c]->title);
        new->columns[c]->type = df->columns[c]->type;
        new->columns[c]->data = malloc(sizeof(void *) * limit);
        for (int r = 0; r < limit; r++) {
            new->columns[c]->data[r] = copy_val_node(df->columns[c]->data[r],
                df->columns[c]->type);
        }
    }
}

dataframe_t *df_head(dataframe_t *df, int n)
{
    int limit;
    dataframe_t *new;

    if (df == NULL)
        return (NULL);
    limit = (n > df->nb_rows) ? df->nb_rows : n;
    new = malloc(sizeof(dataframe_t));
    new->nb_rows = limit;
    new->nb_columns = df->nb_columns;
    new->columns = malloc(sizeof(column_t *) * (new->nb_columns + 1));
    copy_cols(new, df, limit);
    new->columns[new->nb_columns] = NULL;
    return (new);
}
