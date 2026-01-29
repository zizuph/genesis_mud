/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Blacksmith forge of Last
 *
 * Shinto, March 98
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/lib/trade";

#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>

#define MEND_COST    60							/* Mending will cost 50% of the weapon's price
*/
#define WAX_COST     20 /* Waxing costs 10% per point */
#define SHARPEN_COST 20 /* Sharpening as well */

#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
int enemy_check();
int race_invis_enemy();

/* Prototypes */
int calc_sharpen_value(object o);
int calc_wax_value(object o);
int calc_mend_value(object o);
int distort(int i);
object keeper, door;
/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Blacksmith of Calathin");
    set_long("You are in the blacksmith of Calathin.  The room is " +
	     "illuminated by a deep orange glow from the massive forge " +
	     "where the weapon smith works his trade.  The walls and ceiling " +
	     "are coated with a layer of black soot. To the east you " +
             "see another smaller forge. A little sign is hanging on the wall.\n");

    add_item(({"list", "pricelist", "sign", "little sign"}), "@@sign_long");
    add_item("forge", "It's black and made of cast iron.\n");
    add_item("soot", "Soot from the forge.\n");

    INSIDE;

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");
    door = clone_object(CALATHIN_DIR + "obj/forge_door");
    door->move(TO);

    add_exit(CALATHIN_DIR + "terel_forge", "east", 0);

    set_alarm(0.0, -1.0, "reset_room");
}

/*
 * Function name: reset_room
 * Description:   clone the dog if necessary
 */
public void
reset_room()
{
    if (!present("keeper")) 
    {
        keeper = clone_object(CALATHIN_DIR+"npc/blacksmith");
				keeper->move_living("east", TO);
    }
}

