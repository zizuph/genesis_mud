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
    set_short("Deep in the forest");
    set_long(s_desc_sky_outside_sky() + "The road continues into the " +
        "forest. The forest becomes thicker, and an unsettling feeling " +
        "seems to descend on the area. Trees rise to the sky and block " +
        "most of the sky's light.\n");
    
    add_std_herbs("forest");

    add_exit(GIB_DIR + "road03", "east");
    add_exit(GIB_DIR + "road01", "southwest");


}
