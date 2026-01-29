/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "";

void
create_forest_room()
{
    set_short("A track in the forest");
    set_long(mt_desc5(extra_line));

    set_add_valley();
    add_std_herbs("forest");
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();

    add_exit(FOREST_DIR + "mtroad16", "northwest");
    add_exit(FOREST_DIR + "mtroad18", "southeast");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    object npc;
    string npc_file_name = TRAVELLER,
        npc_name = FAERIE + npc_file_name + "_";

    if (!present(npc_name)) 
    {
        npc = clone_object(NPC_DIR + npc_file_name);
        npc->move(TO);
    }

    set_searched(0);
}
