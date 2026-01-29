/*
 * Filename:    bank.c
 * Description: The bank in Solace
 *
 * Revision history:
 *
 */
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/lib/bank";
inherit SOLINROOM;

void
create_solace_room()
   {
   object          xx;
   config_default_trade();
   set_short("Bank of Solace");
   set_long("You are in the recently opened bank of Solace. With the town "+
      "booming as it is, the gnomes of Genesis decided to open up a branch "+
      "here and profit from the newfound popularity of Solace. There is a "+
      "plaque on the counter giving directions for using the bank.\n");
   add_item("plaque", "@@standard_bank_sign");
   add_cmd_item("plaque", "read", "@@standard_bank_sign");
   config_trade_data();
   add_exit(ROOMS + "platform8", "out", 0);
   xx = clone_object("/d/Genesis/obj/deposit");
   xx->set_short("deposit");
   xx->set_no_show_composite(1);
   xx->move(this_object());

}

fee()
{
   set_bank_fee(25);
   config_trade_data();
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
