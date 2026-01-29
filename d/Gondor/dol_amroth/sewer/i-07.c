/* -*- Mode: C -*-
 * Sewer i-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "h-07", "west", 0, 2);
    add_exit(DOL_SEWER + "j-06", "northeast", 0, 2);
}
