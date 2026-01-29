/*
 * Secret path for Rangers.
 * Branch 2. Runs from Weathertop to the Trollshaws
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("thin");
    set_area("path in");
    set_areaname("the foothills");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_treetype("conifers");

    set_add_foothills();
    set_add_sky();
    add_std_herbs("hills");

    set_extraline("This is a deep ravine on the edge of the Trollshaws. " +
        "It is full of thick bushes and stunted trees which make travel " +
        "difficult. A path climbs out of the ravine to the northwest " +
        "and runs east out of the ravine.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the ravine.\n");

    add_exit(ER_DIR + "br5_05", "northeast");
    add_exit(ER_DIR + "br5_03", "northwest");


}

