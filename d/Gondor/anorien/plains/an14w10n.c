/*
 * Anorien - /d/Gondor/anorien/plains/an14w10n.c
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
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are wandering across the fields of Anorien, not far from " +
        "the ruined city of Osgiliath that lies on the banks of the Anduin " +
        "to the east. To the south, a great wall rises up behind the dusty " +
        "roads that travel around it, encircling the massive citadel of " +
        "Minas Tirith as it perches on the slopes of the White Mountains " +
        "to the southwest. To the north, rolling fields of tall grass are " +
        "filled with groves of trees and colourful wildflowers, which dance " +
        "in the breeze beneath the " + VBFC("day_time") + " " + 
        VBFC("sun_moon") + ".\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr1","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w11n","south",0,2,1);
    add_exit(ROAD_DIR + "wr2","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w9n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","east",0,2,1);
    add_exit(PLAINS_DIR + "an15w11n","southeast",0,2,1);
}
