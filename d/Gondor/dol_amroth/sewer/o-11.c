/* -*- Mode: C -*-
 * Sewer o-11.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "n-10", "northwest", 0, 2);
    add_exit(DOL_SEWER + "p-12", "southeast", 0, 2);
}
