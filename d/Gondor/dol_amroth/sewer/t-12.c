/* -*- Mode: C -*-
 * Sewer t-12.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "s-11", "northwest", 0, 2);
    add_exit(DOL_SEWER + "u-13", "southeast", 0, 2);
}
