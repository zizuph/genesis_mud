inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
create_monster()
{
    ::create_monster();
    set_name("skeever");
    add_name("tattooer");
    set_living_name("skeever");
    set_race_name("goblin");
    set_adj("spike-haired");
    add_adj("mottled");
    set_stats(({50,50,75,40,40,30}));
    set_alignment(-50);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,30);
    config_default_trade();
    add_speak("How 'bout a tattoo ta make ya look more attractive.\n");
    set_knight_prestige(50);
    set_act_time(3);
    add_act("emote looks like he wants you to get a tattoo.");
    add_act("say Get a tattoo or get out!");
    add_act("say Ah'm the most bestest tattooer in the city.");
    set_title("the Masterful Tattooer");
    add_ask(({"tattoo"}),"The spike-haired mottled goblin says: Look at "+
      "the sign ya idjut!\n");
    set_default_answer("The spike-haired mottled goblin says: Unhhh...what "+
      "you want?\n");
    MONEY_MAKE_GC(random(3))->move(TO,1);
}
void
init_living()
{
    AA(buy_tattoo,buy);
}
int
buy_tattoo(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;
    if(!str)
    {
	NF("Buy what?\n");
	return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;
    if(what == "tattoo1")
    {
	buy_ob = clone_object(PORT(obj/tattoo1));
    }
    else
    if(what == "tattoo2")
    {
	buy_ob = clone_object(PORT(obj/tattoo2));
    }
    else
    if(what == "tattoo3")
    {
	buy_ob = clone_object(PORT(obj/tattoo3));
    }
    else
    if(what == "tattoo4")
    {
	buy_ob = clone_object(PORT(obj/tattoo4));
    }
    else
    if(what == "tattoo5")
    {
	buy_ob = clone_object(PORT(obj/tattoo5));
    }
    else
    if(what == "tattoo6")
    {
	buy_ob = clone_object(PORT(obj/tattoo6));
    }
    else
    if(what == "tattoo7")
    {
	buy_ob = clone_object(PORT(obj/tattoo7));
    }
    else
    if(what == "tattoo8")
    {
	buy_ob = clone_object(PORT(obj/tattoo8));
    }
    else
    if(what == "tattoo9")
    {
	buy_ob = clone_object(PORT(obj/tattoo9));
    }
    else
    if(what == "tattoo10")
    {
	buy_ob = clone_object(PORT(obj/tattoo10));
    }
    else
    if(what == "tattoo11")
    {
	buy_ob = clone_object(PORT(obj/tattoo11));
    }
    else
    if(what == "tattoo12")
    {
	buy_ob = clone_object(PORT(obj/tattoo12));
    }
    else
    if(what == "tattoo13")
    {
	buy_ob = clone_object(PORT(obj/tattoo13));
    }
    else
    if(what == "tattoo14")
    {
	buy_ob = clone_object(PORT(obj/tattoo14));
    }
    else
    if(what == "tattoo15")
    {
	buy_ob = clone_object(PORT(obj/tattoo15));
    }
    else
    if(what == "tattoo16")
    {
	buy_ob = clone_object(PORT(obj/tattoo16));
    }
    else
    if(what == "tattoo17")
    {
	buy_ob = clone_object(PORT(obj/tattoo17));
    }
    else
    if(what == "tattoo18")
    {
	buy_ob = clone_object(PORT(obj/tattoo18));
    }
    else
    if(what == "tattoo19")
    {
	buy_ob = clone_object(PORT(obj/tattoo19));
    }
    else
    if(what == "tattoo20")
    {
	buy_ob = clone_object(PORT(obj/tattoo20));
    }
    else
    if(what == "tattoo21")
    {
	buy_ob = clone_object(PORT(obj/tattoo21));
    }
    else
    if(what == "tattoo22")
    {
	buy_ob = clone_object(PORT(obj/tattoo22));
    }
    else
    {
	notify_fail("I have no such thing to sell you.\n");
	return 0;
    }
    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) {
	buy_ob->remove_object();
	return 0;
    }
    if (buy_ob->move(this_player())) {
	write("For some reason, the tattoer messed up.\n");
	say(QCTNAME(TP) + " tried to get a tattoo done, but the tattoer messed up.\n");
	buy_ob->move(environment(this_player()));
    }
    else {
	write("You get a tattoo done on yourself.\n");
	say(QCTNAME(TP) + " gets a tattoo!\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}
