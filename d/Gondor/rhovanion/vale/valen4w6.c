/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";

void 
create_vale_room()
{
    set_items_vale();
    set_items_east();
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("You are standing on the slopes of a deep valley, surrounded " +
        "by fields of tall, yellow-green grasses which bend and sway with " +
        "the gentle breezes that swirl around you. In the middle of the " +
        "vale, the great river Anduin churns as those powerful waters cut " +
        "through the land on its long journey south towards the sea. On " +
        "the western shore, rocky foothills march up to the rugged wall " +
        "of the Misty Mountains, whose jagged peaks are lost in the clouds " +
        "high above. Shadows lurk behind an endless line of tall, black " +
        "trees which spread across the entire eastern horizon. These woods, " +
        "best known as Mirkwood forest, have been the subject of countless " +
        "tales of danger and darkness.\n");

    add_exit(VALE_DIR + "valen3w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen3w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen4w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen5w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen5w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen5w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen4w7", "west",0,2,1);
    add_exit(VALE_DIR + "valen3w7", "southwest",0,2,1); 
}
