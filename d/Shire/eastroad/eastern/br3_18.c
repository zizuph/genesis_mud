/*
 * Secret path for Rangers.
 * Branch 2. Runs from Weathertop to the Trollshaws
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

#define WTOP    "/d/Shire/wtop/"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("rocky");
    set_area("trail in");
    set_areaname("the lowlands");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_treetype("conifers");

    set_add_foothills();
    set_add_sky();
    add_std_herbs("plains");

    set_extraline("The lowlands run to the east. Trees grow in " +
        "scattered groups growing on the tops of the low hills.");

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the land.\n");

    add_exit(ER_DIR + "br3_19", "northeast");
    add_exit(ER_DIR + "br3_17", "northwest");

}

