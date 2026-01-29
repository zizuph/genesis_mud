/*
 * The weapon smith of Minas Tirith
 *
 * Olorin, 15-nov-1994
 *
 * Weapons:
 * no clubs and maces
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";
inherit "/d/Gondor/common/lib/friend_or_foe";
inherit "/lib/shop";

#include <cmdparse.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

#define MT_WEAPON	(MINAS_DIR + "obj/mt_weapon")

#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */

#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })

#define DEBUG 0

// prototypes are here
int     calc_sharpen_value(object obj);
int     calc_wax_value(object obj);
int     distort(int price);
object  buy_weapon(string wt, string str2, string str3);
void    unwield_weapon();


// Global variables 
string  working = 0;
int     reset_alarm = 0,
        work_alarm,
        report_alarm,
        report_stage;

void
create_dunadan()
{
    set_name("herumegil");

    add_name(({"smith", "weapon smith", "weapon maker", }));

    set_race_name("human");

    set_adj(({"strong", "dark-skinned"}));

    set_title("Master Weapon Smith");
    set_dunedain_house("Hador");

    set_long(BSN("This strong dark-skinned dunadan is one of the "
      + "weapon smiths of Minas Tirith. His mighty arms and his dark "
      + "sweaty skin are testimony of his profession. While he is "
      + "working for the Guard of the Tower most of his time, he also "
      + "accepts orders from citizens and travellers."));

    default_config_npc(80);
    set_base_stat(SS_STR, 100);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alignment(250);

    set_tell_active(1);

    config_default_trade();
    set_money_give_max(1000);
    set_money_greed_sell("@@discriminate");

//    set_default_answer(VBFC_ME("default_answer"));
    set_default_answer(
        QCTNAME(TO) + " says: To see what I sell, please look at the pricelist!\n" +
        QCTNAME(TO) + " says: I can also sharpen and wax your weapons.\n" +
        QCTNAME(TO) + " says: If you want to know the price of my service, ask me for the cost!\n");
    // for the Whodunnit: Herumegil will give a red herring
    add_ask(({"dagger", "ornate dagger", "murder weapon", }),
        VBFC_ME("ask_dagger"));

    set_act_time(4);
    add_act("glitter");
    add_act("emote hammers heavily at the anvil.");
    add_act("sing tinuviel");
    add_act("sing gil-galad");
    add_act("emote wipes the sweat from his brows.");
    add_act("emote swings his mighty hammer on the anvil.");
    add_act("emote hammers on a glowing piece of steel.");
    add_act("emote dips a glowing piece of steel into a bucket of water. "
      + "A cloud of steam rises as the hot metal cools down.");
    add_act("emote puts a piece of steel into the hot forge, "
      + "using his pliers to turn the glowing coals around it.");

    set_equipment( ({ WEP_DIR + "smithhammer", ARM_DIR + "smithapron" }) );
}

string
default_answer()
{
    command("say To see what I sell, please look at the pricelist!");
    command("say I can also sharpen and wax your weapons.");
    command("say If you want to know the price of my service,");
    command("say ask me for the cost!");

    return "";
}

void
answer_weapon()
{
    command("say I fabricate swords, polearms, axes, and daggers.");
    command("say Look at the weapons displayed on the walls to see "
      + "what is in stock.");
}

int query_knight_prestige() { return -5; }

int
do_cost(object weapon, object tp)
{
    int     v1,
            v2;
    string  it,
            what = "";

    if (function_exists("create_object",weapon) != "/std/weapon")
    {
        command("say That is not a weapon!");
        return 0;
    }
    
    if (weapon->query_prop(OBJ_I_BROKEN))
    {
        command("say But that " + weapon->short() + " is broken!");
        command("say Why don't you buy a new weapon?");
        return 1;
    }

    v1 = calc_sharpen_value(weapon);
    v2 = calc_wax_value(weapon);
    
    it = "that " + weapon->short();

    if (v1 > -1)
    {
        command("say Sharpening "+it+" would cost about "
          + distort(v1) + " coppers.");
        it = "it";
        what = "sharpen";
    }
    if (v2 > -1)
    {
        command("say Waxing "+it+" would cost about "
          + distort(v2) + " coppers.");
        if (strlen(what))
            what += " or ";
        what += "wax";
    }

    if (v1 == -1 && v2 == -1)
        command("say "+CAP(it)+" needs neither sharpening nor waxing!");
    else
        command("say If you want me to "+what+" the weapon, ask me to do so.");

    return 1;
}

