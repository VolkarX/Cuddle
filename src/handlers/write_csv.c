/*
** EPITECH PROJECT, 2025
** Untitled (Workspace)
** File description:
** write_csv.c
*/

#include "../../include/dataframe.h"

static void write_cell(FILE *fp, column_t *col, int r)
{
    if (col->type == INT || col->type == UINT) {
        fprintf(fp, "%d", *(int *)col->data[r]);
        return;
    }
    if (col->type == FLOAT) {
        fprintf(fp, "%.2f", *(float *)col->data[r]);
        return;
    }
    if (col->type == BOOL) {
        fprintf(fp, "%s", *(int *)col->data[r] ? "true" : "false");
        return;
    }
    fprintf(fp, "%s", (char *)col->data[r]);
}

static void write_row(FILE *fp, dataframe_t *df, int r)
{
    for (int c = 0; c < df->nb_columns; c++) {
        write_cell(fp, df->columns[c], r);
        if (c < df->nb_columns - 1)
            fprintf(fp, ",");
    }
    fprintf(fp, "\n");
}

int df_write_csv(dataframe_t *df, const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (!fp || !df)
        return (84);
    for (int i = 0; i < df->nb_columns; i++) {
        fprintf(fp, "%s", df->columns[i]->title);
        if (i < df->nb_columns - 1)
            fprintf(fp, ",");
    }
    fprintf(fp, "\n");
    for (int r = 0; r < df->nb_rows; r++)
        write_row(fp, df, r);
    fclose(fp);
    return (0);
}
