/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** free function
*/

#include "../../../include/dataframe.h"

static void free_column(column_t *col, int rows)
{
    if (!col)
        return;
    for (int r = 0; r < rows; r++)
        free(col->data[r]);
    free(col->data);
    free(col->title);
    free(col);
}

void df_free(dataframe_t *df)
{
    if (!df)
        return;
    for (int i = 0; i < df->nb_columns; i++)
        free_column(df->columns[i], df->nb_rows);
    free(df->columns);
    free(df);
}
