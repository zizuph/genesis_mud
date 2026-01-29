/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gDoor;

RESETROOM

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk02", "east");
    add_exit(TDIR + "platform1", "southwest");

    reset_solace_room();

    gDoor = clone_object(OBJ + "d_bridge_walk01");
    gDoor->move(TO);
}


public string
my_desc()
{
    string str, people;

    str = "The wooden bridge-walk that runs from tree to tree " + 
	  "extends southwest to a platform and further east. " +
	  "Beside you, built into the tree, is a small house with a ";
	  
    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += " green door. You can see the Solace Main road " +
	   "below you";

    if (people = get_living(({TDIR + "main_road3"})))
        str += " and you can also see " + people + " walking along the road";

    str += ". The limbs of the mighty tree you are standing beside mesh " +
           "to form a thick canopy overhead.";

    return str;
}


