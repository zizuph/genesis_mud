/*
 *  Bath House - by Ashbless  10/11/93
 */

inherit "/d/Kalad/room_std";
inherit "/lib/trade";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define MY_PRICES ({ 10,24,24,48 })
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

string pay_type, get_type, coin_pay_text, coin_get_text;
int * money_arr;

create_room() {
    ::create_room();
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    set_short("The Dirty Swine Bath House");

    set_long(BS(
      "You are in the lobby of the Dirty Swine Bath House. " +
      "Travelling the streets of Kabal, it is easy to aquire " +
      "a layer of filth and an offensive stench. " +
      "The Swine offers various bathing facilities for just " +
      "such a reason. A fat toothless clerk is ignoring you " +
      "from behind the bars of the ticket booth. There is a " +
      "pricelist on the wall. The baths are to the north.\n"));

    add_item("bars","They are quite thick and the clerk " +
      "is secure behind them.\n");
    add_item(({"booth","ticket booth"}),
      BS("It is a window in the wall. There are bars running " +
      "across it, with a small slot to exchange coins and " +
      "and tickets. A fat toothless clerk looks up at you " +
      "from behind the bars and says: " +
      "'Whaddaya want, pal?'\n"));
    add_item(({"clerk","fat clerk","toothless clerk",
      "fat toothless clerk"}), BS(
      "The fat toothless clerk is trying to ignore you " +
      "from behind the bars of the ticket booth. He " +
      "doesn't seem very happy with his job so maybe " +
      "you should buy something or leave.\n"));

   add_item(({"pricelist","list","prices"}), "@@price_long");

    add_exit(MARKET(bath/hall),"north",0,0); /*inside:no tired*/


  /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

    set_alarm(10.0, 0.0, "room_events");
}

/* random actions of clerk */
room_events()
{

   switch(random(17))
    {
      case 0:
        tell_room(TO,BS(
          "The fat toothless clerk spits on the floor.\n"));
        break;
      case 1:
        tell_room(TO,BS(
          "The fat toothless clerk grumbles about his wages.\n"));
        break;
      case 2:
        tell_room(TO,BS(
          "The fat toothless clerk glares at you from behind " +
          "the bars.\n"));
        break;
      case 3:
        tell_room(TO, BS(
          "A naked man comes running in from the north. As " +
          "he runs past you notice his face has turned green " +
          "and he is breaking out in welts. He dashes outside " +
          "and the fat toothless clerk yells after him: " +
          "'There's no running in here you bum!'\n"));
        break;
      case 4:
        tell_room(TO,BS("A half clad man with wet hair enters " +
          "from the north and complains that his towel has " +
          "been stolen. The clerk points at a sign and sends " +
          "him away.\n"));
        break;
      case 5:
        tell_room(TO,
          "A small rough-clad boy arrives.\n");
        set_alarm(2.0, 0.0, "boy_north");
        break;
      case 6:
        tell_room(TO,"The fat toothless clerk grinds his teeth.\n");
        break;
      case 7:
        tell_room(TO,BS(
          "A couple dirty men straggle in. " +
          "They buy tickets and leave north.\n"));
        break;
      case 8: case 9:
        tell_room(TO,BS(
          "A man arrives, buys a ticket, and leaves north.\n"));
        break;
      case 10: case 11:
        tell_room(TO,"A woman arrives, buys a ticket, and leaves north.\n");
        break;
      case 14:
        tell_room(TO,
          "Four well-clad men arrive and order a key.\n" +
          "The men look around suspiciously before leaving north.\n");
        break;
      case 15: case 16:
        tell_room(TO,
          "A woman arrives, looking clean, and leaves south.\n");
        break;
      case 12: case 13:
        tell_room(TO,
          "A man arrives, looking clean, and leaves south.\n");
        break;
    }

    set_alarm(20.0, 0.0, "room_events");
}

boy_north()
{
    tell_room(TO,"A small rough-clad boy leaves north.\n");
    set_alarm(2.0, 0.0, "boy_arrives");
    return;
}

boy_arrives()
{
    tell_room(TO,
      "A small rough-clad boy arrives carrying some towels.\n");
    set_alarm(2.0, 0.0, "boy_out");
    return;
}

boy_out()
{
    tell_room(TO,
      "A small rough-clad boy leaves outside.\n");
    return;
}

init() {
   ::init();
   add_action("do_read","read",0);
   add_action("do_buy","buy",0);
}

do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "prices")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() {
   return (
      "**************************************************\n"
    + "*                                                *\n"
    + "*  Public Bath Ticket   ...   10 copper coins    *\n"
    + "*  Public Sauna Ticket  ...    2 silver coins    *\n"
    + "*  Private Bath Ticket  ...    2 silver coins    *\n"
    + "*  Private Sauna Key    ...    4 silver coins    *\n"
    + "*                                                *\n"
    + "*  Notice: No entrance into Sauna unless clean!  *\n"
    + "*          No singing in baths! No refunds!      *\n"
    + "*                                                *\n"
    + "**************************************************\n"
     + "");
}


do_buy(str) {
    object ticket;
   string item_name;

   if (!str || str == "")
      return 0;

 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s with %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s with %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

    if (item_name == "public bath" || item_name == "public bath ticket")
   {
      if(can_afford(MY_PRICES[0], "public bath ticket"))
      {
         ticket = clone_object(MRKT_PATH(bath/pub_bath_ticket));
         if(ticket->move(this_player()))
         {
            write("You cannot carry that much!\n");
            return 1;
         }
         say(QCTNAME(this_player()) + " buys a public bath ticket.\n");
      }
      return 1;
   }

    if (item_name == "public sauna" || item_name == "public sauna ticket")
    {
      if(can_afford(MY_PRICES[1], "public sauna ticket"))
      {
        ticket = clone_object(MRKT_PATH(bath/pub_sauna_ticket));
        if(ticket->move(this_player()))
        {
          write("You cannot carry that much!\n");
          return 1;
        }
        say(QCTNAME(this_player()) + " buys a public sauna ticket.\n");
      }

      return 1;
    }

    if (item_name == "ticket" || item_name == "bath" || item_name == "sauna")
    {
      tell_room(TO,BS(
        "The fat toothless clerk spits: " +
        "Which " + item_name + ", you moron?!\n"));
      return 1;
    }

   return 0;
}

/* Test if this_player can afford the price */
can_afford(price, ticket) {
 /* Try to take the money */
   if (sizeof(money_arr = pay(price, this_player(), pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 2)
      {
        tell_room(TO, BS(
          "The fat toothless clerk spits: " +
          "Idiot! You don't have any " + pay_type +
          " coins, " + TP->query_nonmet_name() + "!\n"));
         return 0;
      }
      if (money_arr[0] == 1)
      {
        tell_room(TO, BS(
          "The fat toothless clerk spits: " +
          "Dolt! You don't have enough " + pay_type +
          " coins to pay for that " + ticket +
          ", " + TP->query_nonmet_name() + "!\n"));
         return 0;
      }
      else
      {
        tell_room(TO, BS(
          "The fat toothless clerk gracefully announces: " +
          "You can't cough up enough for that " + ticket +
          ", " + TP->query_nonmet_name() + "! Get outta here " +
          "ya deadbeat!\n"));
         return 0;
      }
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You order a " + ticket + " and pay " + coin_pay_text + ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back.\n");
   return 1;
}
