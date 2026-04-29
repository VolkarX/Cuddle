/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** strict type conversion
*/

#include "../../../include/dataframe.h"

static bool check_num(char *str, column_type_t type)
{
    int dots = 0;
    int i = (str[0] == '-') ? 1 : 0;

    if (type == UINT && str[0] == '-')
        return (false);
    for (; str[i]; i++) {
        if (str[i] == '.') {
            dots++;
            continue;
        }
        if (!isdigit(str[i]))
            return (false);
    }
    return (dots <= 1);
}

static void *do_conv(char *str, column_type_t type)
{
    int *v_i;
    float *v_f;

    if (type == INT || type == UINT || type == BOOL) {
        v_i = malloc(sizeof(int));
        if (type == BOOL)
            *v_i = (atoi(str) != 0 || strcasecmp(str, "true") == 0) ? 1 : 0;
        else
            *v_i = atoi(str);
        return (v_i);
    }
    if (type == FLOAT) {
        v_f = malloc(sizeof(float));
        *v_f = (float)atof(str);
        return (v_f);
    }
    return (strdup(str));
}

static bool process_col(dataframe_t *new, int idx, column_type_t type)
{
    char *old;

    for (int r = 0; r < new->nb_rows; r++) {
        old = (char *)new->columns[idx]->data[r];
        if (type != STRING && type != BOOL && !check_num(old, type))
            return (false);
    }
    for (int r = 0; r < new->nb_rows; r++) {
        old = (char *)new->columns[idx]->data[r];
        new->columns[idx]->data[r] = do_conv(old, type);
        free(old);
    }
    new->columns[idx]->type = type;
    return (true);
}

dataframe_t *df_to_type(dataframe_t *df, const char *col, column_type_t type)
{
    int idx = -1;
    dataframe_t *new;

    if (df == NULL || col == NULL)
        return (NULL);
    new = df_copy(df);
    for (int i = 0; i < new->nb_columns; i++)
        if (strcmp(new->columns[i]->title, col) == 0)
            idx = i;
    if (idx == -1)
        return (new);
    if (!process_col(new, idx, type)) {
        df_free(new);
        return (NULL);
    }
    return (new);
}
