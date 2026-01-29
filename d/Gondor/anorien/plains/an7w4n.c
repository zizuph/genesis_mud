/*
 * Anorien - /d/Gondor/anorien/plains/an7w4n.c
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
    set_long("The " + VBFC("daylight_desc") + " shines down upon " +
        "the valley of tall green grass which surrounds you. Lush green " +
        "fields stretch out in all directions, while the bright " +
        VBFC("light_type") + " washes over the groves of trees and the " +
        "thousands of wildflowers growing here. The plains are surrounded " +
        "by two large rivers, the Entwash to the north and the mighty " +
        "Anduin to the east. Stretching across the southern horizon, you " +
        "can see the tall jagged peaks of the White Mountains reaching " +
        "for the " + VBFC("day_desc") + " sky. You also notice a dusty " +
        "stone road passing nearby to the southwest.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr9","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an7w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an8w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an6w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an6w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an8w3n","northeast",0,2,1);
}
