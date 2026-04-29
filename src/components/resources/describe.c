/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Describe function
*/

#include "../../../include/dataframe.h"

static void print_desc(char *title, int count, stats_t *s)
{
    double mean = s->sum / count;
    double std = sqrt((s->sq_sum / count) - (mean * mean));

    printf("Column: %s\nCount: %d\nMean: %.2f\n", title, count, mean);
    printf("Std: %.2f\nMin: %.2f\nMax: %.2f\n\n", std, s->min, s->max);
}

static void update_stats(stats_t *s, double val, int r)
{
    if (r == 0 || val < s->min)
        s->min = val;
    if (r == 0 || val > s->max)
        s->max = val;
    s->sum += val;
    s->sq_sum += (val * val);
}

void df_describe(dataframe_t *df)
{
    stats_t s;
    double v;
    column_t *c;

    if (df == NULL)
        return;
    for (int i = 0; i < df->nb_columns; i++) {
        c = df->columns[i];
        if (c->type == STRING || c->type == BOOL || c->type == UNDEFINED)
            continue;
        s.sum = 0;
        s.sq_sum = 0;
        for (int r = 0; r < df->nb_rows; r++) {
            v = (c->type == INT || c->type == UINT) ?
                (double)*(int *)c->data[r] : (double)*(float *)c->data[r];
            update_stats(&s, v, r);
        }
        print_desc(c->title, df->nb_rows, &s);
    }
}
