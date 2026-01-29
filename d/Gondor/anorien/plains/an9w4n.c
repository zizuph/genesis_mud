/*
 * Anorien - /d/Gondor/anorien/plains/an9w4n.c
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
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are in the middle of the plains of Anorien, where the " 
        + VBFC("day_time") + " " + VBFC("sun_moon") + " shines down upon " +
        "rolling hills covered with a tall green grass. The fields are " +
        "filled with colourful wildflowers and groves of trees, surrounded " +
        "by the grey waters of the Entwash flowing past to the north and " +
        "the mighty Anduin river which cuts through the land to the east. " +
        "Far to the south, the jagged peaks of the White Mountains range " +
        "across the southern horizon, bathed in the " + VBFC("light_type") +
        " shining down upon them.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an8w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an9w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an8w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an10w3n","northeast",0,2,1);
}
