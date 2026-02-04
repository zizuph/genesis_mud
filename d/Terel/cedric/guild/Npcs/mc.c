/* A merchant for the minstrel guild. Mortricia 8/93 */
// revisions: 

#pragma save_binary

inherit "/std/monster";
// inherit "/lib/trade";
inherit "/lib/shop";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <money.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <config.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

#define BSN(x)       (break_string(x, 77) + "\n")
#define MAXLIST      30
#define STORE_ROOM   TO()
#define NUM	     4
#define FORK_1_FILE    GUILDOBJ + "fork_brass"
#define FORK_2_FILE    GUILDOBJ + "fork_silver"
#define FORK_3_FILE    GUILDOBJ + "fork_gold"
#define FORK_4_FILE    GUILDOBJ + "fork_platinum"

#define TRADER_EQUIP  ({ FORK_1_FILE, FORK_2_FILE, FORK_3_FILE, FORK_4_FILE })

void fix_it(object instrument);
void introduce_me(object who);

public string figure_category(object ob);

public void set_standard_equip(mixed x);
public object *clone_and_buy_it(string str1, string str2, string str3);
public object clone_it(string str);
public int do_buy(string args);
public int do_list(string args);
public int do_show(string str);
static string *standard_equip;
string *sold_list = ({});

void
create_monster()
{
    if (!IS_CLONE) return;

    set_living_name("kyrsis");
    set_title("the Instrumentalist of the Muses");
    set_name("kyrsis");
    add_name("man");
    set_adj("small");
    add_adj("agile");
    set_race_name("human");

    set_long(
        "This is Kyrsis, an instrument maker whose talents are unsurpassed. "
       +"With the blessing of the Muses he is able to bring "
       +"life to even the most defiled instrument. Perhaps he can sell "
       +"you some of the tools o/f his trade, or <list> what he "
       +"has in stock.\n");
    default_config_npc(40);
    set_alignment(500);
    config_default_trade();
    // set_money_greed_buy(100);
    // set_money_give_reduce( ({ 0, 2, 3, 3 }) );

    set_cact_time(1);
    add_cact("say You keep fighting me and you'll be punished!");
    add_cact("say You don't get it, do you? Do you want to be kicked out "+
        "of the Minstrels?"); 
    add_cact("say My blood on your hands will get you banished from the "+
        "Mintrels!");
    add_cact("say I'm a minstrel, you fool! If you kill me you will be "+
        "banished from the palace forever.");
    add_cact("say Our Muses will punish you for this!");
 
    set_store_room("/d/Terel/guilds/minstrels/room/shop_storeroom");
    set_standard_equip(TRADER_EQUIP);

    trig_new("%s 'introduces' %s", "react_introduce");

    seq_new("foo");
    seq_addfirst("foo", ({ "@@do_give" }) );
}

/*
 * Function name: do_sell
 * Description:   Try to let the player sell the_item
 *                Observe there is no message written when sold item
 *                has a value higher than the shop gives out.
 * Returns:       1 on sucess
 * Arguments:     str - string holding name of item, hopefully
 */
int
do_sell(string str)
{
    notify_fail("Kyrsis isn't interested in buying anything from you.\n");
    return 0; 
}

/*
 * Function name: figure_category
 * Description:   Figure out which category ob belongs to
 * Arguments:     ob - the object to describe
 * Returns:       The category - weapon type, armour type or "General"
 */
 
public string
figure_category(object ob)
{
    int val;
    string short_descr;
//    if (ob->check_weapon())
    if (IS_WEAPON_OBJECT(ob))
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
        if(ob->function_exists("create_arrow", ob))
            return "Arrow";
//    if (ob->check_armour())
    if (IS_ARMOUR_OBJECT(ob))
    {
        switch(ob->query_at())
        {
            case A_ARMS: return "Arms";
            case A_L_ARM: return "Arms";
            case A_R_ARM: return "Arms";
            case W_LEFT: return "Arms";
            case W_RIGHT: return "Arms";
            case A_BACK: return "Back";
            case A_BODY: return "Torso";
            case A_TORSO: return "Torso";
            case A_FEET: return "Feet";
            case A_L_FOOT: return "Feet";
            case A_R_FOOT: return "Feet";
            case A_EARS: return "Ears";
            case A_L_EAR: return "Ears";
            case A_R_EAR: return "Ears";
            case A_FINGERS: return "Ring";
            case A_ANY_FINGER: return "Ring";
            case A_L_FINGER: return "Ring";
            case A_R_FINGER: return "Ring";
            case A_HANDS: return "Hands";
            case A_L_HAND: return "Hands";
            case A_R_HAND: return "Hands";
            case A_HEAD: return "Helmet";
            case A_LEGS: return "Legs";
            case A_NECK: return "Neck";
            case A_ROBE: return "Robe";
            case A_SHIELD: return "Shield";
            case A_SHOULDERS: "Shoulders"; 
            case A_L_SHOULDER: "Shoulders";
            case A_R_SHOULDER: "Shoulders";
            case A_WRISTS: return "Wrists";
            case A_L_WRIST: return "Wrists";
            case A_R_WRIST: return "Wrists";
            case A_WAIST: return "Waist";
            case A_L_HIP: return "Hips";
            case A_L_HIP: return "Hips";
            case A_L_ANKLE: return "Ankles";
            case A_R_ANKLE: return "Ankles";
        }
        return "Armour";
    }
    if(IS_HERB_OBJECT(ob))
        return "Herb";  
    if(IS_DRINK_OBJECT(ob))
        return "Drink";
    if(IS_FOOD_OBJECT(ob))
        return "Food";
    if(IS_COINS_OBJECT(ob))
        return "Money";
    if (ob->query_gem())
        return "Gem";
    return "General";
}

