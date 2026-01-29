/*
 * Anorien - /d/Gondor/anorien/plains/an13w4n.c
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
    set_herbs_2();
    
    set_short("Anorien");
    set_long("You are wandering somewhere amidst the rolling plains " +
        "of Anorien, enjoying the " + VBFC("light_type") + " as it " +
        "bathes the tall green grass. Clusters of colourful wildflowers " +
        "are scattered across the grassy fields, while dozens of tree " +
        "groves huddle in the valleys. The plains are surrounded by " +
        "the Entwash to the north as it empties into the Anduin River " +
        "in the east. Far to the south, the jagged peaks of the " +
        "White Mountains claw at the " + VBFC("sun_moon") + " in the " +
        "sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an12w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","northeast",0,2,1);
}
