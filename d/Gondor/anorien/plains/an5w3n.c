/*
 * Anorien - /d/Gondor/anorien/plains/an5w3n.c
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
    set_items_road();
    set_herbs_1();
    
    set_short("Anorien");
    set_long("You wandering in the " + VBFC("light_type") + " that shines " +
        "across the plains of Anorien, just north of a dusty road. " +
        "Colourful clusters of wildflowers are nestled beneath the fields " +
        "of tall grass, while the occasional grove of trees provides a " +
        "little bit of shade and shelter. In the distance to the north, " +
        "you can barely make out the meandering waters of the Entwash as " +
        "they slowly drain into the Anduin far to the east. As you look " +
        "to the south, the majestic heights of the White Mountains reach " +
        "high into the " + VBFC("day_desc") + " sky to stand prodly beside " +
        "the " +  VBFC("sun_moon") + " above.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr11","southwest",0,2,1);
    add_exit(ROAD_DIR + "wr10","south",0,2,1);
    add_exit(PLAINS_DIR + "an6w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an4w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an6w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an4w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an5w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an6w2n","northeast",0,2,1);
}
