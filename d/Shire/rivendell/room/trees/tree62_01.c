/*
 * Up in trees in Rivendell forest
 * By Finwe, March 1999
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit TREES_BASE;
 
void
create_tree_room()
{
    set_extraline("This is one of the lower branches of a tall tree " +
        "in the forest. Branches obstruct your view of the " +
        "ground below.\n");
    set_noshow_obvious(1);
    add_exit(TREES_DIR + "tree62_02", "up");
    add_exit(FOREST_DIR + "forest62", "down");
}


string short_desc()
{
    return "Up in the branches of a tall tree";
}
