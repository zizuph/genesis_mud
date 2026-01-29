/*
 * Duh, where do you think this guy is cloned?
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>

#define	NUM	sizeof(MONEY_TYPES)

//    Prototypes
void introduce_me();
void re_intro();

object	ship;

int intro_id = -1,re_intro_id = -1;
int not_intro;

void
do_die(object killer)
{
    ::do_die(killer);
    if (ship)
	ship->stop_ship("The ship stops; someone killed the captain!\n");
}

void
set_ship(object s)
{
    ship=s;
}

void
create_monster()
{
    set_name("riondir");
    add_name("captain");
    set_title("Captain of the Flying Swan");
    set_living_name("_riondir_");
    set_race_name("elf");
    add_adj("tall");

    add_prop(OBJ_M_NO_ATTACK, "Trust me, you don't want to attack this long-time seafarer.\n");
    set_stats(({ 60, 50, 80, 60, 50, 90 }));
    set_skill(SS_SWIM, 100);
    heal_hp(10000);

    config_default_trade();

    trig_new("%w 'introduces' %s", "react_introduce");
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
    int *result, m_res, price;

    if (!str) {
	notify_fail("Buy what?\n");
	return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    if (what != "ticket") {
	notify_fail("I have no such thing for sale.\n");
	return 0;
    }

    buy_ob=clone_object(STAND_OBJ + "ticket");
    if (!buy_ob) {
	notify_fail("I seem to be out of tickets.\n");
	return 0;
    }

    if (TP->query_average_stat() < 20)
    {
	if (present("the shire line", TP))
	{
	    command("sigh");
	    command("say But, you already have a ticket!");
	    return 1;
	}
	command("smile");
	command("say Newbies get tickets for free you know.\n");
	price = 0;
    }
    else
      price = buy_ob->query_prop(OBJ_I_VALUE);
 
    result = pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1)
    {
	buy_ob->remove_object();
	return 0;
    }
    if (buy_ob->move(this_player())) {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	    " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else {
	write("You get your " + buy_ob->short() + ".\n");
    if (price == 0)
      say(QCTNAME(TP) +" is given a "+buy_ob->short()+".\n");

    else
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }

  if (price != 0)
  {
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
  }

  else
    return 1;
}

void
react_introduce(string person,string who)
{
    if (not_intro)
	return;
    if (intro_id == -1)
        intro_id = set_alarm(4.0,0.0,&introduce_me());
}

void
introduce_me()
{
    remove_alarm(intro_id);
    intro_id = -1;
    command("introduce myself");
    not_intro = 1;
    if (re_intro_id == -1)
        re_intro_id = set_alarm(15.0,0.0,&re_intro());
}

void
re_intro()
{
    not_intro = 0;
    remove_alarm(re_intro_id);
    re_intro_id = -1;
}
