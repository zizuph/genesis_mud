/* -*- Mode: C -*-
 * Sewer s-09.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

int
grate()
{
    write("A grate blocks your path northeast.\n");
    return 1;
}

void
create_sewer()
{
    set_checkpoint("s-09");

    add_exit(DOL_SEWER + "n-10", "northeast", &grate(), 2);
    add_exit(DOL_SEWER + "r-10", "southwest", 0, 2);
}
