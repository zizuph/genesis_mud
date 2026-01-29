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

    add_exit(TDIR + "platform5", "east");
    add_exit(TDIR + "bridge_walk25", "southwest");

    gDoor = clone_object(OBJ + "d_bridge_walk26");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "There is a small house built in this mighty " +
	  "Vallenwood tree, with a ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += " green door leading into it. To the east you can spot a " +
           "platform and extending to the west is the bridge-walk.";

    return str;
}
