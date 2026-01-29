/*
 * Anorien - /d/Gondor/anorien/plains/an6w3n.c
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
    set_long("You are wandering through fields filled with thousands of " +
        "colourful wildflowers and a tall green grass that bends and " +
        "sways in the wind. Several groves of trees litter the rolling " +
        "plains, providing a little bit of shade and shelter for the " +
        "wildlife. Far to the south, past the dusty stone road that " +
        "passes nearby to the southwest, are the snow-capped peaks of " +
        "the White Mountains. In the distance to the east, the mighty " +
        "Anduin River brings in new life from the mouths of the " +
        "Entwash to the north.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr10","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an6w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an7w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an5w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an5w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an6w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an7w2n","northeast",0,2,1);
}
