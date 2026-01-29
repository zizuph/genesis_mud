/* -*- Mode: C -*-
 * Sewer k-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "j-06", "northwest", 0, 2);
    add_exit(DOL_SEWER + "l-07", "east", 0, 2);
}
