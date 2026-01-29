/*
* The bank in the Solamnian Guild
* 
* Made by Nick
*/
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit BALIFOR_IN;
inherit "/lib/bank";

/*
* Function name: create_room Description:   Set up default trade and
* configure it if wanted.
   */
void
create_balifor_room()
{
    object xx;
    config_default_trade();
    set_short("Bank of Balifor");
    set_long("You are in the bank of Balifor. There is a plaque on the " +
      "counter giving directions for using the bank.\n");
    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    config_trade_data();
    add_exit(BROOM + "city17", "west", 0);
    xx = clone_object("/d/Genesis/obj/deposit");
    xx->set_bank_id(4303, "Balifor");
    xx->set_short("deposit");
    xx->set_no_show_composite(1);
    /* Added by Ashlar: Setting a large weight makes sure
    is not destroyed by any errant sivak fire */
    xx->add_prop(OBJ_I_WEIGHT, 500000);
    xx->move(this_object());

}

fee()
{
    set_bank_fee(15);
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
