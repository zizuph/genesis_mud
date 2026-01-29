/*
 * Anorien - /d/Gondor/anorien/plains/an12w6n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are wandering through fields of tall grass, their " +
        "green lengths brushing against you as the wind gently blows " +
        "past. Countless wildflowers of all colours sway under the " +
        "bright light of the " + VBFC("sun_moon") + " above, while " +
        "hundreds of trees gather in groves across the lengths of the " +
        "rolling plains. To the north, the Entwash flows east to empty " +
        "into the Anduin as it runs south towards the sea. Far to " +
        "the south, the jagged peaks of the White Mountains cover the " +
        "horizon, beautifully cloaked in the " + VBFC("light_type") +
        " that shines down upon them.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an11w7n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","south",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an11w6n","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","east",0,2,1);
    add_exit(PLAINS_DIR + "an11w5n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an12w5n","north",0,2,1);
    add_exit(PLAINS_DIR + "an13w5n","northeast",0,2,1);
}
