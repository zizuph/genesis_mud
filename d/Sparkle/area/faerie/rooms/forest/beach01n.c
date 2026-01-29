/*
 * The Beach of Faerie, beneath the second pier
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
inherit BEACH_BASE;

void
create_beach_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("Beneath a pier on a beach");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "A pier above " +
    "you runs out into the water. Ships from distant lands dock at it. " +
    "The yellow sand has been washed clean from the waves. Trees line a " +
    "ridge above you to the south. The beach slopes gently to the north " +
    "into the water. A path leads southeast up away from the beach.\n" );

    reset_room();
    
    set_add_beach();
    set_add_forest();
    set_pier_bottom();

    add_exit(FOREST_DIR + "beach02n", "north");
    add_exit(FOREST_DIR + "landing",  "southeast");


}
void
reset_room()
{
}
