/*
 * Anorien - /d/Gondor/anorien/plains/an13w3n.c
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
    set_herbs_1();
    
    set_short("Anorien");
    set_long("Bright " + VBFC("daylight_desc") + " shines down from the " +
        VBFC("day_time") + " " + VBFC("sun_moon") + ", illuminating the " +
        "rolling plains of Anorien that surround you. Brightly coloured " +
        "wildflowers and fields of tall green grass engulf the land, " +
        "broken only by the groves of trees that dot the plains. To the " +
        "north, the mouths of the Entwash slowly flood the land as they " +
        "feed the mighty Anduin river as it continues its journey through " +
        "Gondor. In the distance, spread out across the southern horizon, " +
        "you can see the snow-capped peaks of the White Mountains which " +
        "overlook the land.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an12w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w2n","northeast",0,2,1);
}
