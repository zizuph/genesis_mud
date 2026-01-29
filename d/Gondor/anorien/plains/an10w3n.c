/*
 * Anorien - /d/Gondor/anorien/plains/an10w3n.c
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
    set_herbs_4();
    
    set_short("Anorien");
    set_long("You are wandering through the tall green grass that covers " +
        "the rolling plains of Anorien. Hundreds of trees have gathered " +
        "to form dense groves that have been sprinkled across the fields. " +
        "Off to the east, the mighty Anduin river cuts through the land, " +
        "fed by the grey waters flowing through the mouths of the " +
        "Entwash. Marching across the southern horizon, the rocky " +
        "peaks of the White Mountains reach up to brush the " +
        VBFC("day_desc") + " sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an9w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an11w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an9w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an11w2n","northeast",0,2,1);
}
