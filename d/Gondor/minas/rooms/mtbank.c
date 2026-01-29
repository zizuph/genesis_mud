/*
 *  The bank in Minas Tirith
 *
 *  Rewritten using /lib/bank.c by Olorin, Feb 1995
 *
 *  Removed BSN, 2008-01-09, Toby
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/bank";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define STD_FEE 20

string  exa_plaque();

void
create_gondor()
{
    set_short("the Bank of Gondor in Minas Tirith");
    set_long(
        "This is the main office of the Royal Bank of Gondor. Here "
      + "you can exchange money. " 
      + "There is a lovely secretary sitting behind a counter, and a "
      + "strong guard by the door. There is a plaque on the wall. "
      + "A doorway leads west to the Minas Tirith branch of the "
      + "Gnomes of Genesis money-deposit service. "
      + "The exit to the street is south.\n");
    add_item("secretary", "She is a lovely young Gondorian woman, "
      + "hired to exchange money for the adventurers that visit Minas "
      + "Tirith.\n");
    add_item("guard", "He looks like one of the toughest you have "
      + "seen. Do not make any trouble as long as he is watching, that "
      + "is my advice.\n");
    
    add_exit(MINAS_DIR + "s2crc1", "south", 0,0);
    add_exit(MINAS_DIR + "rooms/mtbank2","west",0,0);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();
    set_bank_fee(STD_FEE);
    config_trade_data();

    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

                     /* Copper Silver Gold  Platinum  */
    set_money_give_out(({40000, 4000, 2000, 200}));
    set_money_give_max(40000);
    set_money_give_reduce(({0, 0, 0, 0}));

    money_num = sizeof(query_money_types());

    add_item("plaque", exa_plaque());
    add_cmd_item(({"plaque", "instructions"}), "read", exa_plaque());
}

/*
 * Function name: init
 * Description:   Initalize the bank actions
 */
void
init()
{
    ::init();

    bank_init();
}

void
test_tour(object player)
{
    object note;

    if (objectp(note = present("Minas_Tirith_Tour_Note", player)))
    {
        if (note->query_tour_no() != 1)
            return;

        note->set_tour_done();
        set_alarm(3.0, 0.0, "tour_done", player);
    }
    return;
}

void
tour_done(object player)
{
    tell_object(player,"This is indeed the place that the Master of Advice told you to find.\n"+
        "You may now return to him!\n");
    return;
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);

    if (objectp(obj) && living(obj))
        test_tour(obj);
}

/*
 * A few hooks to get your own messages.
 */
void
bank_hook_pay(string text)
{
    TP->reveal_me(1);
    write("You pay " + text + ".\n");
}

void
bank_hook_change(string text)
{
    write("You get " + text + " back.\n");
}

void
bank_hook_other_see(int test)
{
    TP->reveal_me(1);
    if (!test)
        say(QCTNAME(TP) + " changes some money.\n");
    else
        say(QCTNAME(TP) + " seems to calculate something.\n");
}

/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    write("You pay "+pay_text+" and get "+got_text+" in return.\n"
        + "Your coins are now minimized.\n");
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
}

/*
 * Function name: exa_plaque
 * Description:   returns a string with a plaque message
 * Arguments:     none
 * Returns:       message string
 */
string
exa_plaque()
{
    return "The plaque reads:\n\n" + 
	"The Bank of Gondor provides you with a cheap way to relieve "
      + "you of the burden of heavy coins. "
      + "For each transaction we ask only a fee of about "+bank_fee+"%. "
      + "These are examples of what you can do:\n\n" +
	    "\t- Change copper and silver for gold.\n" +
	    "\t- Test change copper and silver for gold.\n" +
	    "\t- Change 1 platinum for copper.\n" +
	    "\t- Change platinum for 100 silver.\n" +
	    "\t- Minimize coins.\n";
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
   int     bargain = TP->query_skill(SS_TRADING);

   if (bargain > 30)
       bargain = 30;
   bargain = 103 - bargain/5;

   switch (query_friend_or_foe(TP))
   {
     case -1: bargain = (bargain * 105) / 100; break;
     case  0: break;
     case  1: bargain = (bargain *  98) / 100; break;
   }
   return bargain + bank_fee;
}




