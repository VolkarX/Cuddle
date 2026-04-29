/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** read_csv implementation
*/

#include "../../include/dataframe.h"

static int count_cols(char *line, const char *sep)
{
    int count = 0;
    char *tmp = strdup(line);
    char *tok = strtok(tmp, sep);

    while (tok) {
        count++;
        tok = strtok(NULL, sep);
    }
    free(tmp);
    return (count);
}

static void update_col(dataframe_t *df, int c)
{
    column_type_t curr;

    df->columns[c]->type = UNDEFINED;
    for (int r = 0; r < df->nb_rows; r++) {
        curr = detect_type((char *)df->columns[c]->data[r]);
        if (curr == STRING) {
            df->columns[c]->type = STRING;
            return;
        }
        if (curr == FLOAT)
            df->columns[c]->type = FLOAT;
        if (df->columns[c]->type == UNDEFINED)
            df->columns[c]->type = curr;
    }
    if (df->columns[c]->type == UNDEFINED)
        df->columns[c]->type = STRING;
}

static void convert_single_cell(column_t *c, int r)
{
    char *s = (char *)c->data[r];

    if (c->type == INT || c->type == UINT || c->type == BOOL) {
        c->data[r] = malloc(sizeof(int));
        *(int *)c->data[r] = (c->type == BOOL) ?
            (strcasecmp(s, "true") == 0 || atoi(s) != 0) : atoi(s);
        free(s);
        return;
    }
    if (c->type == FLOAT) {
        c->data[r] = malloc(sizeof(float));
        *(float *)c->data[r] = (float)atof(s);
        free(s);
    }
}

static void convert_col_data(column_t *c, int rows)
{
    for (int r = 0; r < rows; r++)
        convert_single_cell(c, r);
}

static void finalize_types(dataframe_t *df)
{
    for (int c = 0; c < df->nb_columns; c++) {
        update_col(df, c);
        if (df->columns[c]->type != STRING)
            convert_col_data(df->columns[c], df->nb_rows);
    }
}

static void fill_columns(dataframe_t *df, FILE *fp, const char *sep)
{
    char *line = NULL;
    size_t len = 0;
    char *tok = NULL;

    for (int r = 0; r < df->nb_rows; r++) {
        if (getline(&line, &len, fp) == -1)
            break;
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        tok = strtok(line, sep);
        for (int c = 0; c < df->nb_columns; c++) {
            df->columns[c]->data[r] = strdup(tok ? tok : "");
            tok = strtok(NULL, sep);
        }
    }
    free(line);
}

static void init_struct(dataframe_t *df, char *header, const char *sep)
{
    char *tok = NULL;

    if (header[strlen(header) - 1] == '\n')
        header[strlen(header) - 1] = '\0';
    df->columns = malloc(sizeof(column_t *) * (df->nb_columns + 1));
    tok = strtok(header, sep);
    for (int i = 0; i < df->nb_columns; i++) {
        df->columns[i] = malloc(sizeof(column_t));
        df->columns[i]->title = strdup(tok ? tok : "col");
        df->columns[i]->type = STRING;
        df->columns[i]->data = malloc(sizeof(void *) * df->nb_rows);
        tok = strtok(NULL, sep);
    }
    df->columns[df->nb_columns] = NULL;
}

static void df_parse_file(dataframe_t *df, FILE *fp, const char *sep)
{
    char *line = NULL;
    size_t len = 0;

    rewind(fp);
    getline(&line, &len, fp);
    init_struct(df, line, sep);
    fill_columns(df, fp, sep);
    finalize_types(df);
    free(line);
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    const char *sep = separator ? separator : ",";
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!fp || !df)
        return (NULL);
    df->nb_rows = 0;
    if (getline(&line, &len, fp) != -1)
        df->nb_columns = count_cols(line, sep);
    while (getline(&line, &len, fp) != -1)
        df->nb_rows++;
    df_parse_file(df, fp, sep);
    fclose(fp);
    return (df);
}
