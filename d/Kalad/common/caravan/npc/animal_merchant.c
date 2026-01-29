#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES)

void
create_kalad_monster()
{
    set_name("durmor");
    add_name("merchant");
    set_living_name("durmor");
    set_race_name("human");
    set_adj("slick");
    add_adj("dark-haired");
    set_stats(({75, 75, 75, 75, 75, 75}));
    set_alignment(100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_TRADING, 100);
    set_skill(SS_AWARENESS, 100);
    config_default_trade();
    set_title("the Animal Merchant of Kabal");
    add_speak("I'm here selling small animals as pets, for those that "+
      "need companionship. Would you care to buy one?\n");
    set_knight_prestige(-1);
    set_act_time(3);
    add_act("say Greetings traveller! Care to buy an animal?");
    add_ask(({"pets", "pet", "companion", "companions", "animals", "animal"}),
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-Animal1 - A small black cat for 1 gold coin\n"+
      "-Animal2 - A small brown puppy for 2 gold coins\n"+
      "-Animal3 - A small blue parakeet for 3 gold coins\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    set_default_answer("What were you asking again?\n");
    MONEY_MAKE_SC(random(10))->move(TO, 1);
}

int
buy_animal(string str)
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

    if(what == "animal1")
    {
	buy_ob = clone_object(NPC + "animal1");
    }

    else if(what == "animal2")
    {
	buy_ob = clone_object(NPC + "animal2");
    }

    else if(what == "animal3")
    {
	buy_ob = clone_object(NPC + "animal3");
    }
    else
    {
	NF("I have no such animal to sell to you.\n");
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
    add_action(buy_animal, "buy");
}
