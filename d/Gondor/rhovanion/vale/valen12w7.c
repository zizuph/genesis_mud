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
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("You standing on the eastern banks of the great river, known " +
        "more commonly as the Anduin. The river carves a deep valley as it " +
        "tumbles down from the north on its journey to the sea in the south. " +
        "Spread across the rugged slopes of the valley, the broad carpet of " +
        "tall, yellow grass brushes against you as it sways " +
        "in the breeze. On the far side of the valley, rocky foothills " +
        "march up into the cloudy mists in the sky, where they are most " +
        "appropriately named the Misty Mountains. While to the east, an " +
        "imposing line of tall, black oak trees loom menacingly. This forest " +
        "is certainly the mighty Mirkwood of legend, a name which has " +
        "inspired fear and terror in many a tale.\n");

    add_exit(VALE_DIR + "valen11w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen11w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen12w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen13w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen13w7", "north",0,2,1);
}
