/*
 * REGION.c
 * Region File that defines the regional information
 * on the outside portions of the city of Avular.
 * - Alaron Jan 2000
 */

#include "defs.h"
#include "/d/Emerald/sys/terrain_types.h"

inherit "/d/Emerald/std/region";

void
create_region()
{
    set_region_name("Avular");

    set_coordinates(1, -1, -1499, -1500);
    set_terrain( TERRAIN_PATH | TERRAIN_SHADY | TERRAIN_CLUTTER );
 
    /* About 1500 feet up */
    set_elevation( 500 );

    /* Somewhat high elevation, utter darkness, its going to be cold */
    set_temperature( 8 );

    /* Somewhat less precip than the average domain spots */
    set_precipitation_mod( 80 );


}
