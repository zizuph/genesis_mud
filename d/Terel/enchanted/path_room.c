/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge_room.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Path");
    set_long("You are on a path that leads through a large forest " +
	     "of mixed trees, mostly conifers and some deciduous.  " +
	     "The small path looks very old and is laden with stones. " +
	     "An air of enchantment comes from the depths of the forest.\n");

    add_item("path",
	     "It looks very old and worn by many travellers.  Many\n" + 
	     "stones have been placed along it, thus it will stay easily\n" +
	     "in view, despite the ravages of nature.\n");
   
    add_item("trees",
	     "Countless numbers of trees, many ancient, some\n" + 
	     "only young sapling awaiting their chance to grow. The trees\n" + 
	     "amoungst each other for dominance, some never make it.\n");
   
    add_item("stones",
	     "Brought by many travellers, these stones come from\n" + 
	     "all over, as told by their differing colors and shapes.\n");
}

