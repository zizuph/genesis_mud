/*
 * Anorien - /d/Gondor/anorien/plains/an14w11n.c
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
    set_items_road();
    set_items_city();
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You passing through the southern part of Anorien, just west " +
        "of the ruins of Osgiliath with Rammas Echor on the other " +
        "side of the road to the south. To the west, the White Mountains " +
        "begin their march across the length of Gondor, while to the " +
        "east, the " + VBFC("day_time") + " " + VBFC("sun_moon") + 
        " sparkles along the surface of the Anduin River. Rolling fields " +
        "of wildflowers and tall green grass stretch out to the north, " +
        "broken only by the countless tree groves that dot the plains.\n");

    add_trees(1);

    add_exit(ANORIEN_DIR + "pelennor/noutgate","southwest",0,2,1);
    add_exit(ROAD_DIR + "or1","south",0,2,1);
    add_exit(ROAD_DIR + "wr1","west",0,2,1);
    add_exit(ROAD_DIR + "wr2","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w10n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an15w11n","east",0,2,1);
    add_exit(ROAD_DIR + "or2","southeast",0,2,1);
}
