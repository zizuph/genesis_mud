// /d/Avenir/common/outpost/smithy.c
// Lilith, Apr 2022
// added as part of the Fort makeover


#include "/d/Avenir/common/outpost/outpost.h"

inherit OUTPOST +"fort_base";
inherit "/lib/trade";

#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>

#define MEND_COST    50 /* Mending will cost 50% of the weapon's price */
#define WAX_COST     20 /* Waxing costs 10% per point */
#define SHARPEN_COST 20 /* Sharpening as well */
#define SEE_EAST   ({ OUTPOST + "armorer" })


string 
east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " with "+ COMPOSITE_LIVE(live) + " watching over "+
       "them";
  }
  return "";
}
/* Prototypes */
int calc_sharpen_value(object o);
int calc_wax_value(object o);
int calc_mend_value(object o);
int distort(int i);

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_fort_room()
{
    set_short("the Weaponsmith of Fort Sybarus");
    set_long("You've entered the weaponsmith's forge in Fort Sybarus. "+
        "It almost exclusively serves the guards stationed here, but "+
        "the weaponsmiths will help visitors with repairs when they "+
        "have the time. "+
        "There is a contraption made of chains and buckets "+
		"that hangs down into a hole in the floor. "+
        "Beside it, a wooden ladder descends into the "+
        "same hole. "+
        "There are a few workstations with anvils and tools where "+
        "dwarven smiths gleaming with sweat can be seen pounding "+
        "and quenching metal. "+ 
		"On the west wall is a large sign. "+
		"You may leave up to go toward the center of the fort, "+
        "or go east to where the armourers are hard at work"+
        "@@east_view@@.\n");

    add_exit("forge_entry",  "up",0);
    add_exit("armorer","east", 0);
    add_exit("forge",  "down", 0);

    add_fort_room();
	add_exit_views();
	
    add_item(({"list", "pricelist", "sign", "little sign"}), "@@sign_long");
    add_item("forge", "It's black and made of cast iron.\n");
    add_item("soot", "Soot from the forge.\n");
    add_item(({"contraption", "buckets", "chains", "lift", 
	    "bucket lift", "bucket-lift", "hole", "hole in the floor"}),
        "This is a bucket-lift, a contraption designed to lift "+
        "and lower metals and ores between the foundry and "+
        "forges below and the smithy and armourer above.\n");
    add_item(({"workstation", "workstations", "anvil", "anvils",
        "tools", "smiths", "dwarven smiths", "metal"}),
        "There are a few workstations with anvils and tools where "+
        "dwarven smiths gleaming with sweat can be seen pounding "+
        "and quenching metal.\n"); 

    config_default_trade();     /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");
	
    add_npc(OUTPOST +"mon/smith", 1);
}


public int
check_smith_presence()
{
    if ( !present("fronkildor") )
    {
        return 0;
    }
    return 1;
}


int
do_mend(string str)
{

    NF("There is no smith here to serve you.\n");
    if ( !check_smith_presence() )
        return 0;

    write("The weaponsmith says: Sorry, it is illegal for me to fix " +
        "broken weapons.\n");
    return 1;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
//    add_action("do_mend", "mend",    0);
    add_action("do_fix",  "mend",    0);
    add_action("do_fix",  "sharpen", 0);
    add_action("do_fix",  "wax",     0);
    add_action("do_read", "read",    0);
    add_action("do_cost", "cost",    0);
}

/*
 * Function name: sign_long
 * Description:   The long desription of the sign
 * Returns:       what is written on the sign.
 */
 
