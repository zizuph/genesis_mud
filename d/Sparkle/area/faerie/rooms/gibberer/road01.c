/*
 * The forest road of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A clearing deep in the forest");
    set_long(s_desc_sky_outside_sky() + "The clearing is wide and " +
        "cleared of all growth. A cairn of rocks has been erected in " +
        "the center of the clearing. It is large and dominates the " +
        "area. An opening can be seen in the side of the cairn.\n");     
    add_item(({"cairn", "tomb"}),
        "This is a pile of stones that have been erected as a grave. " +
        "It stands as a memorial for some unknown battle that was fought " +
        "in the forest.\n");
    add_item(({"opening"}),
        "It is set into the side of the cairn. It is irregularly shaped " +
        "and enables visitors to enter the cairn.\n");
    add_item(({"stones", "pile", "pile of stones"}),
        "They are different colors and sizes of stones. Most of them are " +
        "quite large and have been piled in a heap to form the cairn.\n");
    add_item(({"memorial", "grave"}),
        "It's a pile of stones that make up the cairn.\n");
    add_item(({"clearing", "forest clearing"}),
        "It is a wide area, cleared of trees and underbrush. The ground " +
        "is trampled and hard looking. There is a pile of rocks in " +
        "the center of the clearing.\n");
    
    add_std_herbs("forest");

    add_exit(GIB_DIR + "road02", "northeast");
    add_exit(GIB_DIR + "gib01", "in");


}
