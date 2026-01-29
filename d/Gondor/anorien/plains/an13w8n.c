/*
 * Anorien - /d/Gondor/anorien/plains/an13w8n.c
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
    set_items_anduin();
    set_items_road();
    set_herbs_5();
    
    set_short("Anorien");
    set_long("You are travelling across the green plains of Anorien, where " +
        "the land is filled with plentiful tree groves and fields of " +
        "colourful wildflowers and a tall grass that sways in the wind. " +
        "The " + VBFC("day_time") + " " + VBFC("sun_moon") + " reveals " +
        "a dusty stone road passing nearby to the southwest, hidden beneath " +
        "the jagged peaks of the White Mountains that dominate the " +
        "southern horizon. In the distance to the north and east, the " +
        "turbulent waters of the Anduin river crash through the land, " +
        "making their way towards the sea.\n");
    
    add_trees(1);

    add_exit(ROAD_DIR + "wr3","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w9n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w8n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w7n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w7n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w7n","northeast",0,2,1);
}
