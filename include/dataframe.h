/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Header for dataframe operations
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <math.h>
    #include <ctype.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct column_s {
    char *title;
    column_type_t type;
    void **data;
} column_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    column_t **columns;
} dataframe_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct stats_s {
    double sum;
    double sq_sum;
    double min;
    double max;
} stats_t;

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *df, const char *filename);
void df_free(dataframe_t *df);
dataframe_t *df_head(dataframe_t *df, int n);
dataframe_t *df_tail(dataframe_t *df, int n);
dataframe_shape_t df_shape(dataframe_t *df);
void df_info(dataframe_t *df);
void df_describe(dataframe_t *df);
dataframe_t *df_filter(dataframe_t *df, const char *col, bool (*f)(void *));
dataframe_t *df_sort(dataframe_t *df, const char *col,
    bool (*f)(void *, void *));
dataframe_t *df_apply(dataframe_t *df, const char *col, void *(*f)(void *));
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);
dataframe_t *df_copy(dataframe_t *df);
column_type_t detect_type(char *str);
dataframe_t *df_groupby(dataframe_t *df, const char *by,
    const char **to, void *(*f)(void **, int));
void *df_get_value(dataframe_t *df, int row, const char *column);
void **df_get_values(dataframe_t *df, const char *column);
void **df_get_unique_values(dataframe_t *df, const char *column);

#endif /* !DATAFRAME_H_ */
