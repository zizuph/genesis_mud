#pragma strict_types
/*  Ashlar, 1 Oct 97
 *  a priest npc, this lad is the gardener
 *  he also acts as a herb shop, and will identify herbs for you if you
 *  give them to him
 *
 *  Revisions:
 *      Navarre, Mar 2013:  Added Support to buy multiple herbs at a time.
 *                          Also fixed bugs with selling and buying.
 *      Lucius, Aug 2016:   Fixed the herb identification.
 *      Lucius, Sep 2016:   Changed is_allowed to pass object to check.
 *                          Added is_allowed check to 'show' function.
 *                          Various code cleanups.
 *      Carnak, Dec 2016:   Fixed is_allowed to allow strangers to buy herbs if
 *                          allowed, and priests able of being prevented to.
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include <files.h>
#include <language.h>
#include <composite.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit "/d/Ansalon/guild/pot/obj/living/npc";
inherit "/lib/trade";

#define HERB_STORE	"/d/Ansalon/taman_busuk/neraka/temple/dung1/herb_store"
#define NORMAL_PRICE	120
/* Maximum number of herbs you can buy */
#define MAX_BUY		20


public void init_herb_store(void);
public void herb_enter_inv(object obj, object from);


public string
query_guild_title_race(void)
{
    return "Wyllows of Flotsam";
}

public int
query_guild_family_name(void)
{
    return 1;
}


public void
create_pot_monster(void)
{
    if(!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());
        
    set_name("alister");
    set_living_name("alister");
    set_title("Master of the Gardens");
    add_name("priest");
    add_name("gardener");
    add_name("master");

    set_introduce(1);

    set_race_name("half-elf");
    set_adj("tall");
    add_adj("bald-headed");
    set_long("This is the Master of the Gardens, the overseer of the " +
      "plants in these caverns. His long coat is discoloured by plant " +
      "stains and his hands are also stained. He trades in herbs, and " +
      "you can use the commands buy, sell, show and list to trade with him.\n");

    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 75000);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, "You sense a dark power protecting "+
        "this one, and find yourself unable to attack.\n");

    set_stats(({ 114, 135, 110, 150, 140, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           55);
    set_skill(SS_PARRY,             50);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);
    set_skill(SS_HERBALISM,         90);
    set_skill(SS_ALCHEMY,           70);

    set_skill(PS_GUILD_LEVEL, 45);
    set_skill(PS_SPELLS, PTELL_ID);

    set_all_hitloc_unarmed(10);

    set_alignment(-900);
    set_knight_prestige(900);

    set_act_time(7);
    add_act("say I know what is worth to know about the plants that " +
      "we grow down here.");
    add_act(VBFC_ME("pick_flower"));
    add_act(VBFC_ME("smell_flower"));
    add_act("emote uproots some weeds from the garden.");
    add_act("smile .");
    add_act(VBFC_ME("hpick"));

    set_cact_time(5);
    add_cact("say I curse you!");
    add_cact("sneer");
    add_cact("say The hatred of the Dark Queen will follow you to your grave!");

    set_default_answer(QCTNAME(TO) + " mutters: I can not help you with " +
      "that.\n");

    add_ask(" [for] 'help' ", "say I might be able to help you, " +
      "if you have come to seek training in the art of the herbs.", 1);
    add_ask(" [about] [the] [art] [of] [the] 'art' / 'herbs' ",
      "say I may be able to train you in herbalism.", 1);
    add_ask(" [about] 'herbalism' ",
      "say O, mickle is the powerful grace, that lies in herbs, plants, " +
      "stones, and their true qualities.", 1);

    config_default_trade();

    /* So people can do sell all and still get full payment.
     * Saves a few cpu cycles 
     */
    set_money_give_max(999999);
    set_money_give_out(({10000, 2000, 200, 10}));
}

public void
init_living(void)
{
    ::init_living();
    init_herb_store();
}

public void
arm_me(void)
{
    LOAD_ERR(HERB_STORE);
    ::arm_me();
}

string
hpick()
{
    if (!random(6))
	command("search here for herbs");
}

varargs string
pick_flower(int round)
{
    switch(round)
    {
        case 0:
	        command("emote picks a small flower and studies it intently.");
	        break;

        case 1:
	        command("say Within the infant rind of this small flower");
	        break;

        case 2:
	        command("say Poison has residence, and medicine power");
	        break;
    }

    if (round < 2)
    {
	    set_alarm(5.0, 0.0, &pick_flower(round + 1));
    }
}

