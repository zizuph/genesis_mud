/*
 * /d/Sparkle/area/city/bank/room/bank_standard.c
 *
 * This is the standard file for all bank rooms in Sparkle.
 *
 * Created March 2008, by Aeg (Matthew Morin)
 */

#pragma strict_types
#pragma no_clone

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* inheritance */
inherit "/std/room";

inherit "/d/Sparkle/lib/room_tell";

public void create_bank_room() {}

public void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    create_bank_room();
    reset_room();

	add_item( ({ "gnome", "gnomes", }),
		"Gnomes operate this bank and they are seemingly everywhere. "
	  + "It is difficult to get an accurate gnome count, because they "
	  + "refuse to stand still and for every gnome that leaves the room "
	  + "another enters.\n");

/* General tells */

    set_tell_time(240);
	add_tell("A gnome scurries past carrying a hammer and a shovel.\n");
	add_tell("A gnome scurries past carrying a pipe and some bolts.\n");
	add_tell("A gnome scurries past carrying a bucket of water and a "
		+ "whistle.\n");
	add_tell("A loud explosion is heard in the distance. Nearby gnomes "
		+ "flood in that direction.\n");
	add_tell("A gnome scurries past carrying a bank employee manual and "
		+ "a handful of bank bags.\n");
	add_tell("A gnomish bureaucrat runs past mumbling at his ledger.\n");
	add_tell("A quarter regiment of gnomish guards, who are armed to "
		+ "their teeth, patrol the area.\n");
	add_tell("An eighth regiment of gnomish guards, who are armed to "
		+ "their teeth, patrol the area.\n");
	add_tell("Gnomish guards patrol the area.\n");

} /* create_room */


public void reset_room()
{
    ::reset_room();
}

 void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}