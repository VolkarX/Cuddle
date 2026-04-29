/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Main file
*/

#include "./include/dataframe.h"

/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Main file
*/

#include "./include/dataframe.h"

int cmp_int_asc(void *a, void *b)
{
    return (*(int *)a - *(int *)b);
}

int main(void)
{
    dataframe_t *df = df_read_csv("test.csv", ",");
    dataframe_shape_t s;
    //dataframe_t *sorted = df_sort(df, "age", cmp_int_asc);

    if (!df)
        return (84);
    s = df_shape(df);
    printf("--- SHAPE ---\nRows: %d, Cols: %d\n\n", s.nb_rows, s.nb_columns);
    df_to_type(df, "age", INT);
    printf("--- INFO ---\n");
    df_info(df);
    printf("\n--- DESCRIBE ---\n");
    df_describe(df);
    df_write_csv(df, "output.csv");
    df_free(df);
    return (0);
}
