/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKOUTROOM
/*inherit ROOM_TELLS*/

#include <ss_types.h>
#include <macros.h>

void
create_xak_room() 
{
    set_short("The swamp lands");
    set_long("You are standing in the swamp lands."
	     + " The swamp stretches on in all directions"
	     + " but the only passable stretch is a seemingly"
	     + " endless stretch of water, mud and dangerous quicksand"
	     + " to the north."
	     + " The marsh insects fly and crawl all over you making you"
	     + " even more disgusting filthy than you already are.\n");
    
    add_exit(TDIR + "/d/Krynn/wild/eastconnect.c", "west", 0);
    add_exit(TDIR + "xakout.c", "north", "@@swmove", 3);
    OUTSIDE;
    LIGHT;
    add_item(({"marsh", "swamp", "swamp lands"}), "@@swamp");
    set_tell_time(15);
    add_tell("An ooze pit next to you bubbles and erupts spurting"
	     + " gunge all over you.\n");
    add_tell("A small marsh insect flys into your eye"
	     + " momentarily blinding you.\n");
    add_tell("You see some marsh gas escape from a pit"
	     + " of bubbling ooze to your east.\n");
    add_tell("The noise of the swamp insects chatters on"
	     + " all around you.\n");
    add_tell("You see a small swamp lizard scurry out from some"
	     + " brush and catch a marsh fly with its tongue.\n");
    add_tell("Far up above you, you spy several birds"
	     + " circling. They seem awful big considering the distance"
	     + " they are away.\n");
    add_tell("You start to shiver from the cold and wet.\n");
    add_tell("You thought you heard something behind you..."
	     + "   or was it below you?\n");
    add_tell("A soft breeze blows up carrying the stench of the"
	     + " swamp to your nostrils.\n");
}

string
swamp()
{
    write("The swamp is a filthy wet disgusting place. Various"
	  + " unhealthy looking puddles of ooze and muck lie everywhere.\n");
    return "";
}

int
swmove()
{
    write("You trudge through the seeming endless swamp. Its very tiring.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
