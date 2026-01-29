/* 
An example shop coded by Nick, some Ideas and part of code taken from 
Tricky's shop in hobbitown.

Added to Re-Albi by Ged and Gresolle 92
Changed to use /lib/shop by Glindor
Used for the Thvil General Store 93

*/

#include "defs.h"

inherit THWIL_BASE_ROOM;
inherit "/d/Emerald/lib/shop_list";


#define STORE_ROOM "/d/Earthsea/roke/thwil/store"

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/
void
create_thwil_room()
{
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(1300);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The Thwil General Store");
   set_long("You are in Thwil's general store. " +
	    "Here you can trade your collected " +
	    "treasures for money or buy new equipment " +
	    "for coming adventures. " +
	    "There is a small sign to read with " +
	    "instructions on how to use " +
	    "this shop.\n");
   
   add_item("sign", "A nice looking sign, perhaps you should read it.\n");
   
   add_exit(THWIL+ "t7", "west", 0);
   add_exit(THWIL+"store", "north", "@@wiz_check");
   set_no_npc(1);
   INSIDE;
}

/*
* Function name:   init
* Description:     Is called for each living that enters this room
* Returns:
*/
void
init()
{
   ::init();   /* You MUST do this in a room-init */
   init_shop();
}

