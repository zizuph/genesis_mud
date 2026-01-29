/* -*- Mode: C -*-
 *
 * other/store/f-06.c
 *
 * Skippern 20(c)01
 *
 * A store room. //// WEAPONS
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */
object     o;
object     *tg;

void
create_inside()
{
    set_short("store room for o-11");
    set_long("this is the store room of the shop in o-11\n\n");

    add_exit(DOL_CRAFT + "houses/f-06", "down", 0, 1);

    tg = allocate(5);

    reset_room();
}

void
reset_room()
{
    int i;

    for (i = 0; i < 4; i++)
    {
	tg[i] = clone_object(DOL_WEP + "sh-sword");
	tg[i]->move(this_object());
    }
}
