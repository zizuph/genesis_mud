/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gDoor;

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk09", "north");
    add_exit(TDIR + "platform3", "south");

    gDoor = clone_object(OBJ + "d_bridge_walk10");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str, people;

    str = "The bridge-walk stretches out far to the north, while " +
          "to the south it ends at a platform. In this tree some" +
	  "one has built a rather large house with a ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";
 
    str += " brown door. Looking down you can see the East road";

    if (people = get_living(({TDIR + "east_road2"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}





