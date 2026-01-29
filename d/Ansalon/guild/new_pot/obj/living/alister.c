/* Ashlar, 1 Oct 97
   a priest npc, this lad is the gardener
   he also acts as a herb shop, and will identify herbs for you if you
   give them to him
 */
 
 /* Navarre: March 2013 - Added Support to buy multiple herbs at a time.
  *                       Also fixed bugs with selling and buying.
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
#include "/d/Ansalon/guild/new_pot/guild.h"

inherit "/d/Ansalon/guild/new_pot/obj/living/npc";
inherit "/lib/trade";

#define HERB_STORE	"/d/Ansalon/taman_busuk/neraka/temple/dung1/herb_store"
#define NORMAL_PRICE    120
#define MAX_BUY 20 /* Maximum number of herbs you can buy */

void arm_me();
void herb_enter_inv(object obj, object from);
void init_herb_store();

string
query_guild_title_race()
{
    return "Wyllows of Flotsam";
}

int
query_guild_family_name()
{
    return 1;
}


void
create_pot_monster()
{
    if(!IS_CLONE)
	return;

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
    set_skill(SS_HERBALISM,         70);
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

void
init_living()
{
    ::init_living();
    init_herb_store();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    LOAD_ERR(HERB_STORE);

    ::arm_me();
}

string
hpick()
{
    if (!random(6))
    {
	    command("search here for herbs");
    }
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
    {
	    set_alarm(4.0, 0.0, &smell_flower(round + 1));
    }
}

void
give_back(object obj, object from)
{
    command("say That does not interest me.");
    command("drop " + obj->query_name());
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (living(from))
        if(obj->query_herb_value())
    {
	    set_alarm(0.0 + (itof(random(10)) / 5.0), 0.0,
                  &herb_enter_inv(obj, from));
    }
    else if(!obj->query_no_show())
    {
	    set_alarm(1.0, 0.0, &give_back(obj, from));
    }

}

/* Function name: is_allowed
 * Description:   Checks if this_player() is allowed 'what'
 * Arguments:     string what - either of listing, buying, selling or identifying
 * Returns:       int - 1/0, allowed or not
 */
int
is_allowed(string what)
{
    string *tmp;

    if ((tmp = GUILD_ADMIN->query_herbaccess(TP->query_real_name())) &&
        TP->query_guild_name_occ() == GUILD_NAME &&
        member_array(what, tmp) >= 0)
    {
        command("say to " + OB_NAME(TP) + " I have been told " +
            "not to allow you to do so.");
        return 0;
    }
    else if (what != "selling" && member_array(what, tmp) < 0 &&
        TP->query_guild_name_occ() != GUILD_NAME)
    {
        /* Every nonmember is allowed selling only by default */
        command("say to " + OB_NAME(TP) + " I only offer my services " +
                "to Her priests and a few selected others.");
        return 0;
    }
    return 1;
}

/**************************
 herbshop support functions
 **************************/

void
say_herb_id(object obj)
{
    string str;

    if (!obj->do_id_check(TO))
    {
	    command("say Nope, I haven't a clue what it is.");
    }
    else
    {
	    str = obj->query_id_long();
	    str = implode(explode(str,"\n")," ");
	    command("say " + str);
    }
}

void
herb_enter_inv(object obj, object from)
{
    string str;

    /* Sanity check, to see if the giver or the herb has mysteriously
       disappeared
     */

    if (!objectp(obj) || E(obj) != TO || !objectp(from) || E(from) != E(TO))
    {
	    command("scratch head");
        if (objectp(obj))
        {
	        obj->move(HERB_STORE);
        }
	    return;
    }

    if (is_allowed("identifying"))
    {
        say_herb_id(obj);
    }

    command("give " + obj->query_name() + " to " + from->query_real_name());
}

int
herb_compare(mapping hmap,string a, string b)
{
    if (hmap[b][0] < hmap[a][0])
    {
	    return 1;
    }
    else if (hmap[b][0] > hmap[a][0])
	{
        return -1;
    }
	return 0;
}

int
list_herbs(string arg)
{
    string *hl;
    int i,sz,price,count;
    mapping hmap;
    string t;

    if (arg && arg != "herbs")
    {
	    NF("List what?\n");
	    return 0;
    }

    if (!is_allowed("listing"))
    {
        return 1;
    }
    
    hmap = HERB_STORE->query_herb_list();
    hl = m_indexes(hmap);

    sz = sizeof(hl);
    if (sz == 0)
    {
	    write("There are no herbs for sale.\n");
	    return 1;
    }

    hl = sort_array(hl, &herb_compare(hmap,), this_object());

    t = "";
    for (i = 0; i < sz; i++)
    {
	    count = hmap[hl[i]][2];

        price = HERB_STORE->query_sell_price(hl[i]);
#ifdef 0
	    price = hmap[hl[i]][1];
	    price = (price * NORMAL_PRICE) / 100;
        price += (count > 1000 ? count / 3 : (count > 100 ? count / 5 : 0));
#endif

	    t += sprintf("%4d %-'.'23s %s\n", count, hmap[hl[i]][0],
                    (price <= 0 ? "0 copper coins" : 
	                 text( ({ price % 12, (price / 12) % 12,
	                (price / 144) % 12,
	                (price / 1728) % 12 }))));
    }

    this_player()->more(t, 0);
    return 1;
}

int
sell_herb(string arg)
{
    object *hlist;
    int *result, sum, x, size, err;

    hlist = FIND_STR_IN_OBJECT(arg, TP);
    
    // Since FIND_STR_IN_OBJECT doesn't find '10 cattail', but only
    // '10 cattails', we are going to try again with a plural version of the
    // argument if we didn't find anything on the first try.
    // If we always do plural we mess up herbs like 'angel tears', 
    if (!sizeof(hlist))
    {
        hlist = FIND_STR_IN_OBJECT(LANG_PWORD(arg), TP);
    }
    
    if (!find_object(HERB_STORE))
    {
        setuid();
        seteuid(getuid());
        
        HERB_STORE->load_me();
    }
   
    if (!sizeof(hlist))
    {
        notify_fail("Sell what?\n");
        return 0;
    }

    if (!is_allowed("selling"))
    {
        return 1;
    }
        
    if (this_player()->query_wiz_level())
    {
        dump_array(hlist);
    }   

    for (x = 0, sum = 0 ; x < sizeof(hlist) && x < 20 ; x++)
    {
        if (!objectp(hlist[x]))
        {
            hlist = exclude_array(hlist, x, x);
            x--;
            continue;
        }
        
        if (!IS_HERB_OBJECT(hlist[x]))
        {
            hlist = exclude_array(hlist, x, x);
            x--;
            continue;
        }
        
        if (member_array("_shire_herb_bundle", hlist[x]->query_names()) >= 0)
        {
            hlist = exclude_array(hlist, x, x);
            x--;
            continue;
        }

        if ((err = hlist[x]->move(HERB_STORE)))
        {
            if (err ==  7)
            {
                command("say Would you really expect me to have room for this many herbs!?");
            }
            else
            {
                write("Could not store " + hlist[x]->short() + ".\n");
            }
            hlist = exclude_array(hlist, x, x);
            x--;
            continue;
        }
        
        sum += HERB_STORE->query_buy_price(hlist[x]);
#ifdef 0
        hlist[x]->query_herb_value();
#endif
    }

    if (this_player()->query_wiz_level())
    {
        dump_array(hlist);
    }
        
    if (!sizeof(hlist))
    {
        write("You sold nothing.\n");
        return 1;
    }        

    result = give(sum, TP);
    
    tell_room(environment(this_object()),
              QCTNAME(TP) + " sells something to " + QTNAME(TO) + ".\n",
              TP);

    write("You sell " + COMPOSITE_DEAD(hlist) + ".\n");
    write(query_The_name(TP) + " gives you " + text(result[4..7]) + ".\n");

    return 1;
}

int
buy_herb(string arg)
{
    object herb;
    int price;
    int *result;
    int *tmp;
    string* words;
    int amount;
    
    if (!stringp(arg) || arg == "")
    {
	    NF("Buy what?\n");
	    return 0;
    }

    if (!is_allowed("buying"))
    {
        return 1;
    }
    
    arg = lower_case(arg);

    // If they type 'buy herbs' we just list what's available.
    if (arg == "herbs")
    {
        return list_herbs(arg);
    }
    words = explode(arg, " ");
    if (sizeof(words) > 1)
    {
        sscanf(words[0], "%d", amount);
        if (amount > 0)
        {
            arg = implode(words[1..sizeof(words)], " ");
        }
        else
        {
            amount = 1;
        }
    }
    else
    {
        amount = 1;
    }

    // Make sure we don't buy more than allowed per purchase.
    if (amount > MAX_BUY) 
    {
        command("say I am not allowed to sell more than 20 herbs at the time.");
        NF("");
        return 0;
    }
      
    herb = HERB_STORE->extract_several_herbs(LANG_SWORD(arg), amount);
    if (!herb)
    {
	    command("say I have no herb called '" + arg + "'.");
	    NF("");
        return 0;
    }

    price = HERB_STORE->query_sell_price(explode(herb->query_recover(), ":")[0]) * herb->num_heap();
    
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

    if (sizeof((result = pay(price, TP))) != 9)
    {
        herb->move(HERB_STORE);
        return 0;
    }
  
    tmp = result[4..7];

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
	    herb->move(E(TP));
	    write(query_The_name(TP) + " tries to give you the " +
	          herb->short() + ", but you cannot carry it, so he places " +
	          "it on the ground.\n");
    }
    else
    {
	    write(query_The_name(TP) + " gives you the " +
	          herb->short() + ".\n");
    }
    tell_room(E(TP),
              QCTNAME(TP) + " buys something from " + QTNAME(TO) + ".\n",
              TP);    	
    return 1;
}

int
show_herb(string arg)
{
    object herb;
    int price;
    int *result;
    int *tmp;

    if (!stringp(arg) || arg == "")
    {
	    NF("Show what?\n");
	    return 0;
    }

    herb = HERB_STORE->extract_herb(arg);
    if (!herb)
    {
	    command("say I have no herb called '" + arg + "'.");
        NF("");	  
        return 0;
    }
    say_herb_id(herb);
    herb->move(HERB_STORE);
    return 1;
}

void
init_herb_store()
{
    add_action(list_herbs,"list");
    add_action(sell_herb,"sell");
    add_action(buy_herb,"buy");
    add_action(show_herb,"show");
}
