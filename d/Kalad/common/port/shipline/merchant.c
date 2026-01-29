inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";

#include "../default.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"

#define NUM sizeof(MONEY_TYPES)

void
create_monster()
{
    ::create_monster();
    set_name("belorin");
    add_name("merchant");
    set_living_name("belorin");
    set_race_name("human");
    set_adj("dark-haired");
    add_adj("brown-eyed");
    set_stats(({75,85,75,65,65,75}));
    set_alignment(500);
    set_skill(SS_SWIM,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_UNARM_COMBAT,100);
    heal_hp(15000);
    config_default_trade();
    add_speak("I sell many useful items...torches, lamps, flasks of oil...\n");
    set_knight_prestige(-500);
    set_act_time(3);
    add_act("emote looks like he's trying to sell you something.");
    add_act("say Howdy foreigner! Would ya care to buy some of me wares?");
    add_act("say I think its a good thing that Kalad has opened trade with the outside world, it'd do us a lot of good, me thinks.");
    add_act("say My goods are much cheaper then those high-priced goat-stealin merchants up in the city!");
    add_act("shout Get your torches, lamps and oil!");
    add_act(({"say Have you been to the Port District?","point north","say That's the way to it. I'd go there myself, but I have goods to sell."}));
    set_title("the Humble Merchant");
    add_ask(({"wares","goods"}),"The dark-haired brown-eyed human says: I can sell ye torches, lamps and oil...would ye care to buy some?\n");
    add_ask(({"price"}),"The dark-haired brown-eyed human says: You'll just have to buy something and see, eh?\n");
    add_ask(({"port"}),"The dark-haired brown-eyed human says: Just follow the "+
      "path north and ye should reach it.\n");
    set_default_answer("The dark-haired brown-eyed human says: I'm sorry, the waves seem to be affecting my hearing, I didn't quite understand what ye wanted ta buy.\n");
}

void
init_living()
{
    add_action("buy_torch","buy");
    add_action("buy_lamp","buy");
    add_action("buy_oil","buy");
}

int
buy_torch(string str)
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
    if (what != "torch") {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object("/d/Kalad/common/caravan/obj/torch");
    if (!buy_ob) {
	notify_fail("I haven't got anything left to sell.\n");
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

int
buy_lamp(string str)
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
    if (what != "lamp") {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object("/d/Kalad/common/caravan/obj/oil_lamp");
    if (!buy_ob) {
	notify_fail("I haven't got anything left to sell.\n");
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

int
buy_oil(string str)
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
    if (what != "oil") {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object("/d/Kalad/common/caravan/obj/oilflask");
    if (!buy_ob) {
	notify_fail("I haven't got anything left to sell.\n");
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

