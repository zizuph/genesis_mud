/*
 * Anorien - /d/Gondor/anorien/plains/an10w6n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

/*
 * Function name:        create_plains_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/base.c
 */
void 
create_plains_room()
{
    set_items_plains();
    set_items_road();
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are in the middle of Anorien, just north of a dusty " +
        "stone road which runs from east to west. The rolling plains " +
        "that surround you are filled with a tall green grass that " +
        "bends with every breeze that blows past. Groves of trees and " +
        "colourful wildflowers seem to be scattered all across the " +
        "fields, while far to the north, the mouths of the Entwash " +
        "slowly drain into the roaring waters of the Anduin river. " +
        "Standing tall in the " + VBFC("daylight_desc") + " are the " +
        "White Mountains that reach across the entire length of the " +
        "southern horizon.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr5","south",0,2,1);
    add_exit(PLAINS_DIR + "an11w7n","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr6","west",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","east",0,2,1);
    add_exit(PLAINS_DIR + "an9w5n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","north",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","northeast",0,2,1);
}
