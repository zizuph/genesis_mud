/* Ashlar, 20 Jul 97 */
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit INNER_IN;
inherit "/lib/bank";

object g;

void
reset_neraka_room()
{
    if (!objectp(g))
        g = clone_npc(NNPC + "cityguard");
}

void
create_neraka_room()
{
    object xx;
    config_default_trade();
    set_short("The Bank of Neraka");
    set_long("You are in the main office of the Bank of Neraka. " +
        "There is a plaque on the counter giving directions for " +
        "using the bank, and a poster hangs on one wall. " +
        "There is an exit leading east out to the street.\n");
    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    add_item("poster","The poster states the current exchange rates " +
        "for minimizing one's coins.\n");
    add_cmd_item("poster","read","\nBank of Neraka\n" +
        "We exchange money for a meager 30% fee.\n\n");

    add_item_inside();

    set_bank_fee(30);
    config_trade_data();

    add_exit(NINNER + "r39", "east");

    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_bank_id(4304, "Neraka Inner District");
    xx->set_short("deposit");
    xx->set_no_show_composite(1);
    xx->add_prop(OBJ_I_WEIGHT, 500000);
    xx->move(this_object());
    reset_room();
}

init()
{
    ::init();

    bank_init();
}

void
bank_hook_minimized(string pay_text, string got_text)
{
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
    write("You minimize " + pay_text + " and now have " + 
	  got_text + " on you.\n");
}

