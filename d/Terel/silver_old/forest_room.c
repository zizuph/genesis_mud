/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest_room.c
 *
 * A generic silver forest room.  All the silver forest rooms should inherit
 * this file.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#include "local.h"
#include "/d/Terel/include/herb_arrs.h"

#define MONSTER_DIR SILVER_DIR + "monster/"



#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])  



/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    
    ::create_room();
    set_short("A Silver Forest");
    set_long("You are in a large pine forest.  It looks the same " +
	     "everywhere you go.  The tops of the trees are covered with " +
	     "snow in such a way that you know why they call it the Silver " +
	     "forest.  Occasionally, an animal or two will scurry by, " +
	     "searching for food.\n");

    add_item(({"tree", "trees"}),
	     "They are tall and green.  Pine trees often do well in the " +
	     "cold.  They are covered with snow in such a way that the " +
	     "the light reflected off of them gives it a silver colour.\n");

    add_item(({"snow"}), "Don't you just wanna build a Snowman?\n");

    add_item(({"forest"}), "it's all around you... the silver forest.\n");
    add_item(({"ground"}), "the ground is covered with fallen leaves, " +
	     "various plants and snow.\n");
    
    OUTSIDE;
    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"trees","bushes","undergrowth",
                    "plants","shrub","tree","shrubs","here"}) , 3 );

}

