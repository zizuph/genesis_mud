/*
 * The road to the gibberers
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
    set_short("Near the Trade Road");
    set_long(s_desc_sky_outside_sky() + "The road branches and heads " +
        "west into the forest. The trees block your view of the surrounding " +
        "forest. They are thicker here than in other areas of the forest.\n");     
    
    add_std_herbs("forest");

    add_exit(GIB_DIR + "road02", "west");
    add_exit(FOREST_DIR + "ctroad15", "northeast");

    reset_room();

}

void
reset_room()
{
    object band;

    if (!present("_faerie_iron_band",TO))
    {
        band = clone_object(OBJ_DIR + "iron_band");
        band->add_prop(OBJ_I_HIDE, 1 + random(4));
        band->move(TO);
    }
}
