/* -*- Mode: C -*-
 *
 * trade/streets/p-11.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("A hill towers up to the west.");
    set_lastline("To the north a solide bouldng towers up. The phasade " +
		 "is made of granite and it looks very sturdy. To the " +
		 "west is a worn down house with a sign hanging over " +
		 "the door.");

    add_item( ({ "sign", "sign over door" , "sign over the door" }),
	      "A sign hangs over the door to the worn down house to the " +
	      "west. It reas: Dol Amroth General Store.\n");

	add_item( ({ "house", "worn house", "worn down house" }),
		"To the west you can see a worn down house. There is " +
		"a sign hanging over its door.\n");
		  
    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/o-10", "northwest", 0, 1);
    add_exit(DOL_TRADE + "streets/p-12", "south", 0, 1);
    add_exit(DOL_TRADE + "streets/q-11", "east", 0, 1);
    clone_object(DOL_OBJ + "doors/p-11-bank")->move(this_object());
    clone_object(DOL_OBJ + "doors/p-11-shop")->move(this_object());
}

