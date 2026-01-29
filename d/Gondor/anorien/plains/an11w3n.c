/*
 * Anorien - /d/Gondor/anorien/plains/an11w3n.c
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
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You find yourself wandering along the rolling plains " +
        "of Anorien, enjoying the " + VBFC("light_type") + " as it " +
        "shines down on the tall green grass. Colourful wildflowers " +
        "are scattered all across the grassy fields, while several tree " +
        "groves huddle deep in the valleys. The plains are surrounded by " +
        "the grey water flowing through the mouths of the Entwash to the " +
        "north as it empties into the mighty Anduin River " +
        "in the east. Far to the south, the snow-capped peaks of the " +
        "White Mountains reach for the " + VBFC("sun_moon") + " in the " +
        "sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an10w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an10w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an12w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an10w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an12w2n","northeast",0,2,1);
}
