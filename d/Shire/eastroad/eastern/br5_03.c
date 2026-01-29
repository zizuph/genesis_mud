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

    set_extraline("This ridge overlooks the foothills to the east. It is " +
        "bare except for a few stunted trees that grow on the reddish " +
        "top and is dotted by some bushes. The path wanders west and " +
        "descends south into a ravine.");

    add_item(({"path"}),
        "The paths are little more than a thin line that winds through " +
        "the foothills.\n");

    add_exit(ER_DIR + "br5_04", "southeast");
    add_exit(ER_DIR + "br5_02", "west");


}

