/* -*- Mode: C -*-
 *
 * trade/houses/s-13.c
 *
 * Skippern 20(c)01
 *
 * The shop code in this herb shop is hendeled by the shop keeper
 * Thanks to Gwyneth for help with the long description.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

#include <macros.h>

/* Prototypes */

object ShopKeeper;

string
long_desc()
{
    string desc, view;

    desc = ("Dozens of strong scents assault your senses at once. You " +
	    "have entered a small room, filled with hundreds of herbs. Hanging " +
	    "from the ceiling or sealed in jars upon shelves, it is easy to " +
	    "imagine that any herb you require could be purchased here. " +
	    (objectp(ShopKeeper) ?
	     ShopKeeper->query_Art_name(this_player()) + " sits behind a small " +
	     "desk, waiting to help anyone who is in need of some herbs. A " :
	     "A small desk stands empty in the room, and a ") +
	    "large wooden door leads east into a busy square.\n");

  return desc;
}

void
create_inside()
{
    set_short("inside a shop");
    set_long(&long_desc());
	
	add_item( ({ "shelve", "shelves", "shelf", "jar", "jars" }), "Shelves with sealed jars " +
		"line the walls. The jars seems to be filled with various herbs.\n");
	add_item( ({ "herb", "herbs" }), "Hanging from the ceiling hangs barious herbs.\n");

    clone_object(DOL_OBJ + "doors/s-13-door")->move(this_object());
    reset_room();
}

void
reset_room()
{
    if (!present(ShopKeeper)) 
    {
        ShopKeeper = clone_object(DOL_NPC + "keeper/s-13");
	ShopKeeper->move(this_object());
    }
}

void
init()
{
    ::init();
}

