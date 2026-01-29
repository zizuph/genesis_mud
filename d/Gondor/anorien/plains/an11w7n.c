/*
 * Anorien - /d/Gondor/anorien/plains/an11w7n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are in the green, grassy fields of Anorien where " +
        "the " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " illuminates the rolling plains that " +
        "surround you. The fields are full of colourful wildflowers which " +
        "encircle the countless groves of trees. Looking south, the " + 
        VBFC("daylight_desc") + " reveals a dusty stone road which runs " +
        "through the green fields, while the snow-capped peaks of the " +
        "White Mountains stand guard overhead. To the north, the mouths of " +
        "the Entwash sluggishly swirl through marshy fens as they empty " +
        "into the rushing waters of the Anduin River to the east.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr4","south",0,2,1);
    add_exit(PLAINS_DIR + "an12w8n","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr5","west",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","east",0,2,1);
    add_exit(PLAINS_DIR + "an10w6n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","north",0,2,1);
    add_exit(PLAINS_DIR + "an12w6n","northeast",0,2,1);
}
