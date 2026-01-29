/*
 * Anorien - /d/Gondor/anorien/plains/an8w4n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are wandering across the rolling plains of Anorien in " +
        "northern Gondor. A gentle light from the " + VBFC("sun_moon") + 
        " above reveals thousands of colourful wildflowers hiding in " +
        "the tall green grass. Scattered across the fields, hundreds " +
        "of trees gather in small groves while the sluggish waters of " +
        "the Entwash pass by to the north. Far to the south, the " +
        "jagged peaks of the White Mountains are bathed in the " +
        VBFC("daylight_desc") + " as they stretch across the horizon.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an7w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an9w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an7w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","northeast",0,2,1);
}
