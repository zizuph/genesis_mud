/* /d/Faerun/guilds/fire_knives/npc/smithy/
 * 
 * Nerull 2018
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
inherit "/lib/shop";

#include <cmdparse.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include "../guild.h";

#define FIREKNIVES_WEAPON   (FIREKNIVES_GUILD_DIR + "obj/fireknives_weapon")
#define TO this_object()
#define TP this_player()

#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */

#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })

#define DEBUG 1


/*
 *      Prototypes:
 */
int     calc_sharpen_value(object obj);
int     calc_wax_value(object obj);
int     distort(int price);
object  buy_weapon(string wt, string str2, string str3);
public string  default_answer();


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    set_name("bjarn");
    add_name("smithy");
	add_name("crafter");
    add_name("man");

    add_adj("sweaty");
    add_adj("bald");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    
    set_short("sweaty bald man");
    
    set_long("This is Bjarn, a sweaty bald blacksmith. He has "
    +"seen better days judging by frail his skin and white "
    +"mustache. Muscles have dwindled during the years as "
    +"his age is failing him, but he is still hammering the "
    +"anvil making steel sing with every blow. Bjarn offer "
    +"various services to the member of the outfit: selling, "
    +"waxing and repairing weapons.\n");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 170);

    set_stats(({ 110, 110, 120,
                 243, 320, 280 }));

    set_hitloc_unarmed(A_HEAD, 25, 15, "stone head");
    set_hitloc_unarmed(A_R_ARM, 25, 10, "right stone arm");
    set_hitloc_unarmed(A_L_ARM, 25, 10, "left stone arm");
    set_hitloc_unarmed(A_BODY, 25, 45, "stone body");
    set_hitloc_unarmed(A_LEGS, 25, 20, "stone legs");

    set_attack_unarmed(W_LEFT,  55, 55, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  55, 55, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    
    set_appearance(-1000);
    
    config_default_trade();
    set_money_give_max(1000);
    set_money_greed_sell(100);

    set_default_answer(
    QCTNAME(TO) + " says: To see what I sell, <check> at my table!\n" +
    QCTNAME(TO) + " says: I can also sharpen and wax your weapons.\n" +
    QCTNAME(TO) + " says: If you want to know the price of "
    +"my service, ask me for the cost!\n");
	
	add_ask( ({ "crafting" }),
    "say To craft a weapon is both a science and an art.", 1);
	
	add_ask( ({ "smith", "blacksmith", "weaponsmith" }),
    "say Such a name. I prefer 'crafter'.", 1);
	
	add_ask( ({ "weapon", "weapons" }),
    "say I work with weapons: making and treating them.", 1);
	
	add_ask( ({ "armour", "armours" }),
    "say Armours aren't really a priority for me. I focus on the "
	+"tools to kill, not to survive.", 1);
	
	add_ask( ({ "tool", "tools" }),
    "say The craft I have mastered requires a plethora of "
	+"tools. All a science in themselves.", 1);
}


static string
default_answer()
{
    command("say To see what I sell, please <check> my table!");
    command("say I can also sharpen and wax your weapons.");
    command("say If you want to know the price of my service,");
    command("say ask me for the cost!");

    return "";
}


static void
answer_weapon()
{
    command("say I fabricate daggers and knives in all shapes and forms.");
    command("say Please <check> the table to see "
      + "what is in stock.");
}


