/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

object gCitizen;

reset_solace_room()
{
    if (!gCitizen)
        (gCitizen = clone_object(NPC + "citizen"))->move(TO);
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "bridge_walk12", "south");
    add_exit(TDIR + "platform1", "northwest");

    reset_solace_room();
}

public string
my_desc()
{
    string str, people;

    str = "The wooden bridge-walk that winds through the trees " +
          "extends south and northwest from here. The tree branches " +
	  "form a thick canopy overhead. Looking down you can see " +
	  "the Solace Main road";

    if (people = get_living(({TDIR + "main_road5"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}




