/*
 *  The standard post office for the domain Gondor
 *
 *  - Olorin, January 1995
 *
 * Usage:
 * Call create_post() from your create_room() function,
 * if desired, use set_poster_name() to add additional
 * names to the poster.
 * Define the function mail_message() if the post office
 * is defined in a query_post() function in a guild shadow.
 *
 * Modification log:
 * 13-Jul-1997, Olorin: Added feathers.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/lib/trade";
inherit "/d/Genesis/lib/post";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"

#define RAT_VALUE	12
#define NUM		sizeof(MONEY_TYPES)

public int     do_hire(string str);

void
create_post() 
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE,1);

    config_default_trade();  /* Set up the trading system */
                         /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */
}

void
init() 
{
    ::init();
    add_action(do_hire, "hire",0);

    post_init();
}

public int
do_hire(string str) 
{
   object  rat;
   string  item_name,
           pay_type,
           get_type,
           str1,
           coin_pay_text,
           coin_get_text;
   int    *money_arr;

   if (!str)
   {
       NF("Hire what? A rat?\n");
       return 0;
   }

   TP->reveal_me(1);
 /*   Check if the player defines what she wants to pay with
  *   and what you would like in return.
 */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (!(item_name == "rat" || item_name == "black rat"))
   {
      NF("Hire what? A rat?\n");
      return 0;
   }

   if (sizeof(money_arr = pay(RAT_VALUE, TP, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a rat "
          + "with only those coins, "
          + TP->query_race_name() + "."));
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), BSN(
            "The post master says: You have no " + pay_type + " coins on you, "
          + TP->query_race_name() + "."));
         return 1;
      }
      else
      {
         tell_room(this_object(), BSN(
            "The post master says: You cannot afford a rat, "
          + TP->query_race_name() + "."));
         return 1;
      }
   }

 /* Okay, the rat is paid for, now give it to the player */
   rat = clone_object("/d/Shire/misty/obj/post_rat");
   if(rat->move(TP))
   {
      write("You cannot carry that much!\n");
      rat->remove_object();
      return 1;
   }

   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

   write("You pay " +coin_pay_text+ " and hire yourself a rat.\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " back from the small goblin.\n");
   say(QCTNAME(TP) + " hires " + TP->query_objective()
     + "self a rat.\n");
   return 1;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

/*
 * Function name: silent_room
 * Description  : This function catches all commands. Players will be allowed
 *                to use various commands related to mail, the game and the
 *                exits, but disallows all others.
 *                Mask parent to accept the allowed gondor po verbs.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - player blocked/player not blocked.
 */
public int
silent_room(string str)
{
    string verb = query_verb();

    if (member_array(verb, ALLOWED_PO_VERBS) >= 0)
    {
        return 0;
    }
    return ::silent_room(str);
}

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Gondor")
    {
        return 0;
    }
    return ::query_prevent_snoop();
}

