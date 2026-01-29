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
    set_extraline("This is near the top of the tree. The " +
        "branches thin out up here, making it difficult to stay " +
        "in the tree. the branches sway more dangerously here " +
        "and bend under your weight considerably.\n");
    set_noshow_obvious(1);
    add_exit(TREES_DIR + "tree31_top", "up");
    add_exit(TREES_DIR + "tree31_02", "down");
}

 
string short_desc()
{
    return "Near the top of a tall tree";
}
