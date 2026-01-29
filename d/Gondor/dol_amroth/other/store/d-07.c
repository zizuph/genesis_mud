/* -*- Mode: C -*-
 *
 * other/store/d-07.c
 *
 * Skippern 20(c)01
 *
 * A store room. //// ARMOUR
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */
object      o;
object      *tg;

void
create_inside()
{
    set_short("store room for d-07");
    set_long("this is the store room of the shop in d-07\n\n");

    add_exit(DOL_CRAFT + "houses/d-07", "down", 0, 1);

    tg = allocate(4);

    reset_room();
}

void
reset_room()
{
    int i;

    for (i = 0; i < 3; i++)
    {
	tg[i] = clone_object(DOL_ARM + "lt-armour");
	tg[i]->move(this_object());
    }
}
