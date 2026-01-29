/*
 * Anorien - /d/Gondor/anorien/plains/an9w5n.c
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
    set_herbs_2();
    
    set_short("Anorien");
    set_long("A dusty stone road that cuts through the plains of Anorien " +
        "just south of you here. The fields that surround you are covered " +
        "with a blanket of tall green grass, while large clusters of " +
        "colourful wildflowers add their brilliant hues as far as the " +
        "eye can see. Dozens of tree groves have been scattered across the " +
        "plains, providing shade and sheltering all manner of wildlife. Far " +
        "to the north, the sluggish waters of the Entwash slowly drain " +
        "into the mighty Anduin River to the east. All across the southern " +
        "horizon, the rugged snow-capped peaks of the White Mountains scrape " +
        "against the " + VBFC("day_desc") + " sky.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr6","south",0,2,1);
    add_exit(ROAD_DIR + "wr7","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an8w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","northeast",0,2,1);
}
