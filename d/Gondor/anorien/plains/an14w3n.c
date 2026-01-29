/*
 * Anorien - /d/Gondor/anorien/plains/an14w3n.c
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
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You are passing through the rolling plains of Anorien, where " +
        "gentle hills of colourful flowers and fields of tall green grass " +
        "fill the land. Hundreds of trees have collected in groves that " +
        "are sprinkled in every direction, while the plains themselves are " +
        "bordered by the roar of the Anduin as it passes nearby to the " +
        "north and east. Far away in the distance across the southern " +
        "horizon, the rugged peaks of the White Mountains thrust themselves " +
        "up into the " + VBFC("day_time") + " sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an13w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w2n","northeast",0,2,1);
}
