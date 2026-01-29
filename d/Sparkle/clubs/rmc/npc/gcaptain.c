/*
 * RMC ship captain
 *
 * Updated so the captain can't be attacked until further notice.
 * TAPAKAH, 17/06/2005
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";
 
#include "defs.h"
#include "/sys/filter_funs.h"

#include <ss_types.h>
#include <money.h>
 
object ship;
int has_introduced=0;

void
set_ship(object s)
{
    ship = s;
}
 
void
create_monster()
{
    set_name("kroesus");
    add_name("captain");
    set_living_name("kroesus");
    set_race_name("human");

    set_title("The Obscenely Wealthy Member of The Rich Men's Club");

    set_adj("greedy");
    add_adj("rich");
    set_stats(({ 350, 450, 450, 200, 200, 250 }));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(OBJ_M_NO_ATTACK,1);
    set_exp_factor(50);
    refresh_mobile();
    has_introduced = 0;
    config_default_trade();
 
}
 
void
init_living()
{
    add_action("buy", "buy");
}
 
int
buy(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int    *result, m_res, price;
    
    if (!str) 
    {
	NF("Buy what?\n");
    }
    
    if (environment() == find_object(RMCSHIP+"gdeck"))
    {
	NF("You're already on board, you don't need another ticket.\n");
	return 0;
    }
    
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    
    if (what != "ticket")
    {
		NF("I have no such thing for sale.\n");
		return 0;
    }
    
    buy_ob=clone_object(RMCOBJ+"gticket.c");
    
    if (!buy_ob)
    {
		NF("I seem to be out of tickets.\n");
		return 0;
    }
    
    if(!(RMCMASTER)->query_member(TP->query_real_name()))
    {
	price = buy_ob->query_prop(OBJ_I_VALUE);
	result = pay(price, TP, for_c, 0, 0, get_c);
	
	command("rgreet " + TP->query_real_name());
	command("rsmile2");
	command("say Money counts.");
	
	if (sizeof(result)==1)
	{
	    buy_ob->remove_object();
	    return 0;
	}
	
	if (buy_ob->move(TP))
	{
	    write("You drop the " + buy_ob->short() + " on the ground.\n");
	    say(QCTNAME(TP) + " drops one " + buy_ob->short() +
		" on the ground.\n");
	    buy_ob->move(environment(TP));
	}
	else
	{
	    write("You get your " + buy_ob->short() + ".\n");
	    say(QCTNAME(TP) + " buys a " + buy_ob->short() + ".\n");
	}
	write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
	
	if (change)
	    write("You get " + change + " as change.\n");
	
	return 1;
    }
    
    if (buy_ob->move(TP))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(TP) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(environment(TP));
    }
    command("bow " + TP->query_real_name());
    command("rsmile2");
    command("say Money counts.\n");
    
    write("You get your " + buy_ob->short() + " for free since you're a member "+
	  "of The Rich Men's Club.\n");
    say(QCTNAME(TP) + " gets a " + buy_ob->short() + " for free.\n");
    return 1; 
}
 
void
add_introduced(string person)
{
    if (!has_introduced)
    {
	set_alarm(2.0, 0.0, "introduce_me");
	has_introduced = 1;
	set_alarm(12.0, 0.0, "remove_int");
    }
}
 
void
introduce_me()
{
    command("introduce myself");
}
 
void
remove_int()
{
    has_introduced = 0;
}

void
arm_me()
{
    FIXEUID;
    clone_object(RMCOBJ + "kpurse")->move(TO);
    clone_object(RMCOBJ + "ksword")->move(TO);
    clone_object(RMCOBJ + "kplate")->move(TO);
    
    command("wield all");
    command("wear all");
}

void
logger(object killer)
{
    FIXEUID;
    
    write_file("/d/Sparkle/log/npc_kroesus.log", "- "+capitalize(killer->query_real_name()) +
	       " killed me!\t"+extract(ctime(time()),4,15) + "\n");
}

void
do_die(object killer)
{
    if(query_hp()>0)
        return;
    
    logger(killer);

    command("emote screams in agony as he dies!");
    command("emote fetches his bankbook from his money-sack.");
    command("emote shouts: If I can't have it, NO ONE WILL!");
    command("emote throws the bankbook into the sea.");

    if (ship)
	ship->stop_ship("The golden ship has no captain and stops!\n");

    ::do_die(killer);
}
