/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_value function
*/

#include "../../../include/dataframe.h"

void *df_get_value(dataframe_t *df, int row, const char *column)
{
    if (!df || row >= df->nb_rows)
        return (NULL);
    for (int i = 0; i < df->nb_columns; i++) {
        if (strcmp(df->columns[i]->title, column) == 0)
            return (df->columns[i]->data[row]);
    }
    return (NULL);
}
