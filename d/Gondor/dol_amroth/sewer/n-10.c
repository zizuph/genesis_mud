/*
 * Sewer n-10.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

void
create_sewer()
{
    add_exit(DOL_SEWER + "n-09", "north", 0, 2);
    add_exit(DOL_SEWER + "o-11", "southeast", 0, 2);
}
