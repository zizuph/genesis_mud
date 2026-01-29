// -*-C++-*-
// file name:	bones.c	
// creator(s): 	Boriska, Dec 1994

// last update:	Sirra, March 1998 added the functions for
//		for the wolf quest.

// purpose:	search the bones find a vertebra bone(quest obj)

// note:
// bug(s):
// to-do:     

inherit "/std/object";

#include "wolf.h"
#include <macros.h>
#include <stdproperties.h>

string find_wolf_bone(object player, string str);
int do_dust();
int found;

void
create_object()
{
    set_name ("bones");
    add_name ("bunch");
    set_pname("bones");
    set_short ("bunch of bones");
    set_pshort ("bunches of bones");
    set_long("A bunch of bones. They are all that remains of some "+
        "unfortunate and unknown creature.\n");
    add_prop (OBJ_I_WEIGHT, 7000);
    add_prop (OBJ_I_VOLUME, 6000);
    add_prop (OBJ_I_VALUE, 50);


    add_prop(OBJ_S_SEARCH_FUN, "find_wolf_bone");
    add_prop(OBJ_I_SEARCH_TIME,2);

    found = 1;   // as this object resets in the room, so
	         // will the wolf_bone. :) 
}

string
find_wolf_bone(object player, string str)
{
    object bone;

    if (found < 1)
        return 0;

    found--;
    bone = clone_object(WOLF_BONE + "redherring.c");
    bone->move(this_player(), 1);

    set_alarm(1.0, 0.0, "do_dust");

    return "You find a bone!\n";
}

int
do_dust()
{
    this_player()->catch_msg("The bunch of bones crumbles to "
	+ "dust and blows away.\n");

    this_object()->remove_object();

    return 1;
}