public string
sign_long()
{
    return
	    
        "Weapon care and improvement:\n"
      + "----------------------------\n"
      + "Sharpen dull weapons\n"
      + "Wax corroded weapons\n"
      + "\n"
      + "All prices depend on the value of the weapon.\n"
      + "Do \"cost <weapon>\" to see the costs.\n";
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */
public int
do_read(string str)
{
    NF("Read what?\n");
    if (str != "list" && str != "pricelist" &&
        str != "sign" && str != "little sign")
        return 0;

    write(sign_long());
    return 1;
}

/*
 * Function name: do_cost
 * Description:   Handle the cost action
 * Returns:       1/0
 */
public int
do_cost(string str)
{
    object *weapon;
    int v1, v2, v3;
    string sharp_resp, wax_resp, mend_resp;

    NF("Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str, TP)) ||
        !sizeof(weapon))
    {
        return 0;
    }


    NF("There is no smith here to serve you.\n");
    if ( !check_smith_presence() )
    {
        return 0;
    }


    if (sizeof(weapon) > 1)
    {
        write("The weaponsmith says: Be more specific. Which one?\n");
        return 0;
    }

    if (function_exists("create_object",weapon[0]) != "/std/weapon")
    {
        write("The weaponsmith grumbles: That is not really a weapon.\n");
        return 0;
    }

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    v3 = calc_mend_value(weapon[0]);

    sharp_resp = "Sharpening that " + weapon[0]->short() + " " +
        ((v1 == -1) ? "is not necessary."
         : ("would cost about " + distort(v1) +
            " coppers."));

    wax_resp = "Waxing it " +
        ((v2 == -1) ? "is not necessary."
         : ("would cost about " + distort(v2) +
            " coppers."));

    mend_resp = "Mending it " +
        ((v3 == -1) ? "is not necessary."
         : ("would cost about " + distort(v3) +
            " coppers."));

    write("The weaponsmith says: " + sharp_resp);
    write("The weaponsmith says: " + wax_resp);
    write("The weaponsmith says: " + mend_resp);


    return 1;
}

/*
 * Function name: do_fix
 * Description:   Handle the repairing actions: mend, sharpen and wax.
 * Returns:       1/0
 */
public int
do_fix(string str)
{
    object *weapon;
    int int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
    verb;

    verb = query_verb();

    if (!str)
    {
        notify_fail(capitalize(verb) + " what?\n");
        return 0;
    }

    if ( !check_smith_presence() )
    {
        notify_fail("There is no smith here to serve you.\n");
        return 0;
    }

   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
    if (sscanf(str, "%s for %s and get %s", item_name, pay_type, get_type) != 3)
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
        if (member_array(pay_type, MONEY_TYPES)< 0)
        {
            write("The weaponsmith says: I don't accept those " +
                pay_type + " coins, " + TP->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    if (get_type != "")
    {
        if (member_array(get_type, MONEY_TYPES)< 0)
        {
            write("The weaponsmith says: " + capitalize(get_type) +
                    " coins? Never heard of those.\n");
            return 1;

        }
    }

    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
        !sizeof(weapon))
    {
        write("The weaponsmith says: " + capitalize(verb) + " what?\n");
        return 1;
    }

    if (sizeof(weapon) > 1)
    {
        write("The weaponsmith says:  Be more specific. Which one?\n");
        return 1;
    }

    if (function_exists("create_object", weapon[0]) != "/std/weapon")
    {
        write("The weaponsmith says: That is not really a weapon.\n");
        return 1;
    }

    /* Talk about tricky code! ;-) */
    value = call_other(TO, "calc_" + verb + "_value", weapon[0]);

    if (value == -1)
    {
        write("The weaponsmith says: I cannot " + verb + " that any further.\n");
        return 1;
    }

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {

            write("The weaponsmith says: I think that " + weapon[0]->short() +
                " is a bit more expensive, " +
                TP->query_nonmet_name() + ".\n");
            return 1;
        }

        if (money_arr[0] == 2)
        {
            write("The weaponsmith says: You do not have any " + pay_type +
                " coins, " + TP->query_nonmet_name() + ".\n");
            return 1;
        }
        else
        {
            write("The weaponsmith says: I think that " + weapon[0]->short() +
                " is a bit too expensive for you, " +
                TP->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    /* It is paid for, so let's fix the weapon */
    value = call_other(TO, "fix_" + verb, weapon[0]);

    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(TP) + " gives the smith " + TP->query_possessive() +
        " " + weapon[0]->short() + ".\n");

    tell_room(TO, "The smith " + verb + ((verb == "sharpen") ? "s" : "s") +
        " the " + weapon[0]->short() +".\n" +
        "The smith gives the weapon back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
                         sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0,
                         sizeof(MONEY_TYPES) - 1));
    write("You pay the smith " + coin_pay_text+ ".\n");
    if (coin_get_text)
    {
        write("You get " + coin_get_text + " in return.\n");
    }

    return 1;
}

/*
 * Function name: calc_wax_value
 * Description:   Calculate the cost to wax.
 * Returns:       cost to wax.
 */
public int
calc_wax_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
        obj->query_corroded()))
        return -1;

    return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

/*
 * Function name: calc_sharpen_value
 * Description:   Calculate the cost to sharpen
 * Returns:       cost to sharpen.
 */
public int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
        obj->query_dull()))
        return -1;

    return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

/*
 * Function name: calc_mend
 * Description:   Calculate the cost to mend.
 * Returns:       cost to mend.
 */
public int
calc_mend_value(object obj)
{
    if (!(obj->query_prop(OBJ_I_BROKEN)))
        return -1;

    return (F_VALUE_WEAPON(obj->query_pen(), obj->query_hit()) *
                MEND_COST/100);
}

/*
 * Function name: fix_wax
 * Description:   offset corrosion.
 */
public void
fix_wax(object obj)
{
    obj->set_repair_corr(obj->query_repair_corr() + 1);
}

/*
 * Function name: fix_wax
 * Description:   offset dullness
 */
public void
fix_sharpen(object obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
}

/*
 * Function name: fix_wax
 * Description:   remove the broken property
 */
public void
fix_mend(object obj)
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
public int
discriminate()
{
    string race;
    race = TP->query_race();

    if (race == "gnome" || race == "goblin")
        return 130;
    if (race == "elf"|| race == "human" || race == "dwarf")
        return 70;

    return 105;
}

#define F_RANGE_RANDOM(orig, max, min, value) \
       ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
     + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))

/*
 * Function name:   distort
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         distorted price
 */
public int
distort(int price)
{
    int trading;

    trading = TP->query_skill(SS_TRADING);
    if (trading > 100)
        trading = 100;
    if (trading < 0)
        trading = 0;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}



