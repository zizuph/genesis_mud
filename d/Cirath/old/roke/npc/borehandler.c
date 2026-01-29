/*
 * borehandler.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

int nr_of_bores = 0;

int
new_bore()
{
    if (nr_of_bores > 10)
        return 0;
    nr_of_bores++;
    return 1;
}

void
kill_bore()
{
    if (nr_of_bores > 0)
        nr_of_bores--;
}

int
query_bores()
{
    return nr_of_bores;
}
