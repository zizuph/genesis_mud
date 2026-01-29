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
    set_short("A deep valley in the mountains");
    set_long(short() + ". " + s_desc_sky_outside_sky() + 
        "The valley runs to the north " +
        "and is a sharp contrast from the rest of the mountains. Tall " +
        "firs grow in the valley where the track winds its way around " +
        "them. Mountain peaks rise in the distance, covered with more " +
        "trees. " + extra_line + "\n");

    set_add_valley();
    add_std_herbs("forest");
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();

    add_exit(FOREST_DIR + "mtroad03", "north");
    add_exit(FOREST_DIR + "mtroad05", "south");
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
