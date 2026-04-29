/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Info function
*/

#include "../../../include/dataframe.h"

/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** info display
*/

#include "../../../include/dataframe.h"

void df_info(dataframe_t *df)
{
    char *ts[] = {"bool", "int", "unsigned int", "float", "string", "undef"};

    if (!df)
        return;
    printf("%d columns:\n", df->nb_columns);
    for (int i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->columns[i]->title,
            ts[df->columns[i]->type]);
    }
}
