inherit "/std/room";
inherit "/lib/bank";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

create_room() {
   set_short("The Ciubori Bank");
   set_long(break_string(
      "This is the Ciubori Bank Palace. The room is huge and with "+
      "ornamented columns banded with pure gold. The place is very "+
      "impressive. There is a golden plaque on one of the walls, explaining "+
      "how to use the bank."
    + "\n", 60));

   add_exit(CIUBORI+ "sapphire/street2", "east");

   add_item(({"mage","clerk"}),
      "Looks greedily at your money pouch.\n");

   add_item("plaque","@@standard_bank_sign");
   add_cmd_item("plaque","read","@@standard_bank_sign");

   add_item(({"counter","iron-barred counter"}), break_string(
      "You see no way to get behind the counter, since it is totally "
    + "enclosed by thick iron bars.  You wonder how they get the money"+
      " out of there.\n",70));

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

init() {
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
