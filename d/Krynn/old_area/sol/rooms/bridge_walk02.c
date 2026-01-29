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

    set_long_desc("The bridge-walk you are following continues northeast " +
		  "and west to other Vallenwood trees. Above you, the " +
		  "branches of the trees intertwine and form a thick " +
		  "canopy.");

    add_exit(TDIR + "bridge_walk03", "northeast");
    add_exit(TDIR + "bridge_walk01", "west");

    reset_solace_room();
}