int
do_mend(string str)
{
    keeper->command("say I can't mend broken weapons, it's just not done "+
                                 "anymore.");
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
    add_action("do_mend",  "mend",    0);
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
																									"Weapon improvement:\n"
      + "-------------------\n"
      + "Sharpen dull weapons\n"
      + "Wax corroded weapons\n"
      + "\n"
      + "All prices depend on the price of the weapon.\n"
      + "Do \"cost <weapon>\" to see the costs.\n\n"
      + "Guest Smiths may use the smaller forge through the eastern exit\n";
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */ 
public int
do_read(string str)
{
    if (str != "list" && str != "pricelist" &&
				str != "sign" && str != "little sign")
    {
        NF("Read what?\n");
        return 0;
    }

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

    if(!present("keeper"))
    {
        write("The smith is not here.\n");
        NF("");
        return 0;
    }

    if (!str || !(weapon = FIND_STR_IN_OBJECT(str, TP)) || !sizeof(weapon))
		{
        keeper->command("say Which weapon?");
        NF("");
        return 0;
    }

    if(race_invis_enemy())
    {
         NF("");
         return 0;
    }

    if (sizeof(weapon) > 1)
    {
        keeper->command("say Be more specific, which one?");
        NF("");
        return 0;
    }

    if (function_exists("create_object",weapon[0]) != "/std/weapon")
		{
        keeper->command("say That is not really a weapon.");
        NF("");
        return 0;
    }

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    v3 = calc_mend_value(weapon[0]);

    write("Sharpening that " + weapon[0]->short() + " "
																									  + ((v1 == -1) ? "is not necessary.\n"
																									     : ("would cost about " + distort(v1) + 
                                                    " coppers.\n"))
																									  + "Waxing it "
																									  + ((v2 == -1) ? "is not necessary.\n"
																									     : ("would cost about " + distort(v2) + 
                                                    " coppers.\n"))
																									  + "Mending it "
																									  + ((v3 == -1) ? "is not necessary.\n"
																									     : ("would cost about " + distort(v3) + 
                                                    " coppers.\n")));
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
        NF(capitalize(verb) + " what?\n");
        return 0;
    }
    if(!present("keeper"))
    {
        write("The smith is not here.\n");
        NF("");
        return 0;
    }

    /* Code to check for invis players, enemies, goblins, and if the room is dark. */
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }

   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
   if (sscanf(str, "%s for %s and get %s", item_name, pay_type, get_type) != 3)
   {
       get_type = "";
       /* Hmmm... Maybe she only wishes to pay with a certain type */
       if (sscanf(str, "%s for %s", item_name, pay_type) != 2) {
																									   pay_type = "";
																									   item_name = str;
       }
   }

    if (pay_type != "") 
    {
        if (member_array(pay_type, MONEY_TYPES)< 0) 
        {
		        tell_room(TO, "The smith says: I don't  accept those " + pay_type +
														 " coins, " + TP->query_nonmet_name() + ".\n");
																									    return 1;
				}
    }

    if (get_type != "") 
    {
				if (member_array(get_type, MONEY_TYPES)< 0) 
        {
						if (present("keeper")) 
            {
								keeper->command("say " + capitalize(get_type) +
																       "coins? Never heard of those.\n");
								return 1;
					  }
        }
    }


    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||!sizeof(weapon))
		{
        keeper->command("say Mend what?");
        NF("");
        return 0;
    }

    if (sizeof(weapon) > 1)
    {
        keeper->command("say Be more specific. Which one?");
        NF("");
				return 0;
    }

    if (function_exists("create_object", weapon[0]) != "/std/weapon")
    {
        keeper->command("say That's not really a weapon.");
        NF("");
        return 0;
    }

    /* Talk about tricky code! ;-) */
    value = call_other(TO, "calc_" + verb + "_value", weapon[0]);

    if (value == -1)
    {
        keeper->command("say I cannot " + verb + " that any further.");
        NF("");
				return 0;
    }


    /* Try to take the money */
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1) 
    {
        if (money_arr[0] == 1) 
        {
            if (present("keeper")) 
            {
                keeper->command("say I think that " +
                    weapon[0]->short() + " is a bit more expensive, " +
                    TP->query_nonmet_name() + ".\n");
            }
            return 1;
        }
        if (money_arr[0] == 2) 
        {
            keeper->command("say You do not have any " + pay_type +
            " coins, " + TP->query_nonmet_name() + ".\n");
            return 1;
        }
        else 
        {
            keeper->command("say I think that " +
            weapon[0]->short() + " is a bit too expensive for " +
            "you, " + TP->query_nonmet_name() + ".\n");
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
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES) - 1));
    write("You pay the smith " + coin_pay_text+ ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");
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
    {
        return -1;
    }
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
    {
        return -1;
    }
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
    {
        return -1;
    }
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



int
race_invis_enemy()
{
    int chat;
    chat = random(5);

    if(!CAN_SEE_IN_ROOM(keeper) || !CAN_SEE(keeper, TP))
    {
        switch(chat)
        {
            case 0:
                keeper->command("say If you want to do business turn on "+
                              "the light.");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say I can't see what you want to sell.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's turned out the lights?");
                keeper->command("peer");
                break;
        }
        return 1;
    }
    if(TP->query_prop(OBJ_I_INVIS))
    {
        switch(chat)
        {
            case 0:
                keeper->command("peer");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say Damn rats.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's there?");
                keeper->command("peer");
                break;
        }
        return 1;
    }
    if(enemy_check())
    {
        switch(chat)
        {
            case 0:
                keeper->command("say You enter our home and slay us and now "+
                "you want us to do business with you?");
                break;
            case 1:
                keeper->command("say I refuse to do business with enemies of "+
                "out town!");
                break;
            case 2:
                keeper->command("say Get out! I want no business from you!");
                break;
            case 3:
                keeper->command("say You've got a lot of nerve, get out of "+
                "here!");
                break;
            case 4:
                keeper->command("say Leave now, or if the guards don't find "+
                "you I'll call them!");
                break;
        }
        return 1;
    }


    /*
     * This used to use query_race() which does not work well in this
     * era in which we might have subraces that do not match the intention of
     * the coder. I presume that "orcs" would still be discriminated against,
     * but "ogres" perhaps should not be. So, I've changed it to use
     * query_race_name() so that subraces of goblins which may not be
     * fully goblinlike can still use this place.
     *
     * Gorboth, August 2009
     */
    if (TP->query_race_name() == "goblin" ||
        TP->query_race_name() == "orc")
    {
        switch(chat)
        {
            case 0:
                keeper->command("say I don't deal with goblins.");
                break;
            case 1:
                keeper->command("say I won't do business with goblins.");
                break;
            case 2:
                keeper->command("say Get out, I don't do business with "+
                "goblins.");
                break;
            case 3:
                keeper->command("say Goblins will recieve no business in "+
                "Calathin.");
                break;
            case 4:
                keeper->command("say I don't buy, sell, value, or trade to "+
                "goblins.");
                break;
        }
        return 1;
    }
    return 0;
}


int
enemy_check()
{
    object kill_logger = find_object(KILL_LOGGER);
    if(kill_logger->query_killer(TP->query_name()))
    {
        return 1;
    }
    return 0;

}


