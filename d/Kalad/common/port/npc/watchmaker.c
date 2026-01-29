/* Change the alignment from 600, which seemed kind of 
 * extreme for this NPC to 100
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
/* by Antharanos */
void
create_monster()
{
    ::create_monster();
    set_name("goldblum");
    add_name("watchmaker");
    set_living_name("goldblum");
    set_race_name("human");
    set_adj("formal");
    add_adj("uptight");
    set_stats(({20,20,20,70,50,15}));
    set_alignment(100);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_AWARENESS,90);
    heal_hp(15000);
    config_default_trade();
    add_speak("I sell the finest watches in the city.\n");
    set_knight_prestige(-6);
    set_act_time(3);
    add_act("emote stands respectfully behind the counter.");
    add_act("say Greetings friends. Would you care to purchase a watch today?");
    add_act("say I assure you, my watches are of the utmost quality.");
    add_act("say My watches are of such fine quality, even nobles come "+
      "here to purchase them!");
    set_title("the Watchmaker");
    add_ask(({"watches","watch"}),"The formal uptight human says: The "+
      "sign will inform you of the information you seek.\n");
    set_default_answer("The formal uptight human says: Excuse me, good "+
      "friend, but I didn't understand that last question.\n");
    set_alarm(1.0,0.0,"arm_me");
    MONEY_MAKE_GC(random(10))->move(TO,1);
}
void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/obj/note");
    arm -> move(TO);
}
void
init_living()
{
    add_action("buy_watch","buy");
}
int
buy_watch(string str)
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
    if (what != "watch") {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }
    buy_ob=clone_object("/d/Kalad/common/port/arm/gwatch");
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
