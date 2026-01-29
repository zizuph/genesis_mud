/* 
 * An example shop coded by Nick, some Ideas and part of code taken from 
 * Tricky's shop in hobbitown solamnian modifications by percy, aridor
 *
 */


#include <stdproperties.h>
#include "../local.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <std.h>


inherit MITHAS_IN;

inherit "/d/Emerald/lib/shop_list";
//inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    GUILD_ROOM + "pirate_store_room"

string
query_to_jail()
{
    return "west";
}

void
reset_mithas_room()
{
    return;
}

void
create_mithas_room()
{
    set_long("@@long_descr");
    config_default_trade();
    set_money_greed_buy(90);
    set_money_greed_sell(80);
     set_short("Essential's Pirate Equipment");

    add_exit("pirate_center_room","west",0,0);
    add_invis_exit(STORE_ROOM,"east","@@wiz_check");

    add_item(({"cages", "parrots"}),"The animals have "+
               "been trapped here for quite some time, "+
               "if you are lucky you might buy one from "+
               "the shopkeeper.\n");
    set_store_room(STORE_ROOM);
    reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in a huge underground cave, beneath the isle of Mithas. The "+
          "black rock walls are drenched with water and the smell of the fresh seawater "+
          "and wet soil dominate this place. This might be a good place to hide yourself "+
          "or something. This room must be some sort of storeroom, small cages containing "+
          "colorful parrots fill the floor and ceiling of this room. The only exit out of "+
          "here is to the west.\n"+
          "You can also use value or list commands, 'list armours',\n"+
          "'list weapons', 'list <name>' and 'list' works too.\n"+
          "There is also a small sign to read with more instructions.\n"+
          "Two large cages with monkeys and parrots has been placed in the corner.\n";
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
    write("There is no obvious exit east.\n");
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
