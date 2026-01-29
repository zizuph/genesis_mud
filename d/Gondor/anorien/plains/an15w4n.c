/*
 * Anorien - /d/Gondor/anorien/plains/an15w4n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

void 
create_plains_room()
{
    set_items_plains();
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are wandering through the tall green grass that grows " +
        "all across the rolling plains of northern Anorien. Nearby, the " +
        "rushing waters of the Anduin River cuts through the fields of " +
        "wildflowers and secluded tree groves as it passes through the " +
        "lands of Gondor on its journey to the sea. Far in the distance, " +
        "the jagged peaks of the White Mountains rest quietly beneath " +
        "the " + VBFC("sun_moon") + " in the " + VBFC("day_time") + " sky.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w3n","northeast",0,2,1);
}
