/* Ashlar, 5 Jul 97 - smithy, modified from the Red Quarter smithy */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

inherit INNER_IN;
inherit "/lib/trade";

#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))

/* prototypes are here */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int distort(int price);

void
create_neraka_room()
{
    set_short("the Dragon Smithy");
    set_long("You are in a large and very hot stone building, the " +
        "Dragon Smithy according to the banner over the entrance. " +
        "The room is dominated by a large forge, the source of all " +
        "the heat in the room. A sign hangs on one wall, and an " +
        "exit leads east out of this hot room.\n");
    
    add_item(({"list","pricelist","sign"}), "@@sign_long");
    add_cmd_item(({"list","pricelist","sign"}), "read", "@@sign_long");
    add_item(({"forge"}),
	     "It glows a fiery-red colour.\n");
    add_item("anvil","A large anvil stands in front of the forge.\n");
    add_item("banner",
        "The banner proclaims this place to be The Dragon Smithy.\n");
    
    add_item_inside();
    
    add_exit(NINNER + "r12", "east","@@msg@@");
    
    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
                         /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell(110);

}

int
msg()
{
    write("You step out of the hot smithy and into the cooler street.\n");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_not_fix","mend",0);
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_cost","cost",0);
}

string
sign_long()
{
    return
      "Weapon improvement:\n"
      + "-------------------\n"
      + "Sharpen dull weapons\n"
      + "Wax corroded weapons\n"
      + "\n"
      + "All prices depend on the price of the weapon.\n"
      + "Do \"cost <weapon>\" to see the costs.\n";
}

int
do_cost(string str)
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
    v3 = calc_mend_value(weapon[0]);
    
    write("Sharpening that " + weapon[0]->short() + " "
	  + ((v1 == -1) ? "is not necessary.\n"
	     : ("would cost about " + distort(v1) + " coppers.\n"))
	  + "Waxing it "
	  + ((v2 == -1) ? "is not necessary.\n"
	     : ("would cost about " + distort(v2) + " coppers.\n"))
	  + "Mending it "
	  + ((v3 == -1) ? "is not necessary.\n"
	     : ("is necessary but cannot be done here.\n"))
//	     : ("would cost about " + distort(v3) + " coppers.\n"))
	  );
    return 1;
}

int
do_not_fix(string str)
{
    write("Sorry, this option is currently unavailable.\n");
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
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
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
    return obj->query_repair_cost_dull()*2;
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
    //obj->remove_prop(OBJ_I_BROKEN);
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
