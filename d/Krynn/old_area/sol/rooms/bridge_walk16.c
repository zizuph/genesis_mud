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

    add_exit(TDIR + "bridge_walk17", "north");
    add_exit(TDIR + "platform4", "south");

    reset_solace_room();
}

public string
my_desc()
{
    string str, people;

    str = "The bridge-walk extends to the north and south. To the " +
          "south you can see a platform. Looking down, you are " +
          "able to see the west road of Solace";

    if (people = get_living(({TDIR + "west_road2"})))
        str += ", walking along the road you can see " + people;

    return str + ".";
}
