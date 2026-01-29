/* -*- Mode: C -*-
 *
 * other/store/i-06.c
 *
 * Skippern 20(c)01
 *
 * A store room. //// SUPPLY
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */

void
create_inside()
{
    set_short("store room for i-06");
    set_long("this is the store room of the shop in i-06\n\n");

    add_exit(DOL_COMMON + "houses/i-06", "down", 0, 1);

    reset_room();
}

void
reset_room()
{
    int i;
}
