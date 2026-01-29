/*
 * Anorien - /d/Gondor/anorien/plains/an13w7n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are passing through the green fields that cover " +
        "the rolling plains of Anorien, watching as the tall grass shakes " +
        "in the wind. Hundreds of trees have gathered beneath the " +
        VBFC("day_time") + " " + VBFC("sun_moon") + " to form several " +
        "dense groves that have been sprinkled across the fields. " +
        "Off to the east, the mighty Anduin river cuts through the land, " +
        "fed by the grey waters flowing through the mouths of the " +
        "Entwash. Marching across the southern horizon, the rocky " +
        "peaks of the White Mountains reach up to brush the " +
        VBFC("day_desc") + " sky above.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an12w8n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w6n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w6n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w6n","northeast",0,2,1);
}
