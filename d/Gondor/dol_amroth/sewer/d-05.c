/* -*- Mode: C -*-
 * Sewer d-05.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

int
grate()
{
    write("A grate blocks your path north.\n");
    return 1;
}

void
create_sewer()
{
    set_checkpoint("d-05");

    add_exit(DOL_SEWER + "d-06", "south", 0, 2);
    add_exit(DOL_SEWER + "d-04", "north", &grate(), 2);
}
