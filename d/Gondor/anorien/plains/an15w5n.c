/*
 * Anorien - /d/Gondor/anorien/plains/an15w5n.c
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
    set_herbs_5();
    
    set_short("Anorien");
    set_long("Colourful wildflowers and tall grass fill your vision as you " +
        "travel through the rolling fields of Anorien. Dozens of trees " +
        "have gathered into groves that are scattered across the plains " +
        "which is bordered by the rushing waters of the Anduin River to " +
        "the north and east. Illuminated by the " + VBFC("light_type") + 
        ", you can see the rocky peaks of White Mountains as they stretch " +
        "out across the entire length of the southern horizon.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w6n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w6n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w6n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an14w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w4n","northeast",0,2,1);
}
