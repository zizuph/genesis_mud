/*
 * Anorien - /d/Gondor/anorien/plains/an15w6n.c
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
    set_herbs_4();
    
    set_short("Anorien");
    set_long("The " + VBFC("daylight_desc") + " shines down upon the rolling " +
        "plains of eastern Anorien, illuminating the land around you. " +
        "Tall trees gather in secluded groves, while fields of colourful " +
        "wildflowers and tall green grass blanket the low hills that " +
        "rise and fall across the plains. To the north and east, the " +
        "rushing waters of the Anduin River cut through the land while " +
        "across the southern horizon, the rocky peaks of the White " +
        "Mountains jut up into the " + VBFC("day_time") + " sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w7n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w7n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w7n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w6n","east",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w5n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w5n","northeast",0,2,1);
}
