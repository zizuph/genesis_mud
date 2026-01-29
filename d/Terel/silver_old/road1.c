/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road1.c
 *
 * Road from northern edge to centre. Connects with forest. 
 * Northern edge of Calathin, where it intersects with the south of 
 * the forest.  Lightly inhabited here, some trees.  Descs taken    
 * from Vader's forest, for consistency.                            
 * 
 * metaprat - 920622 
 * Modified by Sorgum 921002
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Road through Silver Forest");
    set_long("You are on a road through a large pine forest.  " +
	     "Towards the south, you can see a huge pine tree " +
	     "towering towards the sky, marking the " +
	     "edge of the town of Calathin.  The tops of the trees " +
	     "are covered with snow, the light reflecting off them " +
	     "giving a silver colour.\n",);

    add_item(({"trees", "tree"}),
	     "They are tall and green.  Pine trees " +
	     "often do well in the cold.  They are covered with snow " +
	     "in such a way that the light reflected off of them " +
	     "gives it a silver color.\n");

    add_item( ({"huge tree"}),
	      "The tree looks like an ancient pine, about 100 meters " +
	      "tall or more.\n");

    add_item(({"snow"}), "Don't you just wanna build a Snowman?\n");
    
    add_exit(SILVER_DIR + "forest2",           "north", 0);
    add_exit(CALATHIN_DIR + "north_gate", "south", 0);

}
