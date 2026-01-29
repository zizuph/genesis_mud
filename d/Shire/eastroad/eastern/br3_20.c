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

    set_extraline("Many bushes grow here that make movement difficult. To " +
        "the east and south the bushes are thicker, and block you from " +
        "going in that direction. Dark trees grow to the south and become " +
        "a thick forest. A barely visible path leads south into the Trollshaws.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the foothills.\n");

    add_exit(ER_DIR + "br5_01", "northeast");
    add_exit(ER_DIR + "br3_19", "west");
    add_exit(ER_DIR + "br4_01", "southeast",0,0,2);

}

