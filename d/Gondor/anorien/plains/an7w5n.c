/*
 * Anorien - /d/Gondor/anorien/plains/an7w5n.c
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
    set_long("You are just north of a dusty stone road amongst the " +
        "rolling plains of Anorien in Gondor. Fields of tall green grass " +
        "bend and sway in the wind, beckoning to the colourful wildflowers " +
        "and the huddled groves of trees that cover the plains. Far to the " +
        "north, the sluggish waters of the Entwash slowly deposit " +
        "themselves into the great river known as the Anduin to the east. " +
        "On the other side of the road, massive mountains thrust up high " +
        "into the " + VBFC("day_desc") + " sky, the jagged peaks clawing " +
        "at the " + VBFC("sun_moon") + " high above.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr8","south",0,2,1);
    add_exit(ROAD_DIR + "wr7","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr9","west",0,2,1);
    add_exit(PLAINS_DIR + "an8w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an6w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an7w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","northeast",0,2,1);
}
