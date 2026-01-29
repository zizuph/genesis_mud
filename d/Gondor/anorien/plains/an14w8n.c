/*
 * Anorien - /d/Gondor/anorien/plains/an14w8n.c
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
    set_herbs_4();
    
    set_short("Anorien");
    set_long("You are travelling across the low rolling plains of Anorien. " +
    "Brightly coloured wildflowers hide behind the tall green grass which " +
    "covers the fields, partially interupted by the occasional grove of " +
    "trees. To the north and east, the great river Anduin carves its " +
    "path through the land and the " + VBFC("light_type") + " sparkles " +
    "on its surface in the distance. Jagged snow-capped peaks rise up " +
    "to the south and west, as the White Mountains stretch out across " +
    "the horizon.\n");

    add_trees(1);
    
    add_exit(PLAINS_DIR + "an13w9n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w8n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","north",0,2,1);
    add_exit(PLAINS_DIR + "an15w7n","northeast",0,2,1);
}
