/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit FOREST_BASE;

string extra_line = "";
void add_stuff();

void
create_forest_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("Along the Central Trade Road");
    set_long(forest_desc5(extra_line));
    add_std_herbs("forest");
    add_stuff();

    add_exit(FOREST_DIR + "ctroad11", "northwest");
    add_exit(FOREST_DIR + "ctroad09", "southeast");
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

    string npc_file_name = SETTLER,
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
    set_searched(0);
}
