/*
 * Anorien - /d/Gondor/anorien/plains/an10w5n.c
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
    set_herbs_1();
    
    set_short("Anorien");
    set_long("You are near a dusty stone road that curves through the " +
        "plains of Anorien to the southwest. The fields are covered with a " +
        "blanket of tall green grass, while large clusters of colourful " +
        "wildflowers splash their colourful hues in all directions. Tall " +
        "groves of trees have been scattered across the plains, dotting the " +
        "fields with their shade. Far to the north, the sluggish waters of " +
        "the Entwash slowly drain into the mighty Anduin River to the east. " +
        "Stretching across the southern horizon, the rocky snow-capped peaks " +
        "of the White Mountains rise up into the " + VBFC("day_desc") +
        " sky.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an10w6n","south",0,2,1);
    add_exit(ROAD_DIR + "wr6","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an9w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","northeast",0,2,1);
}
