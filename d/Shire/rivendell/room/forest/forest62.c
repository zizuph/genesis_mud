/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc5);
    extraline="Some broken branches hang down from the trees, " +
        "blocking the light. ";

    add_item(({"broken branch", "broken branches"}),
        "Some broken branches hang down from the trees. Their " +
        "ends look like they were broken off during a strong " +
        "wind or from old age.\n");
    reset_shire_room();
    add_forest_herbs();

    add_exit(TREES_DIR  + "tree62_01", "up",0,4,1);
    add_exit(FOREST_DIR + "forest69", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest63", "east",0,4, check_person);

}

void reset_shire_room()
{
    set_searched(0);

}
