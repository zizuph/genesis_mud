 /*
  * /d/Kalad/common/trade/cliffside/bsmith
  * The new Kalad smith, shamelessley stolen from 
  * the smith in Sanction, with Armans blessing.
  * By Zignur in october 2017
  * 
  */
 
#include "/d/Kalad/defs.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

inherit "/lib/trade";
inherit "/d/Kalad/room_std";

#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))

/* prototypes are here */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int calc_fix_value(object obj);
int distort(int price);

string current_item;

void
create_room()
{
   set_short("Blacksmith");
   set_long(
      "The heat in this forge is almost unbearable. You wonder "
    + "how the blacksmith can work in these circumstances. Here "
    + "you can have your weapons fixed. The humans of Kabal are "
    + "famous for their knowledge about weapons. So you are not "
    +"risking anything by letting them handle your weapons. "
    +"There is an anvil set on the ground, and a little sign "
    +"on the wall.\n");

    add_item(({"list","pricelist","sign"}), "@@sign_long");
    add_cmd_item(({"list","pricelist","sign"}), "read", "@@sign_long");
    add_item("anvil","A large, iron anvil. You see crusty, "+
        "black flakes along the surface.\n");
    add_item("flakes","Dark black ones, they look like old carbon from "+
        "the smelting of steel.\n");      
    add_item(({"smith","blacksmith"}),"The blacksmith looks more than "+
        "capable of reparing or fixing your weapons and armours.\n");    
    add_exit(TRADE(cliffside/cliffside7),"north");
       

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell(110);

    add_npc("/d/Kalad/common/guilds/new_thanar/npc/blacksmith");

}

void
init()
{
    ::init();
    add_action("do_fix","mend",0);
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_armour_fix", "fix", 0);
    add_action("do_cost","cost",0);
}

string
sign_long()
{
    return
    "What do we offer for your hard earned money:\n" +
    "--------------------------------------------\n" +
    "Sharpen dull weapons\n\n" +
    "Wax corroded weapons \n\n"  +
    "Mend broken weapons \n\n" +
    "Fix dented armours \n\n"+
    "All prices are dependant on the weapon.\n" +
    "Do \"cost <weapon>\" to see the costs.\n\n";
}

int
do_cost(string str)
{
    object *weapon, tp;
    int v1, v2, v3, v4;

    tp = this_player();

    notify_fail("Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
      !sizeof(weapon))
       return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
      return 0;

    if(function_exists("create_object",weapon[0]) == "/std/weapon")
    {
        current_item = "weapon";
        v1 = calc_sharpen_value(weapon[0]);
        v2 = calc_wax_value(weapon[0]);
        v3 = calc_mend_value(weapon[0]);

        write("Sharpening that " + weapon[0]->short() + " "
              + ((v1 == -1) ? "is not necessary.\n"
              : ("would cost about " + distort(v1) + " coppers.\n"))
              + "Waxing it "
              + ((v2 == -1) ? "is not necessary.\n"
              : ("would cost about " + distort(v2) + " coppers.\n"))
              + "Mending it "
              + ((v3 == -1) ? "is not necessary.\n"
              : ("would cost about " +distort(v3) + " coppers.\n"))
        );
    }
    else if(function_exists("create_object",weapon[0]) == "/std/armour")
    {
        current_item = "armour";
        v4  =  calc_fix_value(weapon[0]); 
        write("Fixing that " + weapon[0]->short() + " " +
              ((v1 == -1) ? "is not necessary.\n" :
              ("would cost about " + distort(v1) + " coppers.\n")));
    }
    else
    {
        notify_fail("I only work with weapons and armours.\n");
        return 0;
    }
    return 1;
}

int
do_fix(string str)
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
	    tell_room(this_object(), "The smith says: I don't accept " +
	      "those " + pay_type + " coins, " + 
	      tp->query_nonmet_name() + ".\n");
	    return 1;
	}
    }

    if (get_type != "")
    {
	if (member_array(get_type, MONEY_TYPES) < 0)
	{
	    tell_room(this_object(), "The smith says: " + 
	      capitalize(get_type) + " coins? Never "
	      + "heard of those.\n");
	    return 1;
	}
    }

    notify_fail(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
      !sizeof(weapon))
	return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
	return 0;

    notify_fail("That is not really a weapon.\n");
    if(function_exists("create_object",weapon[0]) != "/std/weapon")
    {
        return 0;
    }
    
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
	    tell_room(this_object(), "The smith says: I think that " + 
	      weapon[0]->short() + " is a bit more"
	      + " expensive, " + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
	if (money_arr[0] == 2)
	{
	    tell_room(this_object(), "The smith says: You do not have " +
	      "any " + pay_type + " coins, "
	      + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
	else
	{
	    tell_room(this_object(), "The smith says: I think that " + 
	      weapon[0]->short() + " is a bit too expensive "
	      + "for you, " + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
    }

    notify_fail("The smith fumes: Take it away!\nAfter a short pause he "+
	        "adds more calmly: I wish I was skilled enough to mend this weapon.\n");
    if ((weapon[0]->query_prop(MAGIC_AM_MAGIC)) && (verb == "mend"))
        return 0;

    /* It is paid for, so let's fix the weapon */
    value = call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
        " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
      "The smith " + verb + ((verb == "wax") ? "es" : "s") + " the "
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

int
calc_wax_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
	return -1;

    if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
	obj->query_corroded()))
	return -1;
    return obj->query_repair_cost_corr();
}

int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
	return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
	obj->query_dull()))
	return -1;
    return obj->query_repair_cost_dull();
}

