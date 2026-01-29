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
    add_stuff();

    add_exit(FOREST_DIR + "road14", "north");
    add_exit(FOREST_DIR + "road11", "south");
    add_exit(FOREST_DIR + "road13", "east");
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

    FIXEUID;

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
