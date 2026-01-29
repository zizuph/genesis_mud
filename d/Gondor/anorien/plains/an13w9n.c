/*
 * Anorien - /d/Gondor/anorien/plains/an13w9n.c
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
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You are just northeast of a dusty stone road that cuts " +
        "through the rolling plains of Anorien. Rising up across the " +
        "southern horizon, the massive snow-capped peaks of the White " +
        "Mountains reach up towards the " + VBFC("sun_moon") + " in the " +
        VBFC("day_time") + " sky above. Spread out before you, are " +
        "fields of colourful wildflowers and a tall green grass that " +
        "bends and sways in the wind, while further north and east, the " +
        "great river Anduin cuts through the land on its journey to the "+
        "sea.\n");

    add_trees(1);

    add_item(({"forest","druadan forest","druadan"}),
        "On the far side of the road, you can see the tangled green depths " +
        "of the Druadan forest. It is rumoured that wild men inhabit the " +
        "forest, unfriendly to any who enter their domain.\n");

    set_no_exit_msg(({"southwest"}),
        "The forest on the other side of the road is just too thick " +
        "for you to enter from here, but you can go west or south to " +
        "get onto the road directly.\n");

    add_exit(ROAD_DIR + "wr2","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w10n","southeast",0,2,1);
    add_exit(ROAD_DIR + "wr3","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","east",0,2,1);
    add_exit(PLAINS_DIR + "an12w8n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w8n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","northeast",0,2,1);
}
