/* -*- Mode: C -*-
 * Sewer f-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "g-06", "northeast", 0, 2);
    add_exit(DOL_SEWER + "e-07", "west", 0, 2);
}
