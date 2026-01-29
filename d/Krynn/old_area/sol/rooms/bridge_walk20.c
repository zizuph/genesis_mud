/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

RESETROOM

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk19", "north");
    add_exit(TDIR + "platform7", "southwest");

    reset_solace_room();
}

public string
my_desc()
{
    string str, people;

    str = "The bridge-walk continues to the north and to the " +
	  "southwest, where it ends in a platform. Looking down " +
	  "you can see the West road";

    if (people = get_living(({TDIR + "west_road3"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}



