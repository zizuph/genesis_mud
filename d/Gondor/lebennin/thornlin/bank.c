/*
 *  The bank in Minas Tirith
 *
 *  Rewritten using /lib/bank.c by Olorin, Feb 1995
 *  Modified for Thornlin use by Auberon, 31 Dec. 00
 *  
 */

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/bank";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define STD_FEE 18
string  exa_plaque();

void
create_gondor()
{
    set_short("The Bank of Gondor in Thornlin");
    set_long("This is a branch office of the Royal Bank of Gondor. Here "
      + "you can exchange money. " 
      + "There is a lovely teller sitting behind a counter, and a "
      + "strong guard by the door. There is a plaque on the wall.\n");
    add_item("teller", ("She is a lovely young Gondorian woman, "
      + "hired to exchange money for the residents of Thorbardin.\n"));
    add_item("guard", ("He looks like one of the toughest you have "
      + "seen. Do not make any trouble as long as he is watching, that "
      + "is my advice.\n"));
    
    add_exit(THORN_DIR + "shop", "east", 0,0);
    add_exit(THORN_DIR + "guardhouse","west",0,0);
    add_exit(THORN_DIR + "tavern", "north",0,0);
                      /* This is a real room */
    add_prop(ROOM_I_INSIDE,1);  

    config_default_trade();
    set_bank_fee(STD_FEE);
    config_trade_data();

                     /* Copper Silver Gold  Platinum  */
    set_money_give_out(({40000, 4000, 2000, 200}));
    set_money_give_max(40000);
    set_money_give_reduce(({0, 0, 0, 0}));

    money_num = sizeof(query_money_types());

    add_item("plaque", exa_plaque());
    add_cmd_item(({"plaque", "instructions"}), "read", exa_plaque());
    clone_object("/d/Genesis/obj/deposit")->move(this_object());
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
 * Function name: bank_poster
 * Description:   returns a string with a poster message
 * Arguments:     none
 * Returns:       message string
 */
string
exa_plaque()
{
    return "You read:\n" + (
	"The Bank of Gondor, branch office Thornlin, provides you with a cheap way to relieve "
      + "you of the burden of heavy coins. "
      + "For each transaction we ask only a fee of about "+bank_fee+"%. "
      + "These are examples of what you can do:\n") +
	" - Change copper and silver for gold.\n" +
	" - Test change copper and silver for gold.\n" +
	" - Change 1 platinum for copper.\n" +
	" - Change platinum for 100 silver.\n" +
	" - Minimize coins.\n";
}


