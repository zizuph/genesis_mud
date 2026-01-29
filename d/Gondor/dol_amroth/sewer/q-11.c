/* -*- Mode: C -*-
 * Sewer s-11.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "p-12", "southwest", 0, 2);
    add_exit(DOL_SEWER + "r-10", "northeast", 0, 2);
}