int
do_fix(object weapon, object tp, string verb)
{
    int     int_str,
            value,
           *money_arr;
    string  item_name,
            coin_pay_text,
            coin_get_text;
    
    if (function_exists("create_object",weapon) != "/std/weapon")
    {
        command("say That "+weapon->short()+" is no weapon!");
        return 0;
    }
    
    /* Talk about tricky code! ;-) */
    value = call_other(TO, "calc_"+verb+"_value", weapon);

    if (value <= 0)
    {
        command("say I cannot " + verb + " that any further.");
        return 0;
    }
    
    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, "", 0, 0, "")) == 1)
    {
        if (money_arr[0] == 1)
        {
            command("say I think that " + weapon->short() + " is a bit more"
              + " expensive, " + tp->query_nonmet_name() + ".");
            return 1;
        }
        command("say I think that "+weapon->short()+" is a bit too expensive "
          + "for you, " + tp->query_nonmet_name() + ".\n");
        return 1;
    }
    
    /* It is paid for, so let's fix the weapon */
    value = call_other(TO, "fix_"+verb, weapon);
    
    tp->catch_msg("You give the " + weapon->short() + " to " + QTNAME(TO) + ".\n");
    say(QCTNAME(tp) + " gives " + tp->query_possessive() +
	" " + weapon->short() + " to " + QTNAME(TO) + ".\n");
    
    command("emote "+ verb + ((verb == "wax") ? "es" : "s") + " the "
	      + weapon->short() + ".");
    command("emote gives the weapon back.");
    
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    tp->catch_msg("You pay "+coin_pay_text+" to " + QTNAME(TO) + ".\n");
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
    return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
      return -1;
    
    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
				    obj->query_dull()))
      return -1;
    return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
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

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    string race;
    race = TP->query_race();
    
    /* This is a dunadan; they are suspicious of elves, dwarves, et al */
    if (race == "goblin")
        return 120;
    if (race == "human")
        return  90;
    if (race == "dwarf" || race == "elf")
        return 110;

    return 100;
}

#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))


int
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

/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void
catch_question(string question)
{
    int     n;
    object  tp = TP,
           *wep;
    string *arr,
            str2,
            str;

#if DEBUG
    if (query_friend_or_foe(tp) < -1)
#else
    if (query_friend_or_foe(tp) < 0)
#endif
    {
        command("say We do not want you here in Minas Tirith!");
        command("say Leave before I call the guards!");
        return;
    }

    question = LOW(question);

    if (question == "cost")
    {
        command("peer "+tp->query_real_name());
        command("say The cost for which weapon?");
        return;
    }

    if (question == "sharpen")
    {
        command("peer "+tp->query_real_name());
        command("say Sharpen which weapon?");
        return;
    }

    if (question == "wax")
    {
        command("peer "+tp->query_real_name());
        command("say Wax which weapon?");
        return;
    }

    if (question == "weapon" || question == "weapons" ||
        question == "manufacture")
    {
        answer_weapon();
        return;
    }

    if (parse_command(question, all_inventory(tp) ,
        "[for] / [about] [the] 'cost' [of] / [for] [the] %i", wep))
    {
        wep = NORMAL_ACCESS(wep, 0 , 0);
        if (sizeof(wep) > 1)
        {
            command("say Please be more specific! Which weapon do you mean?");
            return;
        }
        do_cost(wep[0], tp);
        return;
    }

    if (parse_command(question, all_inventory(tp) ,
        "[to] / [for] 'wax' / 'waxing' [of] / [for] [the] %i", wep))
    {
        wep = NORMAL_ACCESS(wep, 0 , 0);
        if (sizeof(wep) > 1)
        {
            command("say Please be more specific! Which weapon do you mean?");
            return;
        }
        do_fix(wep[0], tp, "wax");
        return;
    }

    if (parse_command(question, all_inventory(tp) ,
        "[to] / [for] 'sharpen' / 'sharpening' [of] / [for] [the] %i", wep))
    {
        wep = NORMAL_ACCESS(wep, 0 , 0);
        if (!sizeof(wep))
        {
            command("say You do not have such a weapon.");
            return;
        }
        if (sizeof(wep) > 1)
        {
            command("say Please be more specific! Which weapon do you mean?");
            return;
        }
        do_fix(wep[0], tp, "sharpen");
        return;
    }

    ::catch_question(question);

    return;
}

