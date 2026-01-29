/*
* The bank in the Solamnian Guild
* 
* Made by Nick
*/
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit FLOTSAM_IN;
inherit "/lib/bank";

/*
* Function name: create_room Description:   Set up default trade and
* configure it if wanted.
   */
void
create_flotsam_room()
{
   object          xx;
   config_default_trade();
   set_short("Moneylenders");
   set_long("You stand in a secret moneylenders, based in a " +
      "back room of the local store of Flotsam. You notice the " +
      "exit on the other side of the room has been covered by " +
      "a curtain. You also notice a plaque on the counter " +
      "giving directions for using the moneylenders.\n");
   add_item("plaque", "@@standard_bank_sign");
   add_item(({"exit","curtain","red curtain"}),
      "To the east on the otherside of the exit a red " +
      "curtain covers the door. You have to pass through " +
      "it to get back to the store.\n");
   add_cmd_item("plaque", "read", "@@standard_bank_sign");
   config_trade_data();
   add_exit(FROOM + "store","east",0);
   xx = clone_object("/d/Genesis/obj/deposit");
   xx->set_short("deposit");
   xx->set_no_show_composite(1);
   xx->move(this_object());
   
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