varargs string
smell_flower(int round)
{
    switch(round)
    {
        case 0:
	        command("emote deeply inhales the scent of a purple flower.");
	        break;

        case 1:
	        command("emote sneezes violently.");
	        break;
    }

    if (round < 1)
	set_alarm(4.0, 0.0, &smell_flower(round + 1));
}

public void
give_back(object obj, object from)
{
    command("say That does not interest me.");
    command("drop " + OB_NAME(obj));
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (IS_HERB_OBJECT(obj))
    {
	set_alarm(0.0 + (itof(random(10)) / 5.0), 0.0,
	    &herb_enter_inv(obj, from));
    }
    else if (!obj->query_no_show())
    {
	set_alarm(1.0, 0.0, &give_back(obj, from));
    }
}

/* Function name: is_allowed
 * Description:   Checks if this_player() is allowed 'what'
 * Arguments:     string what - either of listing, buying, selling or identifying
 * 		  object who  - who to check against.
 * Returns:       int - 1/0, allowed or not
 */
public int
is_allowed(string what, object who)
{
    string *tmp = GUILD_ADMIN->query_herbaccess(who->query_real_name());
    
    /* Everyone is allowed to sell herbs by default. */
    if (what == "selling")
        return 1;

    if (who->query_guild_name_occ() != GUILD_NAME ||
        !who->query_priest_level())
    {
        if (pointerp(tmp) && member_array(what, tmp) > -1)
            return 1;
        
        command("say to " + OB_NAME(TP) + " I only offer my services " +
                "to Her priests and a few selected others.");
        return 0;
    }
    
    if (member_array(what, tmp) > -1)
    {
            command("psay to " + OB_NAME(who) + " I have been told " +
                    "not to allow you to do so.");
            return 0;
    }

    return 1;
}

/**************************
 herbshop support functions
 **************************/

public void
say_herb_id(object obj)
{
    if (!obj->do_id_check(TO))
    {
	command("say Nope, I haven't a clue what it is.");
    }
    else
    {
	string str = obj->query_id_long();
	str = implode(explode(str, "\n"), " ");
	command("say " + str);
    }
}

public void
herb_enter_inv(object obj, object from)
{
    /* Sanity check, to see if the giver or the herb has mysteriously
       disappeared
     */
    if (!objectp(obj) || E(obj) != TO || !objectp(from) || E(from) != E(TO))
    {
	command("scratch head");
	obj->move(HERB_STORE);
	return;
    }

    if (is_allowed("identifying", from))
        say_herb_id(obj);

    command("give " + OB_NAME(obj) + " to " + OB_NAME(from));
}

public int
herb_compare(mapping hmap, string a, string b)
{
    if (hmap[b][0] < hmap[a][0])
	return 1;
    else if (hmap[b][0] > hmap[a][0])
	return -1;

    return 0;
}

public int
list_herbs(string arg)
{
    if (arg != "herbs")
    {
	NF("List what?\n");
	return 0;
    }

    if (!is_allowed("listing", TP))
        return 1;
    
    mapping hmap = HERB_STORE->query_herb_list();
    string *hlist = m_indexes(hmap);

    int sz = sizeof(hlist);
    if (sz == 0)
    {
	command("say I have no herbs for sale.");
	return 1;
    }

    arg = "The following herbs are available:\n\n";
    hlist = sort_array(hlist, &herb_compare(hmap,));

    foreach(string h: hlist)
    {
	int count = hmap[h][2];
	int price = HERB_STORE->query_sell_price(h);

#ifdef 0
	price = hmap[h][1];
	price = (price * NORMAL_PRICE) / 100;
        price += (count > 1000 ? count / 3 : (count > 100 ? count / 5 : 0));
#endif

	arg += sprintf("%5d %-'.'23s%s\n", count, hmap[h][0],
	    (price <= 0 ? "0 copper coins" :
		text( ({ price % 12, (price / 12) % 12,
		    (price / 144) % 12, (price / 1728) % 12 }) )));
    }

    this_player()->more(arg, 0);
    return 1;
}