static int
do_cost(object weapon, object tp)
{
    int     v1,
            v2;
    string  it,
            what = "";

    if (function_exists("create_object", weapon) != WEAPON_OBJECT)
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
        command("say "+capitalize(it)+" needs neither "
    +"sharpening nor waxing!");
    else
        command("say If you want me to "
    +what+" the weapon, ask me to do so.");

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
    
    if (function_exists("create_object", weapon) != WEAPON_OBJECT)
    {
        command("say That "+weapon->short()+" is no weapon!");
        return 0;
    }
    
    /* Talk about tricky code! ;-) */
    value = call_other(TO, "calc_"+verb+"_value", weapon);

    if (value == -1)
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

    tp->catch_msg("You give the " + weapon->short() + " to " 
    + QTNAME(TO) + ".\n");
    
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


#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))


public int
distort(int price)
{
    int trading = TP->query_skill(SS_TRADING);

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


    question = LOW(question);

    switch (question)
    {
    case "cost":
        command("peer "+tp->query_real_name());
        command("say The cost for which weapon?");
        break;
    case "sharpen":
        command("peer "+tp->query_real_name());
        command("say Sharpen which weapon?");
        break;
    case "wax":
        command("peer "+tp->query_real_name());
        command("say Wax which weapon?");
        break;
    case "weapon":
    case "weapons":
    case "manufacture":
        answer_weapon();
        break;
    default:
        if (parse_command(question, all_inventory(tp) ,
            "[for] / [about] [the] 'cost' [of] / [for] [the] %i", wep))
        {
            wep = NORMAL_ACCESS(wep, 0 , 0);
            if (sizeof(wep) > 1)
            {
                command("say Please be more specific! Which "
                +"weapon do you mean?");
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
                command("say Please be more specific! Which "
                +"weapon do you mean?");
                return;
            }
            do_fix(wep[0], tp, "wax");
            return;
        }

        if (parse_command(question, all_inventory(tp) ,
            "[to] / [for] 'sharpen' / 'sharpening' [of] / [for] [the] %i", 
            wep))
        {
            wep = NORMAL_ACCESS(wep, 0 , 0);
            if (!sizeof(wep))
            {
                command("say You do not have such a weapon.");
                return;
            }
            if (sizeof(wep) > 1)
            {
                command("say Please be more specific! Which "
                +"weapon do you mean?");
                return;
            }
            do_fix(wep[0], tp, "sharpen");
            return;
        }

        ::catch_question(question);
    }

    return;
}


static void
forge_weapon(string wep)
{
    command("emote finishes his work at forge and anvil.");
    command("emote puts a new "+wep+" on the table.");
}


/*
 * Function name: shop_hook_allow_sell
 * Description:   If you want to do more testing on objects the player intend
 *        to sell.
 * Argument:      ob - The object player wants to sell
 * Returns:   1 if we allow player to sell the object (default)
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
    command("say I just sell daggers and knives.");
    command("say And if you wish I can wax and sharpen your weapons.");
}


/*
 * Function name: shop_hook_sell_no_match
 * Description:   Hook that is called when players tried to sell something
 *        but we couldn't understand what he wanted to sell
 * Arguments:     str - The string player tried to sell
 * Returns:   0
 */
int
shop_hook_sell_no_match(string str)
{
    notify_fail("@@hook_sell_no_match|"+str+"@@");
    return 0;
}


/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object further if you
 *        allow it to be bought
 * Arguments:     ob - The object player wants to buy.
 * Returns:   1 if we allow it to be bought (default)
 */
int
shop_hook_allow_buy(object ob)
{
    return (MASTER_OB(ob) == FIREKNIVES_WEAPON);
}


int
hook_buy_no_match(string str)
{
    notify_fail("");
    command("amazed "+TP->query_real_name());
    command("say But I don't have any "+str+" in stock!");
    return 0;
}


/*
 * Function name: shop_hook_buy_cant_pay
 * Description:   Called when player can't pay for what he wants to buy.
 *        The /lib/trade.c sets some default error messages but
 *        perhaps you are not happy with them?
 * Arguments:     ob - The object
 *        arr - The error code as it comes from trade.c
 */
void
shop_hook_buy_cant_pay(object ob, int *arr) {}


/*
 * Function name: smith_hook_value_store
 * Description:   Player values object in store
 * Arguments:     wtype - Type of weapon
 *        text - The value in text form
 */
void
smith_hook_value_store(string wtype, string text)
{
    command("say The "+(FIREKNIVES_WEAPON->query_weapon_short(wtype))
      + " would cost you " + text + ".");
}


int
hook_value_no_match(string str)
{
    notify_fail("");
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
 * Arguments:     wt - the weapon type
 */
void
smith_hook_list_object(string wt, int price)
{
    string  mess;

    mess = neat_text(split_values(price));
    if (!stringp(mess))
        mess = "That item wouldn't cost you much.\n";

    write(BSN(sprintf("%-35s %20s",
        capitalize(wt), mess)));
}


/*    
 * Function name: query_weapon_price
 * Description:   What price should the player pay
 * Arguments:     wt - weapon type
 * Returns:       The price
 */
int
query_weapon_price(string wt)
{
    int seed,
        value;

    sscanf(OB_NUM(TP), "%d", seed);

    value = FIREKNIVES_WEAPON->query_price(wt);
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
    notify_fail("Buy what?\n");
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
    if (member_array(str1, environment(TO)->query_weapon_stock()) < 0)
        return hook_buy_no_match(str1);

    item = buy_weapon(str1, str2, str3);

    if (objectp(item))
    {
        environment(TO)->remove_weapon(str1);
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

    if (!shop_hook_allow_buy(find_object(FIREKNIVES_WEAPON)))
        return 0;

    price = query_weapon_price(wt);

    bought = clone_object(FIREKNIVES_WEAPON);
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
        notify_fail("");
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
    notify_fail("Value what?\n");
    return 0;
    }

    num = sizeof(query_money_types());

    str = LOW(str);

    if (member_array(str, environment(TO)->query_weapon_stock()) < 0)
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
 * Arguments:       str - the name of the objects to search for
 */
varargs int
do_weapon_list(string str, int silent = 0)
{
    string *item_arr;
    int     i, price;

    item_arr = environment(TO)->query_weapon_stock();

    if (!sizeof(item_arr))
    {
        command("say I'm sorry, but I'm sold out at present!");
        notify_fail("");
    return 0;
    }

    /*if (!silent)
    {
        command("say Look at the pricelist.");
        command("emote points at the pricelist.");
        write("On it you read:\n");
    }*/
    write("\n"
     //+ "    *** Bjarn, Weapon Smith of the Fire Knives ***\n\n"
     + "\t\tOn the table, you see following weapons for sale:\n\n");

    for (i = 0; i < sizeof(item_arr); i++)
    {
        price = query_weapon_price(item_arr[i]);
        smith_hook_list_object(item_arr[i], price);
    }

    write("\n    If you want a weapon sharpened or waxed, "
      + "ask Bjarn about it.\n\n");

    return 1;
}


void
delay_command(string com)
{
    set_alarm(rnd()*10.0 + 2.0, 0.0, &command(com));
}


void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
        command("say Why, thank you!");
        command("say I always appreciate a little tip!");
        command("smile greed");
        return;
    }

    command("say I don't think I need that.");
    to->catch_msg(QCTNAME(TO)+" gives the "+obj->short()+" back to you.\n");
    tell_room(environment(TO), QCTNAME(TO)+" gives "
    +LANG_ADDART(obj->short())
    +" to "+QTNAME(to)+".\n", to);
    
    if (obj->move(to))
       obj->move(to, 1);
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(ob, from));
}


public void
init_living()
{
    ::init_living();

    add_action(do_buy,         "buy");
    add_action(do_value,       "value");
    add_action(do_weapon_list, "check");
}


public void
add_introduced(string name)
{
    object  who;

    if (!objectp(who = find_player(name)))
        return;

    if (who->query_met(query_name()))
        return;
    set_alarm(2.0 + 5.0 * rnd(), 0.0, &command("present me to " +
        name));
}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch (emote)
    {
    case "hail":
        add_introduced(TP->query_real_name());
        break;
    default:
        break;
    }
}

