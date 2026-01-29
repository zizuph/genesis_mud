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
    set_herbs_7();
    
    set_short("Vale of the Anduin");
    set_long("Tall yellow grasses sway all around you here, pushed and " +
        "pulled along with every breeze which drifts past. You are on the " +
        "eastern edge of the great river Anduin, at the bottom of a deep " +
        "valley. The river cuts down from the north running strong and " +
        "fast as it seeks the sea which waits far to the south. On the " +
        "west side of the vale, rolling foothills grow ever larger as they " +
        "become the imposing heights of the Misty Mountains. Not far to " +
        "the east, atop the lip of the valley, thousands of tall, black " +
        "trees mark the edge of Mirkwood forest.\n");

    add_exit(VALE_DIR + "valen14w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen14w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen15w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen16w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen16w7", "north",0,2,1);
}
