/*
 * Anorien - /d/Gondor/anorien/plains/an15w7n.c
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
    set_long("The " + VBFC("daylight_desc") + " shines down upon " +
        "the valley of tall green grass which surrounds you. Lush green " +
        "fields stretch out in all directions, while the bright " +
        VBFC("light_type") + " washes over the groves of trees and the " +
        "thousands of wildflowers growing here. The plains are surrounded " +
        "by mighty Anduin as its grey waters rush nearby to the north and " +
        "east. Stretching across the southern horizon, you " +
        "can see the tall jagged peaks of the White Mountains reaching " +
        "for the " + VBFC("day_desc") + " sky.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w8n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w8n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w8n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w7n","east",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w6n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w6n","northeast",0,2,1);
}
