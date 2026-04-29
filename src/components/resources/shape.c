/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Tail function
*/

#include "../../../include/dataframe.h"

dataframe_shape_t df_shape(dataframe_t *df)
{
    dataframe_shape_t s = {0, 0};

    if (df) {
        s.nb_rows = df->nb_rows;
        s.nb_columns = df->nb_columns;
    }
    return (s);
}