void
forge_weapon(string wep)
{
    command("emote finishes his work at forge and anvil.");
    command("emote puts a new "+wep+" on display onto the wall.");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects the player intend
 *		  to sell.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
int
shop_hook_allow_sell(object ob)
{
    return 0;
}

void
hook_sell_no_match(string str)
{
    command("say I don't buy anything!");
    command("say I just sell weapons.");
    command("say And if you wish I can wax and sharpen your weapons.");
}

/*
 * Function name: shop_hook_sell_no_match
 * Description:   Hook that is called when players tried to sell something
 *		  but we couldn't understand what he wanted to sell
 * Arguments:	  str - The string player tried to sell
 * Returns:	  0
 */
int
shop_hook_sell_no_match(string str)
{
    NF("@@hook_sell_no_match|"+str+"@@");
    return 0;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object further if you
 *		  allow it to be bought
 * Arguments:	  ob - The object player wants to buy.
 * Returns:	  1 if we allow it to be bought (default)
 */
int
shop_hook_allow_buy(object ob)
{
    return (MASTER_OB(ob) == MT_WEAPON);
}

int
hook_buy_no_match(string str)
{
    NF("");
    command("amazed "+TP->query_real_name());
    command("say But I don't have any "+str+" in stock!");
    return 0;
}

/*
 * Function name: shop_hook_buy_cant_pay
 * Description:   Called when player can't pay for what he wants to buy.
 *		  The /lib/trade.c sets some default error messages but
 *		  perhaps you are not happy with them?
 * Arguments:	  ob - The object
 *		  arr - The error code as it comes from trade.c
 */
void
shop_hook_buy_cant_pay(object ob, int *arr) {}

/*
 * Function name: smith_hook_value_store
 * Description:   Player values object in store
 * Arguments:     wtype - Type of weapon
 *		  text - The value in text form
 */
void
smith_hook_value_store(string wtype, string text)
{
    command("say The "+(MT_WEAPON->query_weapon_short(wtype))
      + " would cost you " + text + ".");
}

int
hook_value_no_match(string str)
{
    NF("");
    command("say I don't have any "+str+" in stock!");
    return 0;
}

mixed
neat_text(int *arr)
{
    int     i,
            num = sizeof(query_money_types());
    string  temp;

    if (sizeof(arr) < num) /* invalid array */
        return;

    temp = "";
    for (i = num - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
            temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
        else
            temp += "      ";
    }
    return temp;
}

/*
 * Function name: smith_hook_list_object
 * Description:   List an object
 * Arguments:	  wt - the weapon type
 */
void
smith_hook_list_object(string wt, int price)
{
    string  mess;

    mess = neat_text(split_values(price));
    if (!stringp(mess))
        mess = "That item wouldn't cost you much.\n";

    write(BSN(sprintf("%-35s %20s",
        CAP(wt), mess)));
}

/*    
 * Function name: query_weapon_price
 * Description:   What price should the player pay
 * Arguments:     wt - weapon type
 * Returns: 	  The price
 */
int
query_weapon_price(string wt)
{
    int seed,
        value;

    sscanf(OB_NUM(TP), "%d", seed);

    value = MT_WEAPON->query_price(wt);
    return 2 * value * (query_money_greed_buy() +
	15 - TP->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy an item
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    object  item;
    string str1, str2, str3;

    if (!str || str =="")
    {
	NF("Buy what?\n");
	return 0;
    }
 
    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    str1 = LOW(str1);
    if (member_array(str1, ENV(TO)->query_weapon_stock()) < 0)
        return hook_buy_no_match(str1);

    item = buy_weapon(str1, str2, str3);

    if (objectp(item))
    {
        ENV(TO)->remove_weapon(str1);
	return shop_hook_bought_items(({ item }));
    }

    return 0; /* Player tried to buy a non buyable object. */
}

/*
 * Function name: buy_weapon
 * Description:   Try to let the player buy the item array
 * Arguments:     wt - weapon type
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object
buy_weapon(string wt, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object  bought;
    mixed   tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);

    if (!shop_hook_allow_buy(find_object(MT_WEAPON)))
        return 0;

    price = query_weapon_price(wt);

    FIX_EUID
    bought = clone_object(MT_WEAPON);
    bought->set_weapon_type(wt);

    if (err = bought->move(TP))
    {
        shop_hook_buy_cant_carry(bought, err);
        return 0;
    }

    if (sizeof(arr = pay(price, TP, str2, 0, 0, str3)) == 1)
    {
        command("turn "+TP->query_real_name());
        command("say You can't afford to pay the price for the "+wt+"!");
        NF("");
        bought->remove_object();
        return 0;
    }

    /* Detect if there was a move error. */
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
        /* Couldn't take the money from player, the coins were stuck */
            shop_hook_buy_magic_money(bought);
            bought->remove_object();
            return 0;
        }
    }

    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];

    if (objectp(bought))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));

    return bought;
}

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num;

    if (!str || str =="")
    {
	NF("Value what?\n");
	return 0;
    }

    num = sizeof(query_money_types());

    str = LOW(str);

    if (member_array(str, ENV(TO)->query_weapon_stock()) < 0)
    {
	return hook_value_no_match(str);
    }

    price = query_weapon_price(str);

    arr = split_values(price); /* A price with few coins possible */
    smith_hook_value_store(str, text(arr));

    shop_hook_value_asking(str);

    return 1;
}

