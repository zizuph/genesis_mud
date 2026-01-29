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
    set_extraline("You have reached the top of the tree. The " +
        "tree top bends under your weight, almost as if it was " +
        "about to drop you. Looking out from the here, you see " +
        "nothing but a sea of treetops and more towering trees " +
        "above you.\n");
    set_noshow_obvious(1);
    add_exit(TREES_DIR + "tree59_03", "down");
}

string short_desc()
{
    return "At the top of a tall tree";
}
