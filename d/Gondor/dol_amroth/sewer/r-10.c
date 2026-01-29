/* -*- Mode: C -*-
 * Sewer r-10.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "s-09", "northeast", 0, 2);
    add_exit(DOL_SEWER + "s-11", "southeast", 0, 2);
    add_exit(DOL_SEWER + "q-11", "southwest", 0, 2);
    set_grate("up", DOL_TRADE+"streets/r-10");
}
