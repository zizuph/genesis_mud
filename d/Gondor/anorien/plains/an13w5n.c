/*
 * Anorien - /d/Gondor/anorien/plains/an13w5n.c
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
    set_herbs_3();
    
    set_short("Anorien");
    set_long("You are journeying through the lands of Anorien, where the " +
        "rolling plains are carpeted in fields of brilliant wildflowers and " +
        "tall green grass surround you. Scattered across the land are " +
        "several tree groves, providing shade and shelter for all manner " +
        "of wildlife. The southern horizon is filled with the rugged " +
        "peaks of the White Mountains, while the " + VBFC("daylight_desc") +
        " reveals the rushing waters of the Anduin flowing around the " +
        "edges of Anorien to the north and east.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an12w6n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","northeast",0,2,1);
}
