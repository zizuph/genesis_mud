/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gCitizen, gDoor;

reset_solace_room()
{
    if (!gCitizen)
        (gCitizen = clone_object(NPC + "citizen"))->move(TO);
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk14", "east");
    add_exit(TDIR + "platform4", "northwest");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk15");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "You stand before of a small family residence that has " +
          "been built in a mighty vallenwood tree. The brown door leading " +
	  "into the house is ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". The bridge-walk extends to the east and to the northwest " +
           "from here. The trees form a thick canopy overhead.";

    return str;
}
