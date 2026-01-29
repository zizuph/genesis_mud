/*
 * Anorien - /d/Gondor/anorien/plains/an11w6n.c
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
    set_long("You are just northeast of a dusty stone road that cuts across " +
        "the plains of Anorien. The fields are covered with a blanket " +
        "of tall green grass, while large clusters of colourful wildflowers " +
        "add their brilliant hues as far as the eye can see. Tall groves of " +
        "trees have been scattered across the plains, sheltering all " +
        "manner of wildlife. Far to the north, the mouths of the Entwash " +
        "slowly drain their grey waters into the mighty Anduin River to " +
        "the east. All across the southern horizon, the rugged snow-capped " +
        "peaks of the White Mountains scrape against the " + VBFC("day_desc") +
        " sky.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr5","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w7n","south",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an10w6n","west",0,2,1);
    add_exit(PLAINS_DIR + "an12w6n","east",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","north",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","northeast",0,2,1);
}
