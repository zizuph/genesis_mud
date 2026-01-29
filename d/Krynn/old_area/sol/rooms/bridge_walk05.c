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

    add_exit(TDIR + "platform2", "east");
    add_exit(TDIR + "bridge_walk06", "southwest");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk05");
    gDoor->move(TO);
}

public string
my_desc()
{
    string str;

    str = "In a nearby tree a family house has been built. "+
	  "The green door leading into the house is ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". To the east you can see a big Vallenwood tree containing " +
           "the biggest structure you have noticed here in Solace. There " +
	   "is also a familiar smell in the air. The bridge-walkway " +
	   "extends to the east and southwest.";

    return str;
}


