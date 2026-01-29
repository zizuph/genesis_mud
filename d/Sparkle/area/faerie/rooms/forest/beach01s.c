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
    set_short("Underneath a pier on a beach");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The beach " +
        "is made up of yellow sand and washed smooth from the constant " +
        "motion of the waves.\n" );
    reset_room();
    
    set_add_beach();
    set_pier_bottom();

    add_exit(FOREST_DIR + "landing",  "west");
    add_exit(FOREST_DIR + "beach02s", "southeast");


}
void
reset_room()
{
}