public int
sell_herb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Sell what?\n");
        return 0;
    }

    object *hlist = FIND_STR_IN_OBJECT(arg, TP);
    
    // Since FIND_STR_IN_OBJECT doesn't find '10 cattail', but only
    // '10 cattails', we are going to try again with a plural version of the
    // argument if we didn't find anything on the first try.
    // If we always do plural we mess up herbs like 'angel tears', 
    if (!sizeof(hlist))
        hlist = FIND_STR_IN_OBJECT(LANG_PWORD(arg), TP);
    
    if (!sizeof(hlist))
        return 0;

    if (!is_allowed("selling", TP))
        return 1;
        
    if (this_player()->query_wiz_level())
        dump_array(hlist, "PRE: ");

    if (!find_object(HERB_STORE))
        HERB_STORE->load_me();
   
    int cnt, err, sum;

    foreach(object ob: hlist)
    {
	if (!IS_HERB_OBJECT(ob) || ob->id("_shire_herb_bundle"))
        {
            hlist -= ({ ob });
            continue;
        }
        
        if (err = ob->move(HERB_STORE))
        {
	    if (err ==  7)
	    {
                command("say Would you really expect me to have room "+
		    "for this many herbs!?");
	    }
            else
            {
		command("say I don't seem to be able to store "+
		    ob->short() +".");
            }
            hlist -= ({ ob });
            continue;
        }
        
	cnt++;
        sum += HERB_STORE->query_buy_price(ob);
    }

    if (this_player()->query_wiz_level())
        dump_array(hlist, "POST: ");
        
    if (!sizeof(hlist))
    {
	command("say You didn't have anything to sell it seems.");
        return 1;
    }        

    int *result = give(sum, TP);
    
    write("You sell " + COMPOSITE_DEAD(hlist) + ".\n");
    write(query_The_name(TP) + " gives you " + text(result[4..7]) + ".\n");

    tell_room(environment(this_object()),
	QCTNAME(TP) + " sells something to " + QTNAME(TO) + ".\n", TP);

    return 1;
}

public int
buy_herb(string arg)
{
    if (!strlen(arg))
    {
	NF("Buy what?\n");
	return 0;
    }

    if (!is_allowed("buying", TP))
        return 1;
    
    arg = lower_case(arg);

    // If they type 'buy herbs' we just list what's available.
    if (arg == "herbs")
	return list_herbs(arg);

    int amount = 0;
    string *words = explode(arg, " ");

    if (sizeof(words) > 1)
    {
        sscanf(words[0], "%d", amount);
        if (amount > 0)
            arg = implode(words[1..sizeof(words)], " ");
        else
            amount = 1;
    }
    else
    {
        amount = 1;
    }

    // Make sure we don't buy more than allowed per purchase.
    if (amount > MAX_BUY) 
    {
        command("say I am not allowed to sell more than "+
	    MAX_BUY +" herbs at the time.");
        return 1;
    }
      
    object herb = HERB_STORE->extract_several_herbs(LANG_SWORD(arg), amount);
    if (!herb)
    {
	command("say I have no herb called '" + arg + "'.");
	return 1;
    }

    int price = HERB_STORE->query_sell_price(MASTER_OB(herb));
    price *= herb->num_heap();
    
#ifdef 0
    price = herb->query_herb_value();
    price = (price * NORMAL_PRICE) / 100;
#endif

#ifdef 0
    if (!can_pay(price, TP))
    {
	command("say You can't afford it.");
	herb->move(HERB_STORE);
	return 1;
    }
#endif

    int *result = pay(price, TP);
    if (sizeof(result) != 9)
    {
        herb->move(HERB_STORE);
        return 0;
    }
  
    int *tmp = result[4..7];

    if (tmp[0])
    {
	write("You pay " + text(result[0..3]) + " and recieve " +
	    text(tmp) + " in change.\n");
    }
    else
    {
	write("You pay " + text(result[0..3]) + ".\n");
    }

    if (herb->move(TP))
    {
	herb->move(environment(TP));
	write(query_The_name(TP) + " tries to give you the " +
	    herb->short() + ", but you cannot carry it, so he places " +
	    "it on the ground.\n");
    }
    else
    {
	write(query_The_name(TP) + " gives you the " +
	    herb->short() + ".\n");
    }

    tell_room(environment(TP), QCTNAME(TP) + " buys something from " +
	QTNAME(TO) + ".\n", TP);    	

    return 1;
}

public int
show_herb(string arg)
{
    object herb;

    if (!strlen(arg))
    {
	NF("Show what?\n");
	return 0;
    }

    if (!is_allowed("identifying", TP))
	return 0;

    if (!objectp(herb = HERB_STORE->extract_herb(arg)))
    {
	command("say I have no herb called '" + arg + "'.");
        return 0;
    }

    say_herb_id(herb);
    herb->move(HERB_STORE);
    return 1;
}

public void
init_herb_store(void)
{
    add_action(list_herbs,"list");
    add_action(show_herb,"show");
    add_action(sell_herb,"sell");
    add_action(buy_herb,"buy");
}
