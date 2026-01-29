/* -*- Mode: C -*-
 * Sewer m-08.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "l-07", "northwest", 0, 2);
    add_exit(DOL_SEWER + "n-09", "southeast", 0, 2);
    set_grate("up", DOL_OTHER+"streets/m-08");
}
