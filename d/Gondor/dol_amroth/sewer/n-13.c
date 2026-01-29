/* -*- Mode: C -*-
 * Sewer n-13.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

int
grate_d()
{
    write("A grate blocks the way southwest.\n");
    return 1;
}

void
create_sewer()
{
    set_checkpoint("n-13");

    add_exit(DOL_SEWER + "o-12", "northeast", 0, 2);
    add_exit(DOL_SEWER + "l-07", "southwest", &grate_d(), 2);
    set_grate("up", DOL_HILLS+"streets/n-13");
}
