/*
 *  Bank
 */
#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/lib/trade";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void create_thwil_room() {
   object deposit;

   set_short("The local bank");
   set_long("This is a dark, damp circular room with walls covered with gold "
    + "and platinum in rectangular patterns. This is the famous and "
    + "well-known bank of Thwil.  It is run by wizards, who decided that "
    + "setting up a bank would be a lot of fun.  Behind an iron-barred "
    + "counter is a mage who looks like he wouldn't mind taking some of your "
    + "money.  A plaque is attached to the counter. "
    + "\n");

   add_exit(THWIL+ "t4", "east", 0);
   add_item("floor", "The floor is made of well-polished marble.\n");
   add_item(({"mage","clerk"}),
      "The mage tries to estimate how much money you carry with you.\n");

   add_item("plaque","@@sign_long");

   add_item(({"counter","iron-barred counter"}), break_string(
      "You see no way to get behind the counter, since it is totally "
    + "enclosed by thick iron bars.  You wonder how they get the money"+
      " out of there.\n",70));
   set_no_npc(1);
   INSIDE;

  /* Set up the trading system */
   config_default_trade();
                        /* Copper Silver  Gold  Platinum  */
   set_money_give_out(   ({100000,100000,100000,100000 })); /* Max_pay   */
   set_money_give_reduce(({     0,     0,     0,     0 })); /* Threshold */
   set_money_greed_sell(120);
   set_money_give_max(1000000000);

/* a gnome money deposit */

   deposit = clone_object("/d/Genesis/obj/deposit");
   deposit->set_bank_id(4702, "the Isle of the Wise");
   deposit->move(this_object());
}

init() {
   ::init();

   add_action("do_change","change",0);
   add_action("do_minimize","minimize",0);
   add_action("do_read","read",0);
}


do_read(str) {
   if (str != "plaque")
      return;
   write(sign_long());
   return 1;
}

sign_long() {
   return
      "On the plaque you read:\n\n"
    + "We change all kinds of money.  Simply mention the kind you want\n"
    + "to change, and the kind you want to get.  Our bank provides you\n"
    + "with the cheapest way to relieve you of the burden of heavy coins.\n"
    + "For each transaction we only ask 20% interest.\n"
    + "Examples:\n"
    + "            change silver for platinum\n"
    + "            change gold to copper\n"
    + "            minimize coins\n\n"
    ;
}


do_change(str) {
   string pay_type, get_type, coin_pay_text, coin_get_text;
   int *money_arr;
   object money, tp;
   int value;

   if (!str || str == "") return 0;

   str = lower_case(str);

   NF("You have to state between which cointypes you wish to change.\n");
   if (sscanf(str, "%s for %s", pay_type, get_type) != 2)
     if (sscanf(str, "%s to %s", pay_type, get_type) != 2)
       return 0;

   pay_type = lower_case(pay_type);
   get_type = lower_case(get_type);
   tp = this_player();

   if (pay_type == get_type)
   {
      tell_room(this_object(), break_string(
         "The clerk says: I changed it so fast that you didn't notice "
       + "it, " + tp->query_nonmet_name() + ".\n",70));
      return 1;
   }

   if (member_array(pay_type, MONEY_TYPES) < 0)
   {
      tell_room(this_object(), break_string(
         "The clerk says: We don't take those " + pay_type + " coins "
       + "here, " + tp->query_nonmet_name() + ".\n",70));
      return 1;
   }

   if (member_array(get_type, MONEY_TYPES) < 0)
   {
      tell_room(this_object(), break_string(
         "The clerk says: We don't have any " + get_type + " coins "
       + "here, " + tp->query_nonmet_name() + ".\n",70));
      return 1;
   }

 /* Check what coins the player has */
   money_arr = what_coins(tp);

 /* Keep the coins she wants to pay with */
   want_to_pay(money_arr, pay_type);

 /* Calculate the value of all carried coins of that type */
   value = money_merge(money_arr);

 /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, 0)) == 1)
      return 0;

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));

 /* Hand out the money... */
   if (sizeof(money_arr = give(value, tp, get_type, 0, 0)) == 1)
   {
    /* Then try giving without specifying get_type */
      if (sizeof(money_arr = give(value, tp, 0, 0, 0)) == 1)
      {
         write("Ooops! Bank error. This should not have happened. Try the 'bug' command.\n");
         return 1;
      }
   }

   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   say(QCTNAME(tp) + " changes some coins for some others.\n");
   write("You change your " + coin_pay_text + " for " + coin_get_text + ".\n");

   tell_room(this_object(), break_string(
      "The clerk says: It was nice to do business with you, "
    + tp->query_nonmet_name() + ".\n",70));
   return 1;

}


do_minimize(str) {
   string coin_pay_text, coin_get_text;
   int *money_arr;
   object money, tp;
   int value;

   NF("Minimize what?\n");
   if (str != "coins") return 0;

   tp = this_player();

 /* Check what coins the player has */
   money_arr = MONEY_COINS(tp);

 /* Dont minimize platinum */
   money_arr[NUM-1]=0;

 /* Calculate the value of all coins */
   value = money_merge(money_arr);

 /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, 0, 0, 0, 0)) == 1)
      return 0;

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));

 /* Hand out the money... */
   if (!(money_arr = give(value, tp, 0, 0, 0)))
      return 0;

   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   say(QCTNAME(tp) + " changes some coins for some others.\n");
   write("You minimize your " + coin_pay_text + " and get " + coin_get_text + ".\n");

   tell_room(this_object(), break_string(
      "The clerk says: I hope you enjoyed the transaction as much as I did, "
    + tp->query_nonmet_name() + ".\n",70));
   return 1;

}









