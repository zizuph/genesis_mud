/*
 * Anorien - /d/Gondor/anorien/plains/an14w6n.c
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
    set_herbs_2();
    
    set_short("Anorien");
    set_long("You are wandering across the rolling plains of Anorien, where " +
        "low hills and shallow valleys are covered in a colourful blanket " +
        "of wildflowers and tall green grass. Hundreds of trees collect " +
        "themselves in small groves, offering shade and shelter for any " +
        "who might seek it in these lands. To the north and east, the " +
        "rushing waters of the Anduin River flow past, carving a wide " +
        "path to the sea. Marching across the southern horizon, standing " +
        "proud in the " + VBFC("light_type") + " are the rocky peaks of " +
        "the White Mountains.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an13w7n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w7n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w6n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w5n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w5n","northeast",0,2,1);
}
