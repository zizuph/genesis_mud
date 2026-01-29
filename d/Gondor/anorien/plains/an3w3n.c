/*
 * Anorien - /d/Gondor/anorien/plains/an3w3n.c
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
    set_long("You are just north of a dusty stone road that cuts through " +
        "the plains of Anorien. The fields are covered with a blanket " +
        "of tall green grass, while large clusters of colourful wildflowers " +
        "add their brilliant hues as far as the eye can see. Tall groves of " +
        "trees have been scattered across the plains, sheltering all " +
        "manner of wildlife. Far to the north, the sluggish waters of the " +
        "Entwash slowly drain into the mighty Anduin River to the east. " +
        "All across the southern horizon, the rugged snow-capped peaks " +
        "of the White Mountains scrape against the " + VBFC("day_desc") +
        " sky.\n");

    add_trees(1);

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr12","south",0,2,1);
    add_exit(ROAD_DIR + "wr11","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr13","west",0,2,1);
    add_exit(PLAINS_DIR + "an4w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an2w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an3w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an4w2n","northeast",0,2,1);
}
