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

    set_long_desc("From here the bridge-walk extends to the north and " +
		  "southeast. To the north you spy a platform.");

    add_exit(TDIR + "platform8", "north");
    add_exit(TDIR + "bridge_walk23", "southeast");

    reset_solace_room();
}


