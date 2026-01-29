/*
 * Anorien - /d/Gondor/anorien/plains/an10w4n.c
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
    set_long("You are walking through green fields filled with thousands of " +
        "colourful wildflowers and a tall grass that bends and " +
        "sways in the wind. Dozens of large tree groves litter the rolling " +
        "plains, providing a little bit of shade and shelter for the " +
        "wildlife. Far to the south, the snow-capped peaks of the White " +
        "Mountains are visible beneath the " + VBFC("day_desc") + " " +
        VBFC("sun_moon") + ". Away to the east, the mighty waters of the " +
        "Anduin River brings in new life from the mouths of the " +
        "Entwash that swirl past to the north.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an9w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an10w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an11w3n","northeast",0,2,1);
}
