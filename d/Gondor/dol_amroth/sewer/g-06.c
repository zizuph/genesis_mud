/* -*- Mode: C -*-
 * Sewer g-06.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";
inherit "/lib/unique";

void
create_sewer()
{
    set_checkpoint("g-06");

    add_exit(DOL_SEWER + "g-05", "north", 0, 2);
    add_exit(DOL_SEWER + "h-07", "southeast", 0, 2);
    add_exit(DOL_SEWER + "f-07", "southwest", 0, 2);
}
