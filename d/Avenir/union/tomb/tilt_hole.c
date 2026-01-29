/*
 * Hole that leads between east tilt hallway and the panel room.
 *       Cirion, May 28 1996
 */
#pragma strict_types
#include "defs.h"

inherit "/std/room";
#include <macros.h>


public void
create_room(void)
{
    set_short("narrow square tunnel");
    set_long("You are wedged into a narrow square tunnel made from "+
	"smooth blocks of stone. To the east, there is a faint light "+
	"light, @@see_west@@\n");

    set_noshow_obvious(1);

    add_exit(THALLE, "west", "@@go_west");
    add_exit("panel_room", "east", "@@go_east");
}

public int
go_east(void)
{
    write("You crawl along the tunnel to the east, and come out into "+
	"a large, circular room.\n");
    return 0;
}

public int
go_west(void)
{
    int level = THALLE->query_level();

    switch(level)
    {
    case -9 .. -6:
	write("The opening to the west is not large enough for you "+
	    "to fit through.\n");
	return 1;
    case -5 .. 5:
	write("You crawl out of the hole and into the hallway.\n");
	tell_room(THALLE, QCTNAME(TP) + " crawls out of the hole.\n");
	return 0;
    case 6 .. 99999:
	write("You crawl west, out of the tunnel, and fall to the hard "+
	    "floor below!\n");
	TP->heal_hp(-(level * 5));
	tell_room(THALLE, QCTNAME(TP) +" crawls out from the tunnel "+
	    "high above and falls to the floor with a thud.\n");
	return 0;
    default:
	write("The way west is blocked by a solid wall of stone!\n");
	return 1;
    }
}

public string
see_west(void)
{
    int level = THALLE->query_level();

    if (level > 5)
    {
	return "and to the west, the tunnel leads out through "+
	    "a wall high above the floor.";
    }
    else if (level < -5 && level > -10)
    {
	return "and to the west, the hole partially opens up "+
	    "into a long hallway, but the crack is too narrow "+
	    "to pass through.";
    }
    else if (level >= -5 && level <= 5)
    {
	return "and to the west, the tunnel opens up into a long, "+
	    "strange hallway.";
    }
    else return "and the west is blocked by a solid wall of stone.";
}
