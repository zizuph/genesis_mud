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
    set_name("omareth");
    add_name("merchant");
    set_living_name("omareth");
    set_race_name("drow");
    set_adj("dubious");
    add_adj("shifty");
    set_stats(({70,80,70,25,25,75}));
    set_alignment(-500);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_TRADING,100);
    set_skill(SS_AWARENESS,100);
    config_default_trade();
    set_title("the Successful Merchant of Undraeth");
    add_speak("I sell many valuable goods.\n");
    set_knight_prestige(250);
    set_act_time(3);
    add_act("say For the rarest in trade goods, come trade with me.");
    add_act("grin .");
    add_act("say I promise you won't regret dealing with me.");
    add_ask(({"goods","stuff","wares"}),
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-Item1 - Dragon bane for 3 platinum coins\n"+
      "-Item2 - Gem of light for 2 platinum coins\n"+
      "-Item3 - Gem of darkness for 1 platinum coin\n"+
      "-Item4 - Rothehide Backpack for 1 platinum coin\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    set_default_answer("What were you asking again?\n");
    MONEY_MAKE_GC(random(12))->move(TO,1);
}
void
init_living()
{
    AA(buy_item,buy);
    AA(speak,speak);
    AA(speak,talk);
    AA(speak,chat);
}
int
buy_item(string str)
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
    if(what == "item1")
    {
	buy_ob = clone_object(CPASS(drow/obj/dragon_bane));
    }
    else
    if(what == "item2")
    {
        NF("I'm sorry, I'm all out of these gems.\n");
        return 0;
    }
    else
    if(what == "item3")
    {
        NF("I'm sorry, I'm all out of these gems. However, you "+
        "may try to find them on your own. Deep in the underdark, "+ 
        "there lurks a shadow wolf, with one eye as a gem of darkness.\n");
        return 0;
    }
    else
    if(what =="item4")
    {
	buy_ob = clone_object(CPASS(drow/obj/backpack));
    }
    else
    {
	NF("I have no such item to sell you.\n");
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
