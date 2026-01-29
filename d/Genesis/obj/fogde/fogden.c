/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

inherit "/std/monster.c";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#define MAX_PP 30
#define MAX_GP 300
#define MAX_SP 1000
#define MAX_CP 10000

#define NF(message)	notify_fail(message)
#define TP		this_player()
#define ETP		environment(this_player())
#define TI		this_interactive()
#define TO		this_object()
#define ETO		environment(this_object())
#define BS(message)	break_string(message, 75)

#define RSV		"/d/Genesis/obj/fogde/rsv"
#define FOGDEN		"_fogden_"

public int living_players(object ob);
static void test_money(object *ob);
static void cull_money(object who, object what, int max);

string *names;
int *times;
int curindex;

void
create_monster()
{
    object box;

    setuid();
    seteuid(getuid());

    names = allocate(20);
    times = allocate(20);
    curindex = 0;
    restore_object("/d/Genesis/obj/fogde/savefile");

    if (random(2))
    {
	set_gender(G_MALE);
	set_name(({"tax collector", "feldt"}));
    }
    else
    {
	set_gender(G_FEMALE);
	set_name(({"tax collector", "wibble"}));
    }
    set_adj(({"greedy", "brutish", "big"}));
    set_living_name(FOGDEN);
    set_race_name("troglodyte");
 
              /* str dex con int wis  dis */
    set_stats(({  150, 20, 80, 50, 30, 100 }));
    set_hp(100000); /* Heal fully */

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_PARRY, 80);
    
    add_prop(CONT_I_WEIGHT, 85000);
    add_prop(CONT_I_HEIGHT, 1830);
    add_prop(CONT_I_VOLUME, 84000);

    /* Triggers */
    trig_new("%s 'arrives.' %s", "react_arrive");
    trig_new("%s 'arrives,' %s", "react_arrive");
    trig_new("%s 'arrives' %s", "react_arrive");
    
    /* Start the walkabout */
    set_random_move(random(5) + 5);
}

void
react_arrive(string who, string what)
{
    call_out("delay_arrive", 1, who);
}

void
delay_arrive(string who)
{
    object pl;

    pl = find_player(lower_case(who));
    if (pl && !pl->query_met(lower_case(query_name())))
	command("introduce myself");
    test_money(filter(all_inventory(ETO), "living_players", this_object()));
}

void
enter_env(object dest, object old)
{
    ::enter_env();
    call_out("delay_enter", 1);
}

void
delay_enter()
{
    object *ob;
    int i;

    ob = filter(all_inventory(ETO), "living_players", this_object());

    if (!sizeof(ob))
	return;

    for (i = 0 ; i < sizeof(ob) ; i++)
    {
	if (!ob[i]->query_met("feldt"))
	{
	    command("introduce myself");
	    break;
	}
    }

    test_money(ob);
}

public int
living_players(object ob)
{

    if (!living(ob) ||
	!query_ip_number(ob))
	return 0;

    return 1;
}

void
test_money(object *who)
{
    int i, j;
    object *c_obj;

    for (i = 0 ; i < sizeof(who) ; i++)
    {
	j = member_array(who[i]->query_real_name(), names);
	if(j >= 0 && who[i]->query_age() - times[j] < 3600)
	    continue;
	c_obj = filter(deep_inventory(who[i]), "find_money", this_object());

	for (j = 0 ; j < sizeof(c_obj) ; j++)
	{
	    switch(c_obj[j]->query_coin_type())
	    {
	    case "copper":
		if (c_obj[j]->num_heap() > MAX_CP)
		    cull_money(who[i], c_obj[j], MAX_CP);
		break;
		    
	    case "silver":
		if (c_obj[j]->num_heap() > MAX_SP)
		    cull_money(who[i], c_obj[j], MAX_SP);
		break;
		
	    case "gold":
		if (c_obj[j]->num_heap() > MAX_GP)
		    cull_money(who[i], c_obj[j], MAX_GP);
		break;
		
	    case "platinum":
		if (c_obj[j]->num_heap() > MAX_PP)
		    cull_money(who[i], c_obj[j], MAX_PP);
		break;
		
	    default:
		/* Strange coin indeed */
		write("Gack! Coin type unknown: " + c_obj->query_coin_type() + ".\n");
		break;
	    }
	}
    }
}

static void
cull_money(object who, object what, int max)
{
    object *list;
    int i;

    if((i = member_array(who->query_real_name(), names)) < 0) {
	names[curindex] = who->query_real_name();
	times[curindex] = who->query_age();
	curindex++;
    } else {
	times[i] = who->query_age();
    }

    command("say Hmmm... " + capitalize(who->query_real_name()) + " you have much too much " + what->query_coin_type() + " in\nyour pockets... You owe about " + (what->num_heap()/10) + " to the welfare board of Genesis.\nI'd just as well take it now, don't you think?");
    say(QCTNAME(TO) + " takes something from " + QCTNAME(who) + ".\n");
    MONEY_MOVE(what->num_heap()/10, what->query_coin_type(), who, TO);
    list = filter(all_inventory(TO), "find_money", TO);

    for (i = 0 ; i < sizeof(list) ; i++)
    {
/*	RSV->add_victim(who->query_real_name(), list[i]); */
	command("insert " + list[i]->num_heap() + " " + list[i]->query_coin_type() + " coins in box");
    }
    save_object("/d/Genesis/obj/fogde/savefile");
}

public int
find_money(object ob)
{
    if (file_name(ob)[0..9] == "/std/coins")
	return 1;

    return 0;
}
