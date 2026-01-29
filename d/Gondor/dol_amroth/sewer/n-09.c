/* -*- Mode: C -*-
 * Sewer n-09.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "m-08", "northwest", 0, 2);
    add_exit(DOL_SEWER + "n-10", "south", 0, 2);
}
