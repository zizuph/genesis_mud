/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

#include "/d/Krynn/common/herbsearch.h"

object gCitizen;
object gMerch;

reset_solace_room()
{
    set_searched(random(2));

    if (!gCitizen)
        (gCitizen = clone_object(NPC + "citizen"))->move(TO);

    if (!gMerch)
        (gMerch = clone_object("/d/Krynn/solace/new_village/shoe/shoe_merchant"))->move(TO);
}

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("From here the bridge-walk extends to the north and " +
		  "southeast. To the north you spy a platform.");

    add_exit(TDIR + "platform8", "north");
    add_exit(TDIR + "bridge_walk23", "southeast");

   seteuid(getuid(TO));
   set_search_places(({"trees","tree","vallenwood","vallenwood tree",
        "boughs","branches","vallenwood trees"}));
   add_prop(OBJ_I_SEARCH_TIME,3);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_herb_file("/d/Krynn/common/herbs/vallenwood_blossom");

    reset_solace_room();
}


