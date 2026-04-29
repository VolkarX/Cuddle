/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_values function
*/

#include "../../../include/dataframe.h"

static void **create_null_terminated_array(column_t *col, int rows)
{
    void **arr = malloc(sizeof(void *) * (rows + 1));

    if (arr == NULL)
        return (NULL);
    for (int i = 0; i < rows; i++)
        arr[i] = col->data[i];
    arr[rows] = NULL;
    return (arr);
}

void **df_get_values(dataframe_t *df, const char *column)
{
    if (df == NULL || column == NULL)
        return (NULL);
    for (int i = 0; i < df->nb_columns; i++) {
        if (strcmp(df->columns[i]->title, column) == 0)
            return (create_null_terminated_array(df->columns[i], df->nb_rows));
    }
    return (NULL);
}
