
inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include <stdproperties.h>
#include "../edefs.h"

void
create_room()
{
   config_default_trade();
   set_money_give_out( ({400,400,400,400}) );
   set_short("Coral Requiem General Store");
   set_long("   This is the general store of Coral Requiem.  " +
      "Here you can buy and sell equipment for your journeys.  " +
      "Value and list commands can be used here as well.  " +
      "The exit back into the cave is just to the south.\n\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "store", "east", "@@wiz_check");
   add_exit(CRDIR + "cr1", "south");
   
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   set_store_room(CRDIR+"store");
   
}
/*
* Function name:   init
* Description:     Is called for each living that enters this room
*/
void
init()
{
   ::init();   /* You MUST do this in a room-init */
   init_shop(); /* Get the commands from the shop */
}
