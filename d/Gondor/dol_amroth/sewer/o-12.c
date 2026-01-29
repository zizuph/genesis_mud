/* -*- Mode: C -*-
 * Sewer o-12.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "p-12", "east", 0, 2);
    add_exit(DOL_SEWER + "n-13", "southwest", 0, 2);
}
