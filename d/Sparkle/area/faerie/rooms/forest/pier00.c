/*
 * The pier for Sparkle
 * Tapakah, 10/2008
 */
 
#include "_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit BEACH_BASE;
inherit LIBPIER;

void
create_room()
{
    ::create_beach_room();

    setuid();
    seteuid(getuid());
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A long wooden pier");
    set_long(short() + ". " + s_desc_sky_outside_sky() +
             "It extends northeast " +
             "out into the lake. The pier is brand new being built from " +
             "prime materials by the Genesis ShipLines Company.\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);

    set_add_beach();
    set_add_forest();
    set_pier_top();

    add_exit(FOREST_DIR + "landing",  "southwest");

    // Pier specific functionality
    add_pier_entry(MASTER_OB(this_object()), "Faerie", "Passage to Sparkle");    
    initialize_pier();
}
