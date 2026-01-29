/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Waves lap " +
        "on the beach. It is made up of yellow sand, washed clean " +
        "from the waves. The lake stretches out to the horizon. Seashells " +
        "lay scattered across the beach.\n" );
    reset_room();

    set_add_beach();
    set_add_forest();

    add_exit(FOREST_DIR + "beach03s", "east");
    add_exit(FOREST_DIR + "beach01s", "northwest");

}
void
reset_room()
{
}
