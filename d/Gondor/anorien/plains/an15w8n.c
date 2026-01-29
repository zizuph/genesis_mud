/*
 * Anorien - /d/Gondor/anorien/plains/an15w8n.c
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
    set_items_city();
    set_herbs_2();
    
    set_short("Anorien");
    set_long("You are wandering across the rolling plains of Anorien, not " +
        "far from the ruins of Osgiliath which are visible on the horizon " +
        "to the southeast. Nearby, the rushing waters of the Anduin cut " +
        "through grassy fields filled with groves of trees and wildflowers. " +
        "Farther away, to the south and west, the rugged White Mountains " +
        "stretch up towards the " + VBFC("sun_moon") + " up in the " +
        VBFC("day_time") + " sky above, while a large stone citadel " +
        "perches carefully upon its eastern edge.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w9n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w7n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w7n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an16w8n","east",0,2,1);
    add_exit(PLAINS_DIR + "an16w9n","southeast",0,2,1);
}
