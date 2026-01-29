/*
 *	/d/Gondor/pelargir/misc/pelbank.c
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *
 *  Modification log:
 *
 *     2008-01-09, Toby: Fixed for new bank support.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/bank.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STD_FEE 30

public string  exa_plaque();

object  deposit;

public void
create_gondor()
{
    set_short("the Merchant Bank of Pelargir");
    set_long(BSN("The Merchant Bank of Pelargir is a branch of the "
        + "Royal Bank of Gondor which has specialized on offering "
        + "banking services to travellers and sea-going merchants, "
        + "who come run their business out of Pelargir. A bronze "
        + "plaque on the counter lists the conditions of trade, "
        + "and a gnome money deposit offers additional services."));

    add_exit(PELAR_DIR + "streets/plaza", "north", 0, 0);
    add_prop(ROOM_I_INSIDE,1);

    config_default_trade();
    set_bank_fee(STD_FEE);      /* must come before config_trade_data() */
    config_trade_data();

    add_item( ({ "counter", "clerk", }), "The clerk is sitting "
        + "behind the counter, wondering if you are just going to "
        + "stare at him, or if you are interested in doing business " 
        + "here.\n");

    add_item( ({ "bronze plaque", "plaque", "conditions",
                     "instructions", "conditions of trade", }),
        exa_plaque()); 
    add_cmd_item( ({ "bronze plaque", "plaque", "conditions",
                         "instructions", "conditions of trade", }),
        "read", exa_plaque()); 

    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_bank_id(1802, "Pelargir");
    deposit->move(TO);
}

/*
 * Function name: exa_plaque
 * Description:   returns a string with a poster message
 * Returns:       message string
 */
public string
exa_plaque()
{
    return "The plaque reads:\n\n" +
	"The Merchant Bank of Pelargir provides you with prompt "
            + "service at modest fees (only " + bank_fee + "%). "
            + "These are some examples of the services we are offering:\n\n" 
        + "\t- Change copper and silver for gold.\n"
        + "\t- Test change copper and silver for gold.\n"
        + "\t- Change 1 platinum for copper.\n"
        + "\t- Change platinum for 100 silver.\n"
        + "\t- Minimize coins.\n\n";
}

public void
init()
{
    ::init();

    bank_init();
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
       +  "Your coins are now minimized.\n");
    say(QCTNAME(TP) + " minimized " +
        TP->query_possessive() + " coins.\n");
}

