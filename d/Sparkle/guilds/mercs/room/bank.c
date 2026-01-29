/*
 * /d/Genesis/guilds/merc/bank.c
 *
 * Adapted from code by Nick
 */
inherit "/std/room";
inherit "/lib/bank";

#include "../merc.h"
#include "room.h"

string long_desc()
{
    return INSIDE_TENT_DESC+
	"A wooden counter faces the entrance of the tent, "+
	"behind which several gnomes move frantically around, "+
	"conducting business. On the front of the counter, a "+
	"small plaque has been attached.\n";
}

int exit_tent()
{
    write(TENT_EXIT);
}

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */
void
create_room()
{
    object xx;
    config_default_trade();
    set_short("A small tent");
    set_long("@@long_desc");
    config_trade_data();

    add_item(({"plaque", "sign"}), "@@standard_bank_sign");
    add_cmd_item(({"plaque", "sign"}), "read", 
        "@@standard_bank_sign");
    add_exit(MROOM + "center.c", "southeast", "@@exit_tent", 1, 0);

    add_prop(ROOM_I_INSIDE, 1);
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