/*
 * Function name: shop_hook_list_object
 * Description:   List an object 
 * Arguments:	  ob - The object
 */
void
shop_hook_list_object(object ob, int price)
{
    string str, mess, categ;
    str = sprintf("%-41s", capitalize(LANG_ASHORT(ob)));
    categ = figure_category(ob);
    if (mess = text(split_values(price)))
    {
        mess = sprintf(" %-8s | %2d %2d %2d %2d", categ, price / 1728, (price % 1728) / 144, (price
% 144) / 12, price % 12);
        write("| " +str + "|" + mess + " |\n");
    }
    else
    {
	write(str + "That item wouldn't cost you much.\n");
    }
} 

public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = TRADER_EQUIP;
}

object
clone_it(string str)
{
    int n, s;
    object ob;
    string *s_arr,
        *adjs; 
    seteuid(getuid());
    s_arr = explode(str, " ");
    if ((s = sizeof(s_arr)) > 1)
        str = s_arr[s - 1];
    s_arr -= ({ str });
    --s;
    n = -1;
    while (++n < sizeof(standard_equip) && !objectp(ob))
    {
        if (standard_equip[n]->id(str))
        {
            adjs = standard_equip[n]->query_adjs();
            if (!s || (s == sizeof(adjs & s_arr)))
                ob = clone_object(standard_equip[n]);
        }
    }
    return ob;
} 

object *
clone_and_buy_it(string str1, string str2, string str3)
{
    int price, i, j, k, n,
        num = sizeof(query_money_types()),
        *value_arr = allocate(2 * num),
        *arr, error, err;
    object ob;
    if (!strlen(str1))
	return 0;
    ob = clone_it(str1);
    if (!objectp(ob))
    {
	return 0;
    }
    price = query_buy_price(ob);
  
    if (err = ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        ob->remove_object();
        return 0;
    }
  
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
        shop_hook_buy_cant_pay(ob, arr);
        ob->remove_object();
        return 0;
    }
  
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            /* Couldn't take the money from player, the coins were stuck */
            shop_hook_buy_magic_money(ob);
            ob->remove_object();
        }
        /* We don't want the money so no move error to us, if there was one
           it was because the player couldn't hold all coins, and if so the
           drop text is already written, but the deal is still on :) */
    }
  
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];
  
    if (objectp(ob))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
    return ({ ob });
}

public int
do_buy(string args) 
{
    int     res;
    object *item;
    string  str,
        str2,
        str3;
  
    if (!args || args == "")
    {
        notify_fail("The shopkeeper says: Buy what?\n");
        return 0;
    }
    if (sscanf(args,"%s for %s and get %s", str, str2, str3) != 3)
    {
        str3 = "";
	if (sscanf(args,"%s for %s", str, str2) != 2)
        {
	    str2 = "";
	    str = args; 
        }
    }
    if (res = ::do_buy(args))
        return res;
    else
    {
	item = clone_and_buy_it(str,str2,str3);
	if (sizeof(item))
            return shop_hook_bought_items(item);
        else
            return 0;
    }
    return 0;
}

public int
do_list(string args)
{
    string list_txt; 
    int n, s;
    object *oblist;

    write("This is the equipment Kyrsis has in stock:\n\n" +
    "+-------------------------------------------------------------------+\n"+
    "|                 Name                     | Category |  P  G  S  C |\n"+
    "+-------------------------------------------------------------------+\n");
     s = sizeof(standard_equip);

    if(!s)
        write("The fence has no goods to trade.\n\n");

    while (n < s) 
    {
        call_other(standard_equip[n], "load_me");
        shop_hook_list_object(find_object(standard_equip[n]),
        query_buy_price(find_object(standard_equip[n])));
        n++;
    }
    write("+-------------------------------------------------------------------+\n");
    return 1;
}
public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}
/*
 * Function name: do_show
 * Description  : Allow the player to appraise one of the objects in stock.
 * Returns      : int - 1/0 - true if success. 
 * Arguments    : string str - the name of the objects to search for.
 */
public int
do_show(string str)
{
    object ob;
    if (!str || str == "")
    {
        notify_fail("The shopkeeper says: Show what?\n");
        return 0;
    }
    if (::do_show(str))
	return 1;
    if (!objectp(ob = clone_it(str)))
	return 0;
    shop_hook_appraise_object(ob); 
    ob->appraise_object();
    ob->remove_object();
    return 1;
}


void
init_living()
{
    init_shop(); 

    add_action("do_repair", "assess");  
    add_action("do_repair", "repair");
    add_action("do_repair", "fix");
}

