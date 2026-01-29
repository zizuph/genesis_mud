inherit "/d/Krynn/std/room";
inherit "/lib/bank";

#include "../guild.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_krynn_room()
{
    set_short("The place where gnomes trade money...");
    set_long("Tucked into a corner of the main deposit a human, "
    	+ "obviously the only one in the whole mount, has opened "
    	+ "a tiny bank business. He will be happy to exchange "
    	+ "your coins. However he will ask 25% tax for his services. "
    	+ "There is a plaque containing more detailed information.\n");
    	
    add_item("plaque",
	     "It contains instructions on how to exchange your money.\n");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");

    set_bank_fee(25);
    config_default_trade();
    config_trade_data();

    add_exit(ROOMS + "deposit", "out", 0);
    INSIDE
    LIGHT
}

void
init()
{
     bank_init();
   ::init();
}

void
bank_hook_minimized(string pay_text, string got_text)
{
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
    write("You minimize " + pay_text + " and now have " + 
	  got_text + " on you.\n");
}
