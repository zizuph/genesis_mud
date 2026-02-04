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
             "The river disappears into a dark and forboding crack " +
           "along the southern rockface. A wooden walkway ends here " +
           "before a makeshift robe bridge extending over the river.\n");

    add_item(({"river","riverbank","water","bank"}),
               "The river disappears into a a dark and forboding " + 
               "crack along the southern wall. It looks impossible " +
               "to survive the passage beyond.\n");
    add_item(({"walkway","wooden walkway","wood"}),
               "The walkway is comprised of old wooden planks fitted " +
               "loosely together. Over time, the planks have become " +
               "twisted and rotted due to over exposure due to moisture. " +
               "The walkway ends before a makeshift rope bridge.\n");
    add_item(({"bridge","rope bridge","rope"}),
               "The rope bridge extends over the river to the east. " +
               "The rope appears to be fairly new stretching on either " +
               "side of its wooden plank walkway.\n");
                
    
    add_exit(DEFAULT + "cavern03", "northwest",0,4);
    add_exit(DEFAULT + "cavern05","bridge");



    reset_room();
}