/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_unique_values function
*/

#include "../../../include/dataframe.h"

/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** get_unique_values function
*/

#include "../../../include/dataframe.h"

static bool is_equal(void *v1, void *v2, column_type_t type)
{
    if (type == INT || type == UINT || type == BOOL)
        return (*(int *)v1 == *(int *)v2);
    if (type == FLOAT)
        return (*(float *)v1 == *(float *)v2);
    return (strcmp((char *)v1, (char *)v2) == 0);
}

static bool is_in_array(void **arr, int size, void *val, column_type_t type)
{
    for (int i = 0; i < size; i++) {
        if (is_equal(arr[i], val, type))
            return (true);
    }
    return (false);
}

static void **extract_unique(column_t *col, int rows)
{
    void **arr = malloc(sizeof(void *) * (rows + 1));
    int count = 0;

    if (arr == NULL)
        return (NULL);
    for (int i = 0; i < rows; i++) {
        if (!is_in_array(arr, count, col->data[i], col->type)) {
            arr[count] = col->data[i];
            count++;
        }
    }
    arr[count] = NULL;
    return (arr);
}

void **df_get_unique_values(dataframe_t *df, const char *column)
{
    if (df == NULL || column == NULL)
        return (NULL);
    for (int i = 0; i < df->nb_columns; i++) {
        if (strcmp(df->columns[i]->title, column) == 0)
            return (extract_unique(df->columns[i], df->nb_rows));
    }
    return (NULL);
}
