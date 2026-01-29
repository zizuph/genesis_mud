/* -*- Mode: C -*-
 * Sewer u-13.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "t-12", "northwest", 0, 2);
    add_exit(DOL_SEWER + "v-14", "southeast", 0, 2);
}
