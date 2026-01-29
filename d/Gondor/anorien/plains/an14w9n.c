/*
 * Anorien - /d/Gondor/anorien/plains/an14w9n.c
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
    set_herbs_4();
    
    set_short("Anorien");
    set_long("You are passing the fields of Anorien, a short way from " +
        "the ruins of Osgiliath which lies on the banks of the Anduin River " +
        "to the east. To the south, a great stone wall rises up behind the " +
        "dusty roads, encircling the massive citadel of Minas Tirith as it " +
        "guards Gondor from its seat on the slopes of the White Mountains " +
        "to the southwest. To the north, rolling plains of tall green grass " +
        "are filled with groves of trees and colourful wildflowers, which " +
        "bathe in the light of the " + VBFC("day_time") + " " + 
        VBFC("sun_moon") + " above.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr2","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w10n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w9n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w8n","northeast",0,2,1);
}
