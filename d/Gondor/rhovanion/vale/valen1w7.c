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
    set_items_oldroad();
    set_items_ford();
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow grass brushes against you as it sways " +
        "gently in the breeze. The wide expanse of the great river Anduin " +
        "drifts along beside you to the west, cutting through the land " +
        "to create a deep valley which runs from the north to the south. On " +
        "the other side of the valley, rocky foothills stretch high into the " +
        "clouds, where the become more appropriately known as the Misty " +
        "Mountains. An endless forest of tall, black oaks begins not far " +
        "to the east. There are many tales of Mirkwood, all of which " +
        "tell of the darkness and danger found within. Not far to the south, " +
        "you see what appears to be a wide ford cutting across the Anduin, " +
        "with a broken old road trailing away from it on either side of " +
        "the valley.\n");

    add_exit("/d/Shire/anduin/east/eford", "south",0,2,1);
    add_exit("/d/Shire/anduin/east/rd01", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen1w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen2w7", "north",0,2,1);
}
