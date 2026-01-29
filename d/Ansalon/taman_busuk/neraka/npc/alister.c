/* Ashlar, 1 Oct 97
   a priest npc, this lad is the gardener
   he also acts as a herb shop, and will identify herbs for you if you
   give them to him
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
#include "../local.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit AM_FILE
inherit "/lib/trade";

#define HERB_STORE	"/d/Ansalon/taman_busuk/neraka/temple/herb_store"

#undef DEBUG
#define DEBUG(x)    (find_player("milan")->catch_msg("PRIEST: " + x + "\n"))

#define NORMAL_PRICE    120

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
create_krynn_monster()
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
    set_skill(PS_SPELLS, -1);

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
    set_money_greed_sell(125);
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

    clone_object(POTSHADOW)->add_occ_shadow(TO);

    TO->init_occ_shadow();

    LOAD_ERR(HERB_STORE);
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
	set_alarm(5.0,0.0,&pick_flower(round+1));
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
	set_alarm(4.0,0.0,&smell_flower(round+1));
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
	if(function_exists("create_object",obj) == "/std/herb")
	    set_alarm(0.0+(itof(random(10))/5.0),0.0,&herb_enter_inv(obj,from));
	else if(!obj->query_no_show())
	    set_alarm(1.0,0.0,&give_back(obj,from));

}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Alister",killer);
    return 0;
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
	obj->move(HERB_STORE);
	return;
    }

    say_herb_id(obj);

    command("give " + obj->query_name() + " to " + from->query_real_name());
}

int
herb_compare(mapping hmap,string a, string b)
{
    if (hmap[b][0] < hmap[a][0])
	return 1;
    else if (hmap[b][0] > hmap[a][0])
	return -1;
    else
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
	count = sizeof(hmap[hl[i]]) - 2;

	price = hmap[hl[i]][1];
	price = (price * NORMAL_PRICE) / 100;

	t += sprintf("%2d %-'.'23s %s\n", count, hmap[hl[i]][0],
	  text( ({ price % 12, (price / 12) % 12,
	      (price / 144) % 12,
	      (price / 1728) % 12 })
	  ) );
    }

    this_player()->more(t, 0);

    return 1;
}

int
sell_herb(string arg)
{
    object *hlist;
    int *result, sum, x, size;

    hlist = FIND_STR_IN_OBJECT(arg,TP);

    if (!sizeof(hlist))
    {
        notify_fail("Sell what?\n");
        return 0;
    }

    for (x = 0, sum = 0, size = sizeof(hlist) ; x < size && x < 20 ; x++)
    {
        if (!objectp(hlist[x]) ||
            !IS_HERB_OBJECT(hlist[x]))
	{
            hlist = exclude_array(hlist, x, x);
	}
        
        if (hlist[x]->move(HERB_STORE))
        {
            write("Could not store " + hlist[x]->short() + ".\n");
            hlist = exclude_array(hlist, x, x);
        }
        
        sum += hlist[x]->query_herb_value();
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

    if (!stringp(arg) || arg == "")
    {
	NF("Buy what?\n");
	return 0;
    }

    herb = HERB_STORE->extract_herb(arg);
    if (!herb)
    {
	NF("I have no herb called '" + arg + "'.\n");
	return 0;
    }

    if (!TP->query_pot_member())
    {
        command("say to "+OB_NAME(TP)+
            " These herbs are only for Her priests.");
        herb->move(HERB_STORE);
        return 1;
    }

    price = herb->query_herb_value();
    price = (price * NORMAL_PRICE) / 100;

    if (!can_pay(price, TP))
    {
	command("say You can't afford it.");
	herb->move(HERB_STORE);
	return 1;
    }

    result = pay(price, TP);

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
	NF("I have no herb called '" + arg + "'.\n");
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
