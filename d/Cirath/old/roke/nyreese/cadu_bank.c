/*
 * cadu_bank.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("The Cadu Bank");
    set_long(
        "This is a dark, damp circular room with walls covered with gold " +
	"and platinum in rectangular patterns. This is the famous and " +
	"well-known bank of Cadu.  It is run by wizards, who decided that " +
	"setting up a bank would be a lot of fun.  Behind an iron-barred " +
	"counter is a mage who looks like he wouldn't mind taking some of " +
        "your money. A plaque is attached to the counter.\n");

    add_exit("cadu_a1", "north");

    add_item(({"mage", "clerk"}),
        "The human tries to estimate how much money you carry with you.\n");

    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");

    add_item(({"counter", "iron-barred counter"}),
        "You see no way to get behind the counter, since it is totally " +
        "enclosed by thick iron bars.  You wonder how they get the money " +
        "out of there.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

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
}

void
init()
{
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
