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
    set_extraline("This branch is much higher up in the trees. " +
        "The height is almost dizzying, but not enough to be " +
        "to upsetting. Branches sway in the wind and bend under " +
        "your weight. \n");
    set_noshow_obvious(1);
    add_exit(TREES_DIR + "tree10_03", "up");
    add_exit(TREES_DIR + "tree10_01", "down");
}


string short_desc()
{
    return "On a thick branch in a tall tree";
}
