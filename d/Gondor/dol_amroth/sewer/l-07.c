/* -*- Mode: C -*-
 * Sewer l-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

int
grate()
{
    write("A grate blocks your path east.\n");
    return 1;
}

void
create_sewer()
{
    set_checkpoint("l-07");

    add_exit(DOL_SEWER + "k-07", "west", 0, 2);
    add_exit(DOL_SEWER + "m-08", "southeast", 0, 2);
    add_exit(DOL_SEWER + "m-07", "east", &grate(), 2);
}
