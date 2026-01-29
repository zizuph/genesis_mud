#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void create_er_room()
{
    set_areadesc("rolling");
    set_area("hillside of");
    set_areaname("the large forest");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_grass("lush long");
    set_treetype("oak");

    set_add_forest();
    set_add_sky();

    set_extraline("The dense oak forest surrounds you on all sides. To " +
        "the west, Bree hill rises, blocking movement that way. South is " +
        "the the Great East road which runs through the forest.");
    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees that grow here make up most of the " +
        "forest. They are tall and ancient looking. Their thick branches " +
        "spread out, blocking your view, and are covered with large " + 
        treetype + " leaves.\n");
    add_item(({"bree-hill", "bree hill"}),
        "This is a tall hill on the eastern edge of Bree. It runs north " +
        "and south, and forms the eastern border of Bree. Tall oak trees " +
        "over the hill, which make up the western part of the forest.\n");
    add_item("bree",
        "This important town lies on the other side of the hill. It cannot be seen from the forest.\n");
    add_item(({"east road", "great east road", "great eastroad", "great road"}),
        "The road runs through " + areaname + " to the south. It is hard " +
        "to see it as it is mostly hidden from view.\n");
    add_std_herbs("forest");

    add_exit(ER_DIR + "erb5n1", "east", 0, "@@move_medi@@", 1);
    add_exit(ER_DIR + "erb4", "south", 0, "@@move_medi@@");

}
