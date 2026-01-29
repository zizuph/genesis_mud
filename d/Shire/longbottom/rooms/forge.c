/* 
 * Forge of Longbottom
 * Based on the Forge of Hobbiton
 * -- Finwe, January 2020
 */
#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

#define MEND_COST    50	/* Mending will cost 50% of the weapon's price */
#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */

create_room()
{
    set_short("Forge of Longbottom");
    set_long("This is the vilage forge in Longbottom. The room is hot " +
        "from the forge center of the room. The blacksmith makes various " +
        "tools, household objects for the hobbits of the village. He " +
        "also sharpens and repairs weapons. A small sign hangs on " +
        "the wall.\n");


//   set_long("The heat in this forge is almost unbearable. You wonder "
//    + "how the blacksmith can work in these circumstances. Here "
//    + "you can have your weapons improved. "
//    + "A little sign is hanging on the wall.\n");

   add_item(({"list","pricelist","sign","little sign"}), "@@sign_long");

   add_exit(LB_RM_DIR + "lb03", "southwest");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   config_default_trade();  /* Set up the trading system */
   set_money_give_max(100000); /* Else things go wrong with "sell all" */
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
   set_money_greed_sell("@@discriminate");

   reset_shire_room();
}

reset_shire_room()
{

}

init()
{
   ::init();
//   add_action("do_fix","mend",0);
   add_action("do_fix","sharpen",0);
   add_action("do_fix","wax",0);
   add_action("do_read","read",0);
   add_action("do_cost","cost",0);
}

sign_long()
{
   return
      "Weapon improvement:\n"
    + "-------------------\n"
//    + "Mend damaged weapons\n"
    + "Sharpen dull weapons\n"
    + "Wax corroded weapons\n"
    + "\n"
    + "All prices depend on the price of the weapon.\n"
    + "Do \"cost <weapon>\" to see the costs.\n";
}

do_read(str)
{
   notify_fail("Read what?\n");
   if (str != "list" && str != "pricelist" &&
       str != "sign" && str != "little sign")
      return 0;

   write(sign_long());
   return 1;
}

do_cost(str)
{
   object *weapon, tp;
   int v1, v2, v3;

   tp = this_player();

   notify_fail("Which weapon?\n");
   if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
       !sizeof(weapon))
      return 0;

   notify_fail("Be more specific. Which one?\n");
   if (sizeof(weapon) > 1)
      return 0;

   notify_fail("That is not really a weapon.\n");
   if (function_exists("create_object",weapon[0]) != "/std/weapon")
      return 0;

   v1 = calc_sharpen_value(weapon[0]);
   v2 = calc_wax_value(weapon[0]);
//   v3 = calc_mend_value(weapon[0]);

   write("Sharpening that " + weapon[0]->short() + " "
       + ((v1 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v1) + " coppers.\n"))
       + "Waxing it "
       + ((v2 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v2) + " coppers.\n"))
                     );
//       + "Mending it "
//       + ((v3 == -1) ? "is not necessary.\n"
//                     : ("would cost about " + distort(v3) + " coppers.\n")));
   return 1;
}

do_fix(str)
{
   object *weapon, tp;
   int int_str, value, *money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;

   verb = query_verb();

   notify_fail(capitalize(verb) + " what?\n");
   if (!str)
      return 0;

   tp = this_player();

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

   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), 
            "The smith says: I don't accept those " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n");
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         tell_room(this_object(), 
            "The smith says: " + capitalize(get_type) + " coins? Never "
          + "heard of those.\n");
         return 1;
      }
   }

   notify_fail("Mend what?\n");
   if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
       !sizeof(weapon))
      return 0;

   notify_fail("Be more specific. Which one?\n");
   if (sizeof(weapon) > 1)
      return 0;

   notify_fail("That is not really a weapon.\n");
   if (function_exists("create_object",weapon[0]) != "/std/weapon")
      return 0;

   notify_fail("I cannot repair broken weapons.\n");
    if(weapon[0]->query_prop(OBJ_I_BROKEN))
   return 0;
   /* Talk about tricky code! ;-) */
   value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

   notify_fail("The smith says: I cannot " + verb + " that any further.\n");
   if (value == -1)
      return 0;

   /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         tell_room(this_object(), 
            "The smith says: I think that " + weapon[0]->short() + " is a bit "
          + "more expensive, " + tp->query_nonmet_name() + ".\n");
         return 1;
      }
      if (money_arr[0] == 2)
      {
         tell_room(this_object(), 
            "The smith says: You do not have any " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n");
         return 1;
      }
      else
      {
         tell_room(this_object(), 
            "The smith says: I think that " + weapon[0]->short() + " is a bit "
          + "too expensive for you, " + tp->query_nonmet_name() + ".\n");
         return 1;
      }
   }

   /* It is paid for, so let's fix the weapon */
   value = call_other(this_object(), "fix_"+verb, weapon[0]);

   write("You give the smith the " + weapon[0]->short() + ".\n");
   say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
       " " + weapon[0]->short() + ".\n");

   tell_room(this_object(),
        "The smith " + verb + ((verb == "sharpen") ? "s" : "es") + " the "
      + weapon[0]->short() + ".\n"
      + "The smith gives the weapon back.\n");

   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
			sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
   write("You pay the smith " +coin_pay_text+ ".\n");
   if (coin_get_text)                                          
      write("You get " + coin_get_text + " in return.\n");

   return 1;
}

calc_wax_value(obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
                                  obj->query_corroded()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

calc_sharpen_value(obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
                                  obj->query_dull()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

calc_mend_value(obj)
{
   if (!(obj->query_prop(OBJ_I_BROKEN)))
      return -1;
   return (F_VALUE_WEAPON(obj->query_pen(), obj->query_hit()) * MEND_COST)/100;
}

fix_wax(obj)
{
   obj->set_repair_corr(obj->query_repair_corr() + 1);
}

fix_sharpen(obj)
{
   obj->set_repair_dull(obj->query_repair_dull() + 1);
}

fix_mend(obj)
{
   obj->remove_prop(OBJ_I_BROKEN);
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
discriminate()
{
   string race;
   race = this_player()->query_race();

   /* This is a Hobbit shop; they are suspicious of big folk and gnomes */
   if (race == "gnome" || race == "human" || race == "goblin")
      return 110;
   if (race == "hobbit")
      return 101;
   return 105;
}

#define F_RANGE_RANDOM(orig, max, min, value) \
       ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
     + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))


distort(price)
{
   int trading;

   trading = this_player()->query_skill(SS_TRADING);
   if (trading > 100)
      trading = 100;
   if (trading < 0)
      trading = 0;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}
