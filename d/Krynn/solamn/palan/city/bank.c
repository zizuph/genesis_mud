/* 
 * The bank in the Solamnian Guild
 *
 * Made by Nick
 */
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit ROOM_BASE
inherit "/lib/bank";

string
query_to_jail()
{
    return "southeast";
}

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */
void
create_palan_room()
{
    object xx;
    config_default_trade();
    set_short("The bank of Palanthas");
    set_long("This is the esteemed bank of Palanthas, where you " +
        "are able to exchange your hard-earned coins for a lighter " +
        "load, as long as you don't mind the 25% fee. There is a " +
        "small plaque on the wall.\n");
/*
    set_long("You are in the keep bank. Here a knight can exchange heavy " +
	     "coins into higher valued coins thus lowering the load to carry. " +
	     "However, we take a small fee for helping you: 15% of the value " +
	     "of the coins switched if you are a Knight of Solamnia, otherwise " +
	     "the fee is 25%. There is a small plaque on the wall.\n");
*/
    
    add_item("plaque",
	     "It contains instructions on how to exchange your money.\n");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    
    config_trade_data();
    
    add_exit(ROOM + "street15.c", "southeast", 0);

    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_short("deposit");
    xx->set_no_show_composite(1);
    xx->move(this_object());

}

fee()
{
    set_bank_fee(25);
    config_trade_data();
    return;
}

init()
{
    ::init();

    bank_init();
}

change(string str)
{   
    fee();
    return ::change(str);
}

test(string str)
{
    fee();
    return ::test(str);
}

minimize(string str)
{
    fee();
    return ::minimize(str);
}

standard_bank_sign()
{
    fee();
    return ::standard_bank_sign();
}

void
bank_hook_minimized(string pay_text, string got_text)
{
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
    write("You minimize " + pay_text + " and now have " + 
	  got_text + " on you.\n");
}

