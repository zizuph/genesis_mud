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

    add_exit(TDIR + "bridge_walk18", "northeast");
    add_exit(TDIR + "bridge_walk20", "south");

    gDoor = clone_object(OBJ + "d_bridge_walk19");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "A house has been built here in the tree; the green door " +
          "leading into the house is ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". The bridge-walk extends to the northeast and to the south.";

    return str;
}
