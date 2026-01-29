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
    set_short("A sandy beach alongside a lake");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The beach " +
        "slopes gently to the north into the water. It is yellow colored " +
        "and dotted with shells and flotsam and jetsam. The beach runs " +
        "northwest and south around the lake.\n" );

    reset_room();
    
    set_add_beach();
    set_add_forest();

    add_exit(FOREST_DIR + "beach01n",  "south");
    add_exit(FOREST_DIR + "beach03n", "northwest");


}
void
reset_room()
{
}
