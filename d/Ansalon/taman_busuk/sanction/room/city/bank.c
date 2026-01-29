#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCINROOM;
inherit "/lib/bank";

void
create_sanction_room()
{
    object xx;
    config_default_trade();
    set_short("bank of Sanction");
    set_long("You stand in the Bank of Sanction. Before the occupation "+
      "of the city by dragonarmy forces, this was a bustling building "+
      "full of merchants and traders. Now it is mostly empty, used mainly "+
      "to store the wages and battle loot of dragonarmy soldiers. A dusty plaque "+
      "hangs on a wall near you.\n");
    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    config_trade_data();
    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_bank_id(4305, "Sanction City");
    /*
	xx->set_no_show_composite(1);
    */
    xx->move(this_object());
    add_exit(SCITY + "street12","west",0);

}

fee()
{
    set_bank_fee(40);
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