fork_filter(object ob)
{
    if (member_array("minstrel_tuning_fork", ob->query_names()) >= 0)
	return 1;
    return 0;
}

weapon_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/weapon");
}

armour_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/armour");
}

string_filter(object ob, string str)
{
    return ob->id(str);
}

int
do_repair(string str) 
{
    int testflag,cost,damage; 
    object instrument;
    mixed result;

    if (!str)
    {
	command("say What do you want me to "+query_verb()+"?");
	return 1;
    }

    if (query_verb()=="assess")
        testflag = 1;
    else
	testflag = 0;

    if (parse_command(str, TP(), "%o", instrument)
    && member_array("minstrel_instrument",instrument->query_names()) >= 0)
    {
    	damage = instrument->query_damage();
	if (damage < 1)
	{
	    NF(BS("Kyrsis looks the "+instrument->query_name()+" over with the "
	    + "trained eye of an expert, and says, \"I see nothing wrong with "
	    + "your instrument, friend.\"\n"));
	    instrument->set_damage(0);
	    return 0;
	}
	cost = damage * damage * damage;
	result = pay(cost, TP(), "", testflag, TO(), "", 0);
	if (intp(result))
	    switch (result)
	    {
		case 3: 
		    write("Kyrsis asks "+cost+" copper coins to repair your "
		    + "instrument.\n");
		    return 1;
		default:
		    write(BS("Kyrsis begins to take your money, then stops, "
		    + "confused. \"Odd!\" he exclaims. \"An error code "+result
		    + " kept me from taking your money. Better tell the "
		    + "guildmaster.\" Kyrsis shrugs and returns to his work.\n"));
		    return 1;
	    }
	if (testflag)
	{
	    write("Kyrsis asks "+text(result)+" to repair the "
	    + instrument->query_name()+".\n");
	    return 1;
	}
	else
	{
	    write("You pay "+text(result)+" to Kyrsis, who carefully "
	    + "looks your "+instrument->query_name()+" over.\n");
	    set_alarm(4.0, 0.0, &fix_it(instrument));
	    return 1;
	}
    }
    else
    {
	NF("Kyrsis glares at you and goes back to his work.\n");
        return 0;
    }
}

void fix_it(object instrument)
{
    switch (instrument->query_damage())
    {
	case 1..4: 
	    write(BS("Kyrsis remarks: Why, it's only out of tune! Don't you know "
	    + "how to tune your own "+instrument->query_name()+"?\"\n")+BS("He "
	    + "quickly tunes the instrument and hands it back to you.\n"));
	    break;
	case 5:
	    write(BS("Kyrsis seems amused. \"They don't get much more out of "
	    + "tune than this, do they?\" he laughs. He quickly tunes the "
	    + instrument->query_name()+" and hands it back to you.\n"));
	    break;
	case 6..10:
	    write(BS("Kyrsis takes the damaged instrument gingerly and "
	    + "places it on his workbench. Working quickly, but with great "
	    + "love and care, his deft fingers fly over the instrument. When "
	    + "he hands it back to you, the "+instrument->query_name()
	    + " looks as fine as the day "+environment(instrument)->
	    query_muse_name() + " first handed it into your care.\n"));
	    break;
    }
    instrument->set_damage(0);
}

void
react_introduce(string person, string who)
{
    object *obs;
    string name, dummy;

    if (sscanf(person, "Ghost of %s", dummy) == 1) {
        name = dummy;
    } else {
        name = person;
    }

    obs = FIND_STR_IN_OBJECT(lower_case(name), environment());
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return;
    if (!CAN_SEE(obs[0], TO())) return;
    set_alarm(4.0, 0.0, &introduce_me(obs[0]));
    return;
}

void introduce_me(object who)
{
    string name;

    if (!who || environment() != environment(who)) return;
    name = lower_case(who->query_name());

    if (MEMBER(who)) {
        command("introduce me to " + name);
        command("smile at " + name);
    } else {
	command("peer " + name);
    }

    return;
}


void attacked_by(object attacker)
{
   // Break the peace, forfeit your weapons.
    ::attacked_by(attacker);
   (GUILD+"office")->purge_tickets(attacker);
   command("say You've broken the peace! Whatever you checked in is forfeit now!");
}

public void
do_die(object killer)
{
 //   string logfile, *loglines;
 //   int i;
    
    seteuid(getuid());
    if (MEMBER(killer))
    {
	killer->CM("You deal the fatal blow, and stand triumphant over the "
	+ "fallen body of Kyrsis. Yet the victory seems curiously hollow, "
	+ "and your "+ present("minstrel_instrument", killer)->query_name() 
	+ " slips from your suddenly "
	+ "numb fingers. \n");
// removed by Lilith Apr 2022: too harsh a penelty
//        write_file(BANISHDIR+killer->query_real_name()+"_banished",
//		   "Banished forever from the Minstrels.\n");
//	killer->muse_banish();
	killer->muse_punish();
    }
    (GUILD+"office")->mc_died(killer);
    (GUILD+"tower_roof")->mc_died();
    ::do_die(killer);

}
