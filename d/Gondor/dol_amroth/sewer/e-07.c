/* -*- Mode: C -*-
 * Sewer e-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "f-07", "east", 0, 2);
    add_exit(DOL_SEWER + "d-06", "northwest", 0, 2);
    add_exit(DOL_SEWER + "d-08", "southwest", 0, 2);
}
