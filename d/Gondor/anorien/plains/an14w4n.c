/*
 * Anorien - /d/Gondor/anorien/plains/an14w4n.c
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
    set_herbs_9();
    
    set_short("Anorien");
    set_long("You find yourself wandering through rolling fields of tall " +
        "grass, their green lengths brushing gently against you as the " +
        "breeze gently blows by. Countless wildflowers of every colour " +
        "bloom under the bright light of the " + VBFC("sun_moon") + " that " +
        "shines above, while hundreds of trees gather in groves across the " +
        "length of the rolling plains. To the north and east, the rushing " +
        "waters of the Anduin River run south towards the sea. Far to " +
        "the south, the rugged peaks of the White Mountains cover the " +
        "horizon, beautifully cloaked in the " + VBFC("light_type") +
        " that falls down upon them.\n");

    add_exit(PLAINS_DIR + "an13w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w5n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","northeast",0,2,1);
}
