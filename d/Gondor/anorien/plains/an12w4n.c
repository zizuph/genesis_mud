/*
 * Anorien - /d/Gondor/anorien/plains/an12w4n.c
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
    set_long("You are in the middle of Anorien, surround by fields of tall " +
        "green grass and rolling hills. Countless trees have gathered into " +
        "groves, surrounded by clusters of bright wildflowers of every " +
        "colour. To the south, the snow-capped peaks of the White Mountains " +
        "are clearly visible in the " + VBFC("daylight_desc") + ", watching " +
        "carefully over the plains. To the north, the mouths of the Entwash " +
        "slowly empty their grey waters into the Anduin as it rushes " +
        "past not far to the east.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an11w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an13w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an11w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","northeast",0,2,1);
}