int
calc_mend_value(object obj)
{
    if (!(obj->query_prop(OBJ_I_BROKEN)))
	return -1;
    return obj->query_repair_cost_dull();
}

int
calc_fix_value(object obj)
{
    int times, cond, rep;

    if (!(obj->query_prop(OBJ_I_BROKEN)))
	return -1;

    cond = obj->query_condition();
    rep = obj->query_repair();

    times = 0;
    while (F_LEGAL_ARMOUR_REPAIR(rep + times, cond))
      times++;
  
    return obj->query_repair_cost() * times;
}

void
fix_wax(object obj)
{
    obj->set_repair_corr(obj->query_repair_corr() + 1);
}

void
fix_sharpen(object obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
}

void
fix_mend(object obj)
{
	obj->remove_prop(OBJ_I_BROKEN);
}

int
distort(int price)
{
    int trading;

    trading = this_player()->query_skill(SS_TRADING);
    if (trading > 100)
	trading = 100;
    if (trading < 0)
	trading = 0;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}

/* Action : 
   Carry out fixing of an armour until it can't be fixed further 
*/
int
do_armour_fix(string str)
{
   object *armour, tp;
   int int_str, price, *money_arr, cond, rep, times;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;

   notify_fail("Fix what armour?\n");
   if (!str)
      return 0;

   tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " asks " + 
             "the smith to fix " + 
             tp->query_possessive() + " " + str + ".\n", tp);
   tp->catch_msg("You ask the smith to " +
                 "fix your " + str + ".\n");

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
         tp->catch_tell("The smith doesn't accept that type of payment.\n");
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         tp->catch_tell("The smith has never heard of "+ capitalize(get_type) + " coins.\n");
         return 1;
      }
   }

   if (!(armour = FIND_STR_IN_OBJECT(item_name,this_player())) ||
       !sizeof(armour))
      {
         tp->catch_tell("Fix what?\n");
         return 1;
      }

   if (sizeof(armour) > 1)
     {
      tp->catch_tell("Be specific, which one?\n");
      return 1;
     }

   if (!(armour[0]->check_armour()))
   {
     tp->catch_tell("That is not really an armour.\n");
     return 1;
   }

  /* blacksmith can't fix broken armours */
  if (armour[0]->query_prop(OBJ_I_BROKEN))
  {
    tp->catch_tell("The " + armour[0]->short() +
                   " is broken and cannot be fixed.\n");
    return 1;
  }
  
  cond = armour[0]->query_condition();
  rep = armour[0]->query_repair();
  
  if (!cond)
  {
    tp->catch_tell("The " +armour[0]->short()+" cannot be repaired " +
                   "any further!\n");
    return 1;
  }

  if (rep && !(F_LEGAL_ARMOUR_REPAIR(rep+1,cond)))
  {
    tp->catch_tell("That " +armour[0]->short()+" has been fixed " +
                   "as much as possible.\n");
    return 1;
  }

  times = 0;
  while (F_LEGAL_ARMOUR_REPAIR(rep + times, cond))
      times++;
  
  price = armour[0]->query_repair_cost() * times;
  
  /* Try to take the money */
  if (sizeof(money_arr = pay(price, tp, pay_type, 0, 0, get_type)) == 1)
  {
      if (money_arr[0] == 1)
      {
         tp->catch_tell("That repair will be a bit more expensive.\n");
         return 1;
      }
      if (money_arr[0] == 2)
      {
          tp->catch_tell("You do not have any " + pay_type + " coins.\n");
          return 1;
      }
      else
      {
          tp->catch_tell("You don't have enough money for this repair.\n");
          return 1;
      }
  }
  
   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
                        sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));

   tp->catch_msg("You pay the smith "+coin_pay_text+".\n");
  
   say(QCTNAME(tp)+" pays the smith "+coin_pay_text+ ".\n");

   if (coin_get_text)
   {
      tp->catch_msg("You get " + coin_get_text + " in return.\n");
      say(QCTNAME(tp) + " gets " + coin_get_text + " in return.\n");
   }

   tp->catch_msg("You give the smith the " 
                 + armour[0]->short() + ".\n");
   say(QCTNAME(tp) + " gives the smith " + 
       tp->query_possessive() + " " + armour[0]->short() + ".\n");

   /* carry out the fixing */
   while (F_LEGAL_ARMOUR_REPAIR(rep+1,cond))
   {
      armour[0]->set_repair((armour[0]->query_repair())+1);
      rep++;
   }

  if(!armour[0]->query_value())  /* broken */
  {
      tp->catch_tell("The smith can't fix your "+armour[0]->short()+".\n");
  }
  else
  {
      tp->catch_tell("The smith fixes your " + armour[0]->short() + " and gives it back.\n");
      say("The smith gives the fixed "+armour[0]->short()+ " back to "+QTNAME(tp)+".\n");
  }
  return 1;
}

