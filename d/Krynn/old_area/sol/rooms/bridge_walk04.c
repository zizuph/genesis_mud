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

    set_long_desc("The bridge-walk extends further to the east and west. " +
		  "To the west, in a mighty Vallenwood tree, is the biggest " +
		  "building you have noticed in this village. From it " +
		  "wafts the smell of cooking food.");

    add_exit(TDIR + "bridge_walk03", "east");
    add_exit(TDIR + "platform2", "west");

    reset_solace_room();
}
