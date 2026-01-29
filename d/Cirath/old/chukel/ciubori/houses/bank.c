/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/bank.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
inherit "/lib/bank";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void
create_room()
{
   	set_short("The Ciubori Bank");
   	set_long("This is the Ciubori Bank Palace. The room is huge and has "+
      		"two ornamented columns banded with pure gold in the middle of it "+
      		" which makes the place look very impressive. There is a golden "+
      		"plaque on one of the walls, explaining how to use the bank.\n");

   	add_item(({"mage","clerk"}), "The clerk looks greedily at your money pouch.\n");

   	add_item("plaque","@@standard_bank_sign");
   	add_cmd_item("plaque","read","@@standard_bank_sign");

   	add_item(({"counter","iron-barred counter"}), "You see no way to get "
   		+"behind the counter, since it is totally enclosed by thick iron "
   		+"bars. You wonder how they get the money out of there.\n");

   	INSIDE;

  	/* Set up the trading system */
   	config_default_trade();
   	set_bank_fee(20);
   	config_trade_data();
                            /* Copper Silver  Gold  Platinum  */
   	set_money_give_out(   ({100000,100000,100000,100000 })); /* Max_pay   */
   	set_money_give_reduce(({     0,     0,     0,     0 })); /* Threshold */
   	set_money_give_max(1000000000);
	/* a gnome money deposit */

 	clone_object("/d/Genesis/obj/deposit")->move(this_object());
 
   	add_exit(CIU_STR + "sstreet2", "east", 0,1);
   	reset_room();

 
}

init() {
   	::init();
   	bank_init();
}

void
bank_hook_minimized(string pay_text, string get_text)
{
    	write("You minimize your " + pay_text + " and get " + get_text + ".\n");
    	say(QCTNAME(this_player()) + " minimized " +
        this_player()->query_possessive() + " coins.\n");
}
