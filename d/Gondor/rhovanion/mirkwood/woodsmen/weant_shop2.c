/*
 * Weanting
 * Varian - March 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_STD_DIR + "room";

void

create_room()

{
    set_short("Storage room for Weanting Shop");
    set_long("Hey, are you a wizard? You shouldn't be here unless you are! This is " +
        "just the storage room for the shop in Weanting.\n");
  
    add_item_light(({"room", "storage room"}),
        "Hey, are you a wizard? You shouldn't be here unless you are! This is " +
        "just the storage room for the shop in Weanting.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit("/d/Gondor/rhovanion/mirkwood/woodsmen/weant_shop", "east", "@@shop@@");
}

int
shop()
{
    write("\n\nYou go back to the shop where you belong\n\n");
    return 0;
}