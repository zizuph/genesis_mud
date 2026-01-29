#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("hidden");
    set_area("path in");
    set_areaname("the forest");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
//    set_areadesc("dark area");
    set_grass("lush long");
    set_treetype("oak");

    set_add_forest();
    set_add_sky();

    set_extraline("Dense, tall " + treetype + " trees fill the forest. " +
        "They tower above and spread out in all directions. The path " +
        "seems to run east and west, with a branch leading south. " +
        "To the south is the Great East road. It runs east and west.");
    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees that grow here make up most of the " +
        "forest. They are tall and ancient looking. Their thick branches " +
        "spread out, blocking your view, and are covered with large " +
        treetype + " leaves.\n");
    add_item(({"path", "hidden path"}),
        "The path is well hidden and doesn't look well used. Leaves " +
        "and branches hide it from all but the most observant traveller.\n");

    add_std_herbs("forest");

    add_exit(ER_DIR + "erb6n1", "east", 0, "@@move_medi@@", 1);
    add_exit(ER_DIR + "erb4n1", "west", 0, "@@move_medi@@", 1);
    add_exit(ER_DIR + "erb5", "south", 0, "@@move_medi@@");

}
