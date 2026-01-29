/*
 * Anorien - /d/Gondor/anorien/plains/an11w5n.c
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
    set_long("The " + VBFC("daylight_desc") + " looks down as you pass " +
        "through a green valley filled with tall grass in the middle of " +
        "Anorien. Just over the crest of a low hill to the north, you can " +
        "see the marshy lands that surround the mouths of the Entwash as " +
        "its grey water slowly empties into the roar of the Anduin River to " +
        "the east. The rugged peaks of the White Mountains reach across the " +
        "southern horizon, stretching up to reach the " +
        VBFC("sun_moon") + " in the " + VBFC("day_time") + " sky above. " +
        "Scattered around the grassy fields in this valley are several " +
        "groves of trees, harbouring all manner of wildlife.\n");  

    add_trees(1);

    add_item(({"vale", "valley", "hill", "crest", "hills", "northern hill"}),
        "You are in a small valley, tucked in between a couple of low hills " +
        "in the lands of Anorien. Just over the crest of the northern hill, " +
        "you can see the mashlands which surround the sluggish waters " +
        "of the Entwash.\n");

    add_exit(PLAINS_DIR + "an10w6n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","south",0,2,1);
    add_exit(PLAINS_DIR + "an12w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an10w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","northeast",0,2,1);
}
