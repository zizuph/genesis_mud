/*
 * Anorien - /d/Gondor/anorien/plains/an15w3n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are passing through the northern part of Anorien, across " +
        "rolling plains and around large groves of trees. The fields are " +
        "covered with a blanket of brightly coloured wildflowers and a " +
        "tall green grass that brushes against you as it sways in the " +
        "gentle breeze. The " + VBFC("daylight_desc") + " sparkles off " +
        "the surface of the Anduin River as it flows nearby to the north " +
        "and east, while far off to the south, the snow-capped peaks of " +
        "the White Mountains stretch out across the horizon beneath the " +
        VBFC("sun_moon") + " in the " + VBFC("day_desc") + " sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an14w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w2n","northeast",0,2,1);
}
