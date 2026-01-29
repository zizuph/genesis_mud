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

    set_extraline("The foothills are a combination of small hills and " +
        "ravines. Thick bushes grow in scattered bunches across the reddish " +
        "hills and the ravines are full of stunted trees.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the foothills.\n");

    add_exit(ER_DIR + "br3_20", "east");
    add_exit(ER_DIR + "br3_18", "southwest");

}

