/* -*- Mode: C -*-
 * Sewer d-06.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "e-07", "southeast", 0, 2);
    add_exit(DOL_SEWER + "d-05", "north", 0, 2);
    set_grate("up", DOL_CRAFT+"streets/d-06");
}
