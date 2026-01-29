#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES)

void
create_kalad_monster()
{
    set_name("volo");
    add_name("merchant");
    set_living_name("volo");
    set_race_name("human");
    set_adj("black-haired");
    add_adj("philosophical");
    set_stats(({90, 90, 90, 90, 90, 90}));
    set_alignment(150);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    config_default_trade();
    add_speak("I sell several varieties of weapons, axes and clubs being "+
      "the ones I have with me today.\n");
    set_knight_prestige(-2);
    set_act_time(3);
    add_act("emote looks like he wants to sell you some weapons.");
    add_act("say How fare thee traveller? Perhaps ye be wanting to purchase weapons for yerself?");
    add_act("say If you be travellin the roads, I caution you to arm "+
      "yourself properly...with weapons purchased from me of course.");
    add_act("say Confidentially, I think I have the best weapons in town.");
    set_title("the Travelling Weapons Merchant");
    add_ask(({"weapons", "weapon"}), "The black-haired philosophical human says: I currently have the following for sale.\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-volo axe- 5 gold coins\n"+
      "-volo club- 10 gold coins\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    set_default_answer("The black-haired philosophical human says: Pardon me, but I have no idea what you are talking about.\n");
    set_alarm(1.0, 0.0, "arm_me");
    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

void
arm_me()
{
    object wep;
    seteuid(getuid(TO));
    wep = clone_object(WEP + "wepaxe");
    wep->move(TO);
    wep = clone_object(WEP + "wepclub");
    wep ->move(TO);
    command("wield all");
}

int
buy_axe(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;

    if (!str)
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    {
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    }

    if (what != "axe")
    {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object(WEP + "wepaxe");
    if (!buy_ob)
    {
	notify_fail("I haven't got anything left to sell.\n");
	return 0;
    }

    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price, this_player(), for_c, 0, 0, get_c);

    if (sizeof(result)==1)
    {
	buy_ob->remove_object();
	return 0;
    }

    if (buy_ob->move(this_player()))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	  " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else
    {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }

    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}

int
buy_club(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;

    if (!str)
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    {
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    }

    if (what != "club")
    {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }

    buy_ob=clone_object(WEP + "wepclub");
    if (!buy_ob)
    {
	notify_fail("I haven't got anything left to sell.\n");
	return 0;
    }

    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price, this_player(), for_c, 0, 0, get_c);

    if (sizeof(result)==1)
    {
	buy_ob->remove_object();
	return 0;
    }

    if (buy_ob->move(this_player()))
    {
	write("You drop the " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
	  " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else
    {
	write("You get your " + buy_ob->short() + ".\n");
	say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }

    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}

void
init_living()
{
    add_action(buy_axe, "buy");
    add_action(buy_club, "buy");
}
