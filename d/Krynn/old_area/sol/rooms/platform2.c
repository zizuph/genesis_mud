/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(PLATFORM);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "inn", "enter");
    add_exit(TDIR + "bridge_walk04", "east");
    add_exit(TDIR + "bridge_walk05", "west");
    add_exit(TDIR + "main_road2", "down");
}

public string
my_desc()
{
    string str, people;

    str = "You are standing outside the famous inn, the Inn of " +
          "the Last Home. A wave of light, noise and the " +
	  "familiar smell of Otik's spicy potatoes hits you " +
	  "full in the face. There is a stairway leading " +
	  "down around the trunk of the tree and onto the Solace " +
	  "Main road. There are bridge-walks leading east and " +
	  "west from here.";

    if (people = get_living(({TDIR + "main_road2"})))
        str += " Looking down you can see " + people + " walking on " +
	       "the road.";

    return str;
}
