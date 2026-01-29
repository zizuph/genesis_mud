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
    set_items_mirk();
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("A field of tall, green grass surrounds you, swaying and " +
        "bending with every faint breeeze which twists past. You are on " +
        "the rolling slopes of a massive valley which runs out of sight " +
        "from the north to the south. This is the vale of the Anduin, named " +
        "for the massive river which tumbles past you on its journey south " +
        "to the sea. On the west side of the valley, steep and rocky " +
        "foothills climb away from the river, reaching up to pierce the " +
        "heavens above where they are known instead as the Misty Mountains. " +
        "To the north and east, an endless forest of tall, black oak trees " +
        "stretches across the horizon. These woods are the legendary " +
        "Mirkwood, where the dark shadows and deepening gloom seem to " +
        "take on a life of their own.\n");

    add_exit(VALE_DIR + "valen17w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen17w5", "southeast",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r17/f02", "east");
    add_exit(MIRK_EP_DIR + "p02", "northeast", "@@epath@@",2,1);
    add_exit(MIRK_EP_DIR + "p01", "north", "@@epath",2,1);
    add_exit(VALE_DIR + "valen19w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen18w7", "west",0,2,1);    
    add_exit(VALE_DIR + "valen17w7", "southwest",0,2,1);  
}

int
epath()
{
write("You pass into the gloomy depths of Mirkwood forest, pushing your " +
    "way through tall black trees and dense underbrush and quickly find " +
    "yourself on what appears to be a narrow path.\n");
return 0;
}

