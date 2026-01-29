/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "";
void add_stuff();


void
create_forest_room()
{
    FIXEUID;
    set_short("Along the Central Trade Road");
    set_long(forest_desc3(extra_line));
    add_std_herbs("forest");
    reset_room();

    add_exit(FOREST_DIR + "road03", "north");
    add_exit(FOREST_DIR + "road01", "south");
    add_stuff();

}

public void
init()
{
    ::init();

}
void
add_stuff()
{
    object npc;
    string npc_file_name = TRAVELLER,
        npc_name = FAERIE + npc_file_name + "_";

    if (!present(npc_name)) 
    {
        npc = clone_object(NPC_DIR + npc_file_name);
        npc->move(TO);
    }
}

void
reset_room()
{
    add_stuff();
}
