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

    set_extraline("The dark forest grows to the south which block your " +
        "view that way. Ridges rise in the distance, and are bare except " +
        "for the bushes and stunted trees that grow on them. The land " +
        "looks very inhospitable.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the foothills.\n");

    add_exit(ER_DIR + "br5_03", "east");
    add_exit(ER_DIR + "br5_01", "west");


}

