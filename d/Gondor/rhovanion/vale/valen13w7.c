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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("Everywhere you look there is a tall, yellow grass which sways " +
        "gently in the breeze that swirls around you. Standing near the " +
        "eastern edge of a deep valley which has been carved out by the " +
        "great Anduin river as it flows down from the high mountains in the " +
        "north before emptying out into the sea far to the south. On the " +
        "far side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. East of the vale, an endless forest " +
        "of tall, black trees clearly marks the edge of the mighty " +
        "Mirkwood as the forest gazes out menacingly over the vale of " +
        "the Anduin.\n");

    add_exit(VALE_DIR + "valen12w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen12w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen13w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen14w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen14w7", "north",0,2,1);
}
