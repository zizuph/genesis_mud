inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";

#include "../default.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES)

object ship;

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
    ::create_monster();
    set_name("andalusia");
    add_name("captain");
    set_living_name("andalusia");
    set_race_name("human");
    set_adj("lovely");
    add_adj("regal");
    set_stats(({95,160,95,85,85,90}));
    set_alignment(750);
    set_skill(SS_SWIM,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_gender(G_FEMALE);
    heal_hp(15000);
    config_default_trade();
    add_speak("My ship is the finest to sail the seas.\n");
    set_knight_prestige(-15);
    set_act_time(3);
    add_act("emote appraises you with eyes of regal bearing.");
    add_act("say I'm quite pleased at running this shipline between Kabal and Arcoron.");
    add_act("emote looks pleased.");
    add_act("smile");
    add_act("think the days to come");
    set_title("the Illustrious Captain of Kabal");
}

void
init_living()
{
    add_action("buy","buy");
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
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object(PORT + "shipline4/ticket");
    if (!buy_ob) {
	notify_fail("I haven't got anymore tickets.\n");
	return 0;
    }

    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) {
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
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }

    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}

