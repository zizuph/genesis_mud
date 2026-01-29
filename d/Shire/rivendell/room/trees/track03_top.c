/*
 * Up in trees in Rivendell forest
 * By Finwe, March 1999
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit TREES_BASE;

void add_stuff();
 
void
create_tree_room()
{
    set_extraline("You have reached the top of the tree. The " +
        "tree top bends under your weight, almost as if it was " +
        "about to drop you. Looking out from the here, you see " +
        "nothing but a sea of treetops and more towering trees " +
        "above you.\n");
    set_noshow_obvious(1);
    add_exit(TREES_DIR + "track03_03", "down");
    add_stuff();
}

 
string short_desc()
{
    return "At the top of a tall tree";
}

void reset_shire_room()
{
    add_stuff();
}


void
add_stuff()
{
   object feather1, feather2, feather3;

    if(!present("_imladris_feather_"))
   {
   feather1 = clone_object(ROBJ_DIR + "feather");
   feather1->move(TO);

   feather2 = clone_object(ROBJ_DIR + "feather");
   feather2->move(TO);

   feather3 = clone_object(ROBJ_DIR + "feather");
   feather3->move(TO);
   }

}
