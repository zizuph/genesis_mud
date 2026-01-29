/* 
* An example shop coded by Nick, some Ideas and part of code taken from 
* Tricky's shop in hobbitown solamnian modifications by percy, aridor
   *
*/
/*
 * Louie April 2006 - Set greed to 100, which all krynn shops should be.
 */

#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#include <macros.h>
#define STORE_ROOM    FROOM + "store02"

string
query_to_jail()
{
    return "north";
}

void
reset_flotsam_room()
{
    return;
}

/*
* Function name:   create_room
* Description:     Initialize this room
*/
void
create_flotsam_room()
{
    set_money_greed_sell(100);
    set_money_greed_buy(100);
    config_default_trade();
    set_short("Store");
    set_long("This is a nondescript store that deals " +
      "in the selling of goods. Common knowledge is that " +
      "this store is also a fence for 'hot' equipment, " +
      "so you should have no trouble selling any stuff " +
      "here. There is a wooden counter against the southern " +
      "wall and a large red curtain over a part of the " +
      "western wall. \n" +
      "You can also use value or list commands, 'list armours',\n" +
      "'list weapons', 'list <name>' and 'list' works too.\n" +
      "There is also a small sign to read with more instructions.\n" +
      "");

    add_item(({"counter","wooden counter","southern wall"}),
      "Against the southern wall is a counter where the shops " +
      "attendant serves his customers from. \n");
    add_item(({"western wall","large red curtain","red curtain",
	"curtain"}),"A large red curtain covers the middle part " +
      "of the western wall. " +
      "It looks like there is an exit hidden behind it.\n");

    add_exit(FROOM + "street38","north");
    add_invis_exit(STORE_ROOM,"south","@@wiz_check");
    add_invis_exit(FROOM + "bank","west","@@enter_bank");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");


    set_store_room(STORE_ROOM);
    reset_flotsam_room();
}

int
enter_bank()
{
    write("You pass through the curtain and into a " +
      "shady moneylenders. \n");
    return 0;
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
    write("There is no obvious exit south.\n");
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