/*
 * Function name:   do_weapon_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments: 	    str - the name of the objects to search for
 */
varargs int
do_weapon_list(string str, int silent = 0)
{
    string *item_arr;
    int     i, price;

    item_arr = ENV(TO)->query_weapon_stock();

    if (!sizeof(item_arr))
    {
        command("say I'm sorry, but I'm sold out at present!");
        NF("");
	return 0;
    }

    if (!silent)
    {
        command("say Please look at the pricelist.");
        command("emote points at the pricelist.");
        write("On it you read:\n");
    }
    write("\n"
     + "    *** Herumegil, Master Weapon Smith of Minas Tirith ***\n\n"
     + "\t\tI sell the following weapons:\n\n");

    for (i = 0; i < sizeof(item_arr); i++)
    {
        price = query_weapon_price(item_arr[i]);
        smith_hook_list_object(item_arr[i], price);
    }

    write("\n    If you want a weapon sharpened or waxed, "
      + "ask me about it.\n\n");

    return 1;
}

public int
special_attack(object victim)
{
    object  wep = query_weapon(-1)[0];

    if (objectp(wep) && (MASTER_OB(wep) == MT_WEAPON))
        return 0;

    command("unwield all");

    if (!present("halberd", TO))
    {
        FIX_EUID
        wep = clone_object(MT_WEAPON);
        wep->set_weapon_type("halberd");
        wep->move(TO);
        command("emote gets a halberd from the weapons on the wall.");
    }
    command("wield halberd");
    return 1;
}

public void
stop_fight(mixed elist)
{
    ::stop_fight(elist);

    set_alarm(2.0, 0.0, unwield_weapon);
}

void
unwield_weapon()
{
    object  wep;

    if (objectp(query_attack()))
        return;

    command("unwield all");
    command("wield hammer");

    if (objectp(wep = present("halberd", TO)))
    {
        command("emote puts his weapon back on the wall.");
        wep->remove_object();
    }
}

void
delay_command(string com)
{
    set_alarm(rnd()*10.0 + 2.0, 0.0, "command", com);
}

public int
second_life(object killer)
{
    FIX_EUID
    M_TIRITH_MASTER->add_enemy(killer);
    return 1;
}

int
end_report()
{
    remove_alarm(report_alarm);
    report_alarm = 0;
    report_stage = 0;

    return 0;
}

