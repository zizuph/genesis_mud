/*
 * Anorien - /d/Gondor/anorien/plains/an12w8n.c
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
    set_long("You are standing just northeast of the dusty stone road which " +
        "cuts through the rolling plains of Anorien. Green fields of tall " +
        "grass sway in the wind, beckoning to the thousnads of colourful " +
        "wildflowers and the huddled groves of trees that cover the plains. " +
        "Far to the north, the sluggish waters of the Entwash slowly deposit " +
        "themselves into the great river known as the Anduin to the east. " +
        "On the other side of the road, rugged mountains thrust up high " +
        "into the " + VBFC("day_desc") + " sky, their snow-capped peaks " +
        "clawing at the " + VBFC("sun_moon") + " high above.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr3","south",0,2,1);
    add_exit(PLAINS_DIR + "an13w9n","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr4","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","east",0,2,1);
    add_exit(PLAINS_DIR + "an11w7n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","north",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","northeast",0,2,1);
}
