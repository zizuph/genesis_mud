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
    set_vbfc_extra(forest_desc2);
    extraline="Some broken branches hang down from the trees, " +
        "blocking the light. ";

    add_item(({"broken branch", "broken branches"}),
        "Some broken branches hang down from the trees. Their " +
        "ends look like they were broken off during a strong " +
        "wind or from old age.\n");
    reset_shire_room();
    add_forest_herbs();

    add_exit(TREES_DIR  + "tree65_01", "up",0,4);
    add_exit(FOREST_DIR + "forest56", "north",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest57", "northeast",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest71", "southwest",0,4, check_player(2));

}

void reset_shire_room()
{
    set_searched(0);

}
