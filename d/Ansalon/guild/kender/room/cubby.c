
#include "../local.h"

inherit KEN_IN;
inherit "/lib/shop";

#include <macros.h>
#define STORE_ROOM KROOM + "cubby_store"

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    config_default_trade();
    set_money_greed_buy(80);
    set_money_greed_sell(75);
    set_short("A small wooden cubby house");
    set_long("You stand in a small wooden cubby house " +
      "that is nestled in the branches of a giant oak tree. " +
      "Here kender may purchase typical kender items considered " +
      "a necessity when wandering the lands. One may examine " +
      "those items that are for sale by using the 'list' command. " +
      "An exit leads out of the cubby to your west.\n");

    add_item(({"cubby house","house"}),
      "A small comfortable cubby house, designed by kender for kender.\n");

    add_exit(KROOM + "r4","west",0);
    add_invis_exit(STORE_ROOM,"south","@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");


    set_store_room(STORE_ROOM);
    reset_kendermore_room();
}

void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}


void
init_shop()
{    
    add_action("do_read", "read");
    add_action("do_list", "list");
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_show","show");

}

/*
* Function name:   wiz_check
* Description:     Check if a player is a wizard
   * Returns:         0 if the player is a wizard
   *                  1 otherwise
*/
int
wiz_check()
{
    if(this_player()->query_wiz_level() || this_player()->query_npc())
	return 0;
    write("There is no obvious exit south.\n");
    return 1;
}

int
do_sell(string str)
{
    notify_fail("You are unable to sell items here.\n");
    return 0;
}
