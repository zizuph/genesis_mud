/* 
* An example shop coded by Nick, some Ideas and part of code taken from 
* Tricky's shop in hobbitown solamnian modifications by percy, aridor
   *
*/

#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit BALIFOR_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#include <macros.h>
#define STORE_ROOM    BROOM + "storeroom"

string
query_to_jail()
{
    return "west";
}

void
reset_balifor_room()
{
    return;
}

/*
* Function name:   create_room
* Description:     Initialize this room
*/
void
create_balifor_room()
{
    set_money_greed_sell(80);
    set_money_greed_buy(80);
    config_default_trade();
    set_short("Store");
    set_long("This is the shop of the Wealthy Merchant of Balifor, "+
      "Eorl. He stares around his store, while sharpening his curved "+
      "knife. You would not even consider stealing from this man, who "+
      "would, from the looks of him, slit your throat without remorse. "+
      "\n"+
      "You can also use value or list commands, 'list armours',\n" +
      "'list weapons', 'list <name>' and 'list' works too.\n" +
      "There is also a small sign to read with more instructions.\n" +
      "");

    add_exit(BROOM + "city19","west");
    add_invis_exit(STORE_ROOM,"east","@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");


    set_store_room(STORE_ROOM);
    reset_balifor_room();
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
    write("Eorl stands up, scowling at you, and you quickly step away "+
      "from the storeroom.\n");
    say(QCTNAME(this_player()) + " walks towards the storeroom, but "+
      "quickly steps away as Eorl stands up scowling angrily.\n");
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
