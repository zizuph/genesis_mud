/*
 *  The gnomes bank of Buckland
 */
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Shire/room";
inherit "/lib/bank";

#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

object deposit;


create_room() {

   set_short("Bank of Buckland");
   set_long(
     "This is the bank of Buckland. The hobbits themselves never liked "
    +"the idea of a bank, since they don't bother much with money. "
    +"So they let the gnomes take care of that, since occasionally "
    +"people do stop by this town, the need for a trustworthy bank has "
    +"grown.  The bank was put in Bucklebury since it is the largest "+
    "and busiest village in Buckland.  Behind the iron-barred counter "+
    "is a gnome with greedy little eyes.  On the wall is a poster.  "+
    "There are some sleepy guards in the corner too.\n");

   add_exit(BB_DIR + "buroad9","west",0,1);
    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->move(this_object());

   add_item(({"gnome","clerk"}),
      "The gnome tries to estimate how much money you carry with you.\n"
     +"He looks at you with very greedy eyes...actually, he is looking at your wallet!\n");  
   add_item(({"guard","guards"}), "The guards in the bank are really big. It would not "
   				 +"be wise to try to rob this bank...\n");
   
   add_item("poster","@@poster_long");

   add_item(({"counter","iron-barred counter"}), break_string(
      "You see no way to get behind the counter, since it is totally "
    + "enclosed by thick iron bars. You wonder how the gnome got in.\n",70));

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

  /* Set up the trading system */
   config_default_trade();
                        /* Copper Silver  Gold  Platinum  */
   set_money_give_out(   ({100000,100000,100000,100 })); /* Max_pay   */
   set_money_give_reduce(({     0,     0,     0,    0 }));
   set_money_greed_sell(124);
   set_money_give_max(100000);
}

init() {
   ::init();
    if (TP->query_prop("_i_kill_hobbits_"))
      set_alarm(1.5,0.0,"throw_out",TP);
   add_action("do_change","change",0);
   add_action("do_minimize","minimize",0);
   add_action("do_read","read",0);
}


do_read(str) {
   if (str != "poster")
      return;
   write(poster_long());
   return 1;
}

poster_long() {
   return
      "On the poster you read:\n\n"
    + "We change all kinds of money. Simply mention the kind you want\n"
    + "to change, and the kind you want to get. Our bank provides you\n"
    + "with the cheapest way to relieve you of the burden of heavy coins.\n"
    + "For each transaction we only ask 24% interest.\n"
    + "Examples:\n"
    + "            change silver to platinum\n"
    + "            change gold to copper\n"
    + "            minimize coins\n\n";
}


do_change(str) {
   string pay_type, get_type, coin_pay_text, coin_get_text;
   int *money_arr;
   object money, tp;
   int value;

   notify_fail("Change what to what?\n");
   if (!str || str == "") return 0;

   str = lower_case(str);
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
   money_arr = MONEY_COINS(tp);

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

   if (!strlen(coin_pay_text)) {
      write("You don't have any coins to change!\n");
      return 1;
   }

   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   say(QCTNAME(tp) + " changes some coins for some others.\n");
   write("You change your " + coin_pay_text + " for " +
        (strlen(coin_get_text) ? coin_get_text : "nothing") + ".\n");

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


   tp = this_player();

 /* Check what coins the player has */
   money_arr = MONEY_COINS(tp);
   money_arr[3] = 0;	/* We don't minimize platinums */

 /* Calculate the value of all coins */
   value = money_merge(money_arr);

 /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, 0, 0, 0, 0)) == 1)
      return 0;

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));

 /* Hand out the money... */
   if (!(money_arr = give(value, tp, 0, 0, 0)))
      return 0;

   if (!coin_pay_text) {
      write("You have nothing to minimize!\n");
      return 1;
   }

   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
   say(QCTNAME(tp) + " changes some coins for some others.\n");
   write("You minimize your " + coin_pay_text + " and get " +
         (strlen(coin_get_text) ? coin_get_text : "nothing back") + ".\n");

   tell_room(this_object(), break_string(
      "The clerk says: I hope you enjoyed the transaction as much as I did, "
    + tp->query_nonmet_name() + ".\n",70));
   return 1;

}


throw_out(tp) {
    string him;

   if (present(tp))
   {
      him = tp->query_objective();

      tp->catch_msg(break_string(
        "The clerk gasps in ashtonishment and looks wide eyed at you. "
       + "He points at you and mumbles something. "
       + "Then he shouts: Guards! Help! Hobbit killers! "
       +"Immediately two big humans come running towards you and grab "
       +"you.  One guard says: I don't understand why these hobbit "
       +"killers expect to get served in here. The other guard agrees "
       +"with the first one.\n",70));

    /* You cannot use break_string here... */

      tell_room(this_object(),
         "The clerk gasps in ashtonishment and looks wide eyed at "
       + QTNAME(tp) + ".\n"
       + "He points at " + QTNAME(tp) + " and mumbles something.\n"
       + "Then he shouts: Guards! Help! Hobbit killers!\n"
       + "Immediately two big humans come running towards "
       + QTNAME(tp) + "\n"
       + "and grab " + him + " by the arms.\n",tp);

    tp->catch_msg("The guards throw you out on your butt into the street.\n");
    tp->move_living("M",BB_DIR + "buroad9",1,0);
    tell_room(environment(tp),"The guards throw "+QCTNAME(tp)+" out of "+
      "the bank.\n",tp);
    }
}
