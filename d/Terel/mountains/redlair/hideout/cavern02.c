/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Notorious Hand Cell Hideout
 * Tomas  -- May 2000
 */

#include "/d/Terel/include/Terel.h"

inherit MOUNTAIN_DIR + "redlair/hideout/include/cavern_base";

#define  DEFAULT   MOUNTAIN_DIR + "redlair/hideout/"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short(query_short());
    set_long(query_long() +
             "The river continues to run along the middle of the " +
           "cavern. A wooden walkway leads along the river " +
           "to the southeast.\n");

    add_item(({"river","riverbank","water","bank"}),
               "The river runs " +
               "through the middle of the cavern twisting and turning " +
               "around stalagmites and large boulders. The water " +
               "is clear allowing you to see to the bottom in most " +
               "areas. Small plants grow just below the surface of the " +
               "water along the riverbank and on the edges of the rocks.\n");
    add_item(({"walkway","wooden walkway","wood"}),
               "The walkway is comprised of old wooden planks fitted " +
               "loosely together. Over time, the planks have become " +
               "twisted and rotted due to over exposure due to moisture. " +
               "The walkway leads along the riverbank.\n");
                
    
    add_exit(DEFAULT + "cavern01", "northwest",0,4);
    add_exit(DEFAULT + "cavern03", "southeast",0,4);


    reset_room();
}
