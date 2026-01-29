/* -*- Mode: C -*-
 *
 * other/store/o-11.c
 *
 * Skippern 20(c)01
 *
 * A store room.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */
int       oilnr;
object    *oil, ob;

void
create_inside()
{
    set_short("store room for o-11");
    set_long("this is the store room of the shop in o-11\n\n");

    add_exit(DOL_TRADE + "houses/o-11", "down", 0, 1);

    oilnr = 5;
    oil = allocate(oilnr);

    reset_room();
}

void
reset_room()
{
    int i;
  
    if (!present("lamp"))
    {
        ob = clone_object("/d/Gondor/common/obj/oil_lamp");
	ob->move(this_object());
    }
    for (i = 0; i < oilnr; i++)
    {
	oil[i] = clone_object("/d/Gondor/common/obj/oilflask");
	oil[i]->move(this_object());
    }
    if (!present("rope"))
    {
        ob = clone_object("/d/Gondor/common/obj/rope");
	ob->move(this_object());
    }
    if (!present("mirror"))
    {
        ob = clone_object("/d/Genesis/doc/examples/obj/mirror");
	ob->move(this_object());
    }
    if (!present("backpack"))
    {
        ob = clone_object("/d/Gondor/common/guild/obj/backpack");
	ob->move(this_object());
    }
    if (!present("wallet"))
    {
        ob = clone_object("/d/Gondor/common/dwarf_guild/obj/wallet");
	ob->move(this_object());
    }
}

