/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** copy.c
*/

#include "../../../include/dataframe.h"

static void *copy_val(void *val, column_type_t type)
{
    void *new = NULL;

    if (type == INT) {
        new = malloc(sizeof(int));
        *(int *)new = *(int *)val;
    } else if (type == FLOAT) {
        new = malloc(sizeof(float));
        *(float *)new = *(float *)val;
    } else {
        new = strdup((char *)val);
    }
    return (new);
}

dataframe_t *df_copy(dataframe_t *df)
{
    dataframe_t *new = malloc(sizeof(dataframe_t));

    if (df == NULL)
        return (NULL);
    if (new == NULL)
        return (NULL);
    new->nb_rows = df->nb_rows;
    new->nb_columns = df->nb_columns;
    new->columns = malloc(sizeof(column_t *) * (new->nb_columns + 1));
    for (int i = 0; i < df->nb_columns; i++) {
        new->columns[i] = malloc(sizeof(column_t));
        new->columns[i]->title = strdup(df->columns[i]->title);
        new->columns[i]->type = df->columns[i]->type;
        new->columns[i]->data = malloc(sizeof(void *) * df->nb_rows);
        for (int r = 0; r < df->nb_rows; r++)
            new->columns[i]->data[r] = copy_val(df->columns[i]->data[r],
                df->columns[i]->type);
    }
    new->columns[new->nb_columns] = NULL;
    return (new);
}
