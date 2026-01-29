/*
 * Anorien - /d/Gondor/anorien/plains/an4w3n.c
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
    set_herbs_9();
    
    set_short("Anorien");
    set_long("You are wandering through the rolling plains of Anorien, not " +
        "far from a dusty stone road that carves a path just south of here. " +
        "The " + VBFC("light_type") + " dances across the thousands of " +
        "colourful wildflowers hiding in the tall grass, while dozens of " +
        "oak, elm and fir trees grow in thick groves which have been " +
        "scattered across the fields. Across the southern horizon, the " +
        "rugged peaks of the White Mountains stretch up towards the " +
        VBFC("sun_moon") + " in the sky above, overlooking the rivers " +
        "that frame the plains in the far distance to both the north and " +
        "east.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr12","southwest",0,2,1);
    add_exit(ROAD_DIR + "wr11","south",0,2,1);
    add_exit(ROAD_DIR + "wr10","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an3w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an5w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an3w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an4w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an5w2n","northeast",0,2,1);
}
