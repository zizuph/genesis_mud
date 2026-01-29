/*
 * Anorien - /d/Gondor/anorien/plains/an12w3n.c
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
    set_long("You are wandering through fields of tall grass, their " +
        "green lengths brushing against you as the wind gently blows " +
        "past. Countless wildflowers of all colours sway under the " +
        "bright light of the " + VBFC("sun_moon") + " above, while " +
        "hundreds of trees gather in groves across the lengths of the " +
        "rolling plains. To the north, the mouths of the Entwash empty " +
        "into the Anduin as it runs south towards the sea. Far to " +
        "the south, the jagged peaks of the White Mountains cover the " +
        "horizon, beautifully cloaked in the " + VBFC("light_type") +
        " that shines down upon them.\n");

    add_exit(PLAINS_DIR + "an11w4n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w4n","south",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an11w3n","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","east",0,2,1);
    add_exit(PLAINS_DIR + "an11w2n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w2n","north",0,2,1);
    add_exit(PLAINS_DIR + "an13w2n","northeast",0,2,1);
}
