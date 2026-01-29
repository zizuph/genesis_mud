/* -*- Mode: C -*-
 *
 * other/store/s-13.c
 *
 * Skippern 20(c)01
 *
 * A store room.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */

void
create_inside()
{
    set_short("store room for s-13");
    set_long("this is the store room of the shop in s-13\n\n");

    add_exit(DOL_TRADE + "houses/s-13", "down", 0, 1);

    reset_room();
}

void
reset_room()
{
    int i;
}
