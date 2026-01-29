/*
 * Anorien - /d/Gondor/anorien/plains/an14w5n.c
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
    set_herbs_1();
    
    set_short("Anorien");
    set_long("You are following a shallow valley, filled with colourful " +
        "wildflowers and a tall green grass that bends in the wind, " +
        "somewhere in the eastern fields of Anorien. To the north and " +
        "east, the tumbling waters of the Anduin River flow past, " +
        "watched over by the tree groves that are scattered all across " +
        "the plains. Far to the south, the jagged peaks of the White " +
        "Mountains stretch up in the " + VBFC("daylight_desc") + " and " +
        "run off in the distance to the west.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an13w6n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","northeast",0,2,1);
}
