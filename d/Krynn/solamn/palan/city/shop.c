/* 
 * An example shop coded by Nick, some Ideas and part of code taken from 
 * Tricky's shop in hobbitown solamnian modifications by percy, aridor
 *
 */
/*
 * Louie April 2006 - Set greed to 100.
 */

#include "../local.h"

inherit ROOM_BASE
inherit "/lib/shop";

#include <macros.h>
#define STORE_ROOM      ROOM + "store"

string
query_to_jail()
{
  return "south";
}


/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_palan_room()
{
    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("The local shop");
    set_long(
      	"You are in the local shop. Here you can sell and buy stuff.\n" +
      	"You can also use value or list commands, 'list armours',\n" +
      	"'list weapons', 'list <name>' and 'list' works too.\n" +
      	"There is also a small sign to read with more instructions.\n" +
      	"");

    add_exit(ROOM + "street15","south");
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    set_store_room(STORE_ROOM);
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
        init_shop(); /* Get the commands from the shop */
}


void
init_shop()
{    
        add_action("do_read", "read");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_show", "show");
        add_action("do_sell", "sell");
        add_action("do_value", "value");

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
    if (this_player()->query_wiz_level())
      	return 0;
    write("Some magic force keeps you from going north.\n");
    say(QCTNAME(this_player()) + " tries to go north but fails.\n");
    return 1;
}
