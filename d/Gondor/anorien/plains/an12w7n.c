/*
 * Anorien - /d/Gondor/anorien/plains/an12w7n.c
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
    set_long("Fields full of tall green grass and bright wildflowers of " +
        "all colours surround you in every direction. Several groves of " +
        "tall trees also dot the rolling plains of Anorien, offering the " +
        "solace of shade and shelter. The massive snow-covered peaks of " +
        "the White Mountains run across the southern horizon, looking " +
        "down upon the dusty stone road that passes nearby to the " +
        "southwest. In the distance to the north, the mouths of the " +
        "Entwash sluggishly deposit their swirling grey waters into " +
        "the Anduin river which cuts through the land to the east.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr4","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w8n","south",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an11w7n","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","east",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w6n","north",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","northeast",0,2,1);
}
