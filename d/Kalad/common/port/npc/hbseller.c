inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
void
create_monster()
{
    ::create_monster();
    set_name("fella");
    add_name("seller");
    set_race_name("hobbit");
    set_adj("talkative");
    add_adj("rotund");
    set_long("A jolly little halfling, he patiently stands here trying "+
      "to sell as much halfing beer as he can. Apparently he's been selling "+
      "quite a lot of it too, since he is decked out in expensive clothing.\n");
    set_stats(({50,75,50,25,25,50}));
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_TRADING,70);
    heal_hp(15000);
    config_default_trade();
    add_speak("Hello! Care to buy some good old halfing beer?\n");
    set_knight_prestige(-10);
    set_act_time(6);
    add_act("think beer");
    add_act("giggle");
    add_act("say Halfling beer is the best!");
    add_act("say How about a good old halfling beer for the road!");
    add_act("say How about several halfling beers for the road!");
    add_act("say Buy my beer :-)");
    add_act("get all");
    add_act("wear all");
    add_act("wield all");
    add_act("get all from corpse");
    set_title("the Seller of Beer");
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/hbshat");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/hbsrobe");
    arm -> move(TO);
    command("wear all");
    MONEY_MAKE_GC(random(5))->move(TO,1);
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
    if (what != "beer") {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }
    buy_ob=clone_object("/d/Kalad/common/port/obj/triple_stout");
    if (!buy_ob) {
	notify_fail("I haven't got anymore beer!\n");
	return 0;
    }
    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) {
	buy_ob->remove_object();
	return 0;
    }
    if (buy_ob->move(this_player())) {
	write("You drop " + buy_ob->short() + " on the ground.\n");
	say(QCTNAME(TP) + " drops " + buy_ob->short() +
	  " on the ground.\n");
	buy_ob->move(environment(this_player()));
    }
    else {
	write("You get " + buy_ob->short() + ".\n");
	say(QCTNAME(TP) + " buys " + buy_ob->short() + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}
