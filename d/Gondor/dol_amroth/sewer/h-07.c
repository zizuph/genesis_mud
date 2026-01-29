/* -*- Mode: C -*-
 * Sewer h-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "g-06", "northwest", 0, 2);
    add_exit(DOL_SEWER + "i-07", "east", 0, 2);
}
