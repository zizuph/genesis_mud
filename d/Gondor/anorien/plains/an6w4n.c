/*
 * Anorien - /d/Gondor/anorien/plains/an6w4n.c
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
    set_herbs_3();
    
    set_short("Anorien");
    set_long("It is " + VBFC("day_desc") + " in the lands of Anorien, and " +
        "you watch as the " + VBFC("light_type") + " plays on the colourful " +
        "wildflowers that hide beneath the tall green grass. Hundreds of " +
        "trees gather in groves, looking north at the sluggish waters of " +
        "the Entwash as they swirl eastward towards the Anduin river. A " +
        "dusty road cuts across the rolling plains to the south, sitting " +
        "in the shadow of the rocky heights of the White Mountains that " +
        "tower across the horizon.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr9","south",0,2,1);
    add_exit(PLAINS_DIR + "an7w5n","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr10","west",0,2,1);
    add_exit(PLAINS_DIR + "an7w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an5w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an6w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","northeast",0,2,1);
}