int
report_dagger(object tp, object dagger, string seller)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
        return end_report();

    switch(report_stage++)
    {
        case 0:
            command("gasp");
            command("say But it is full of blood!");
            break;
        case 1:
            command("say Was it used in a crime?");
            command("ponder");
            break;
        case 2:
            command("say I sold that dagger about a month ago to a man living here in the city.");
            command("say The name was ... ");
            break;
        case 3:
            command("think");
            break;
        case 4:
            command("brighten");
            command("say Yes! Now I remember!");
            break;
        case 5:
            command("say The name is "+CAP(seller)+"!");
            break;
        case 6:
            command("say I hope this information will help you!");
            command("smile "+tp->query_real_name());
            break;
        default:
            return end_report();
            break;
    }

    return 1;
}

string
ask_dagger()
{
    int     ob_num;
    object  dagger,
            tp = TP;
    string  question = query_question(),
           *suspects;

    FIX_EUID

    // is the whodunnit quest active?
    MT_PW5_MASTER->load_me();
    if (!MT_PW5_MASTER->query_pw5_status())
        return default_answer();

    command("stop singing");

    // does the player have the dagger?
    if (!objectp(dagger = present(MT_PW5_MURDER_WEAPON, tp)))
    {
        command("say Which "+question+" are you talking about?");
        command("peer "+tp->query_real_name());
        return "";
    }

    command("say That is an excellent "+dagger->short()+" you have there.");
    command("smile");
    command("say I should know, I forged it.");

    // has the evidence been tampered with?
    if (!dagger->query_bloody())
        return "";

    // abort if the alarm is still active!
    if (report_alarm && sizeof(get_alarm(report_alarm)))
        return "";
    report_stage = 0;

    MT_PW5_SUSPECT->load_me();
    suspects = MT_PW5_SUSPECT->query_suspect_name(-1);
    suspects -= ({ MT_PW5_MASTER->query_murderer_name() });

    sscanf(OB_NUM(dagger), "%d", ob_num);
    report_alarm = set_alarm(2.0, 2.0, "report_dagger", tp, dagger,
        suspects[random(sizeof(suspects), ob_num)]);
//  report_alarm = set_alarm(2.0, 2.0, &report_dagger(tp, dagger, ONE_OF_LIST(suspects)));

    return "";
}

void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
        command("say Why, thank you!");
        command("say I always appreciate a little tip!");
        command("snicker");
        return;
    }

    command("say I don't think I need that.");
    to->catch_msg(QCTNAME(TO)+" gives the "+obj->short()+" back to you.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" gives "+LANG_ADDART(obj->short())+
        " to "+QTNAME(to)+".\n", to);
    if (obj->move(to))
       obj->move(to, 1);
}

void
return_dagger(object obj, object to)
{
    int     ob_num;
    string *suspects = ({});

    if (!(obj->id(MT_PW5_MURDER_WEAPON)))
    {
        return_object(obj, to);
        return;
    }

    command("emote inspects the "+obj->short()+".");
    command("say That is an excellent "+obj->short()+".");
    command("smile");
    command("say I should know, I forged it.");

    // has the evidence been tampered with?
    if (!obj->query_bloody())
    {
        return_object(obj, to);
        return;
    }

    // abort if the alarm is still active!
    if (report_alarm && sizeof(get_alarm(report_alarm)))
    {
        return_object(obj, to);
        return;
    }

    report_stage = 0;

    MT_PW5_SUSPECT->load_me();
    suspects = MT_PW5_SUSPECT->query_suspect_name(-1);
    suspects -= ({ MT_PW5_MASTER->query_murderer_name() });

    sscanf(OB_NUM(obj), "%d", ob_num);
    report_alarm = set_alarm(2.0, 2.0, &report_dagger(to, obj,
        suspects[random(sizeof(suspects), ob_num)]));

    set_alarm(20.0, 0.0, &return_object(obj, to));
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    // Is this the murder weapon?
    if (ob->id(MT_PW5_MURDER_WEAPON))
        set_alarm(0.5, 0.0, &return_dagger(ob, from));
    else
        set_alarm(0.5, 0.0, &return_object(ob, from));
}

public void
init_living()
{
    ::init_living();

    add_action(do_buy, "buy");
    add_action(do_value, "value");
    add_action(do_weapon_list, "list");
}

