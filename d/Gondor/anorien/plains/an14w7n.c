/*
 * Anorien - /d/Gondor/anorien/plains/an14w7n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

void 
create_plains_room()
{
    set_items_plains();
    set_herbs_3();
    
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

    add_exit(PLAINS_DIR + "an13w8n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w8n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w7n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w6n","northeast",0,2,1);
}
