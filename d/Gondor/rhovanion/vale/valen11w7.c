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
    set_items_river();
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("You are surrounded by the tall yellowish grass which grows all " +
        "across the slopes of the deep valley you are in. Rushing down " +
        "through the middle of the valley is the great river Anduin, " +
        "running southwards towards the sea. Across to the west, on the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, the tall, black trees of " +
        "a forest tower over the edge of the valley. The shadows of " +
        "Mirkwood are deep and ominous, their dark reputation seemingly " +
        "well earned.\n");

    add_exit(VALE_DIR + "valen10w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen10w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen11w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen12w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen12w7", "north",0,2,1);
}
