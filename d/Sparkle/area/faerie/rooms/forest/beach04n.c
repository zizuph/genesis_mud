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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Boulders " +
        "litter the beach. They have rolled down off the ridge from above " +
        "and prevent travel to the north. The beach is sandy and dotted " +
        "with broken shells.\n");

    reset_room();
    add_item(({"boulders"}),
        "They rolled down off the ridge from above and lay scattered " +
        "across the beach or partially submerged in the lake. The boulders "+
        "are large and irregular shaped. Most of their edges have been " +
        "worn away by the elements.\n");
    set_add_beach();
    set_add_forest();

    add_exit(FOREST_DIR + "beach03n", "south");


}
void
reset_room()
{
}
