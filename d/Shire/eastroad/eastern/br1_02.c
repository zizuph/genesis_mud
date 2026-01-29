/*
 * Secret path for Rangers.
 * Branch 1. Runs from Bree to Weathertop
 * -- Finwe, June 2004
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("path");
    set_area("among dense oaks in");
    set_areaname("the forest");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("sparse");
    set_treetype("oak");

    set_add_forest();
    set_add_sky();
    add_std_herbs("forest");

    set_extraline("The forest is quite large and full of tall oaks. They " +
        "block your view and the sky above you. The path is barely visible " +
        "in the forest. It wanders though the trees and over fallen " +
        "logs and disappears beyond your view.");

    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees that grow here make up most of the " +
        "forest. They are tall and ancient looking. Their thick branches " +
        "spread out, blocking your view, and are covered with large " + 
        treetype + " leaves.\n");  

    add_item(({"path"}),
        "The path is little more than a thin line that winds through " +
        "the trees. It is probably an animal trail as it is so thin.\n");


    add_exit(ER_DIR + "br1_03", "northeast");
    add_exit(ER_DIR + "br1_01", "southwest");

}

