/* 
 * An example shop coded by Nick, some Ideas and part of code taken from 
 * Tricky's shop in hobbitown solamnian modifications by percy, aridor
 *
 */
/*
 * Louie April 2006 - Set greed to 100.  All shops should be this.
 */


#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    MROOM + "store02"

string
query_to_jail()
{
    return "east";
}

void
reset_mithas_room()
{
    return;
}

/*
* Function name:   create_room
* Description:     Initialize this room
*/
void
create_mithas_room()
{
    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("General Shop");
   
    set_long("You are standing in a large general shop "+
      "that both sells and buys different items. "+
      "however the shopkeeper fancies weapons "+
      "and armours. There's a stone counter "+
      "against the northern wall and heavy wooden "+
      "door blocks the the western exit.\n"+
      "You can also use value or list commands, 'list armours',\n" +
      "'list weapons', 'list <name>' and 'list' works too.\n" +
      "There is also a small sign to read with more instructions.\n");

    add_item(({"counter","stone counter","northern wall"}),
      "Against the northern wall is a counter where the shops " +
      "attendant serves his customers from. \n");

    add_exit(MROOM + "road39","east");
    add_invis_exit(STORE_ROOM,"west","@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");


    set_store_room(STORE_ROOM);
    reset_mithas_room();
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
    if (this_player()->query_wiz_level())
	return 0;
    write("There is no obvious exit west.\n");
    return 1;
}


int
do_buy(string str)
{
    if (check_cheater(this_player()))
        return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (check_cheater(this_player()))
        return 1;
    return ::do_sell(str);
}
