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
             "The river is being fed through a jagged crack high " +
           "above on the northern wall decending downwards " + 
           "crashing to the rocks and stalagmites below. A wooden " +
           "walkway leads from the mouth of the mine shaft along " +
           "river to the southeast.\n");

    add_item(({"river","riverbank","water","bank"}),
               "The underground river is fed from a large jagged fissure " +
               "high above on the northern rockface. The river runs " +
               "through the middle of the cavern twisting and turning " +
               "around stalagmites and large boulders. The water " +
               "is clear allowing you to see to the bottom in most " +
               "areas. Small plants grow just below the surface of the " +
               "water along the riverbank and on the edges of the rocks.\n");
    add_item(({"jagged fissure","fissure","crack"}),
               "The large fissure looks as if it was torn right out of " +
               "the jagged rockface by some earthquake long ago. " +
               "Water pours from the crack creating a magnificent looking " +
               "waterfall, crashing to the rocks below.\n");
    add_item(({"waterfall"}),"The waterfall sparkles in the dim light " +
               "as it falls to the rocks below.\n");     
    add_item(({"walkway","wooden walkway","wood"}),
               "The walkway is comprised of old wooden planks fitted " +
               "loosely together. Over time, the planks have become " +
               "twisted and rotted due to over exposure due to moisture. " +
               "The walkway leads along the riverbank.\n");
    add_item(({"shaft","mine shaft"}),
               "To the south, is the entrance to what looks like a mine " +
               "shaft.\n");
                
    
    add_exit(DEFAULT + "shaft12", "south");
    add_exit(DEFAULT + "cavern02", "southeast",0,4);


    reset_room();
}