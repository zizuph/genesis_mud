/*
 * Anorien - /d/Gondor/anorien/plains/an11w4n.c
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
    set_herbs_9();
    
    set_short("Anorien");
    set_long("You find yourself passing through fields of tall grass, their " +
        "green lengths brushing lightly against you as the wind gently blows " +
        "past. Countless wildflowers of every colour sway under the " +
        "bright light of the " + VBFC("sun_moon") + " that shines above, " +
        "while hundreds of trees gather in groves across the breadth of the " +
        "rolling plains. To the north, the mouths of the Entwash empty " +
        "into the Anduin as it runs south towards the sea. Far to " +
        "the south, the rugged peaks of the White Mountains cover the " +
        "horizon, beautifully cloaked in the " + VBFC("light_type") +
        " that falls down upon them.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an10w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an10w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an10w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an11w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an12w3n","northeast",0,2,1);
}
