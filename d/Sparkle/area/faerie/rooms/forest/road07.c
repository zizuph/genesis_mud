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
    set_short("Along the Southern Trade Road");
    set_long(forest_desc3(extra_line));
    add_std_herbs("forest");
    add_stuff();

    add_exit(FOREST_DIR + "road08", "north");
    add_exit(FOREST_DIR + "road06", "south");


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

    string npc_file_name = ORC,
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
