inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"
#define NUM sizeof(MONEY_TYPES)

/* by Antharanos modified by Sarr*/

void
create_monster()
{
    ::create_monster();
    set_name("brilder");
    add_name("piercer");
    set_living_name("brilder");
    set_race_name("goblin");
    set_adj("large");
    add_adj("repulsive");
    set_long("This is a large and repulsive goblin. He is holding a big "+
      "needle which he apparently wants to stick through various parts "+
      "of your body.\n");
    set_stats(({75,75,100,60,60,50}));
    set_alignment(-50);
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,30);
    config_default_trade();
    add_speak("How 'bout I poke a hole in ya?\n");
    set_knight_prestige(50);
    set_act_time(3);
    add_act("emote looks like he wants to poke a hole in your body.");
    add_act("say Let me stick a needle in you!");
    add_act("say My brother is Skeever. He lives in the Port District.");
    add_act("say My brother can't speak very well, unlike me, I'm much more "+
      "sophisticated.\n");
    add_ask("red fang","For only 1 plat(2 for the double), you can have "+
      "my special red fang rings! Just 'buy red fang <single/double>'.\n");
    add_act("emote scratches his crotch.");
    add_act("emote sniffs his armpit.");
    set_title("the Body Piercing Wonder");
    add_ask(({"pierce"}),"Look at the sign ya idjut!\n");
    add_ask(({"skeever"}),"He sells tattoos in the Port District.\n");
    set_default_answer("I don't know much about that crud. Get lost!\n");
    MONEY_MAKE_GC(random(3))->move(TO,1);
}

void
init_living()
{
    if(TP->test_bit("Kalad",4,8))
    {
	set_alarm(2.0,0.0,"greet_redfang");
    }
    AA(buy_pierce,buy);
    ::init_living();
}

void
greet_redfang()
{
    TP->catch_msg(QCTNAME(TO)+" whispers to you: Hail Red Fang "+
      "Warrior! I have a special deal for you..."+
      "just ask me 'red fang' to find out.\n");
}

int
buy_pierce(string str)
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
    if(what == "red fang single")
    {
	if(!TP->test_bit("kalad",4,8))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/single_ring));
	buy_ob->set_ring_value(1728);
	buy_ob->set_ring_metal("black-steel");
	buy_ob->set_ring_metal("wolf-shaped bloodstone",1);
    }if(what == "red fang double")
    {
	if(!TP->test_bit("kalad",4,8))
	    return 0;      
	buy_ob = clone_object(NOBLE(arm/pair_rings));
	buy_ob->set_ring_value(3456);
	buy_ob->set_ring_metal("black-steel");
	buy_ob->set_ring_metal("wolf-shaped bloodstone",1);
    }
    if(what == "pierce1")
    {
	NF("You already have your left ear pierced.\n");
	if(TP->query_prop(KALAD_RING_EAR_LEFT))
	    return 0;
	NF("You already have both ears pierced.\n");
	if(TP->query_prop(KALAD_RING_EAR_BOTH))
	    return 0;
	NF("If you want both ears pierced, remove the right one, and get "+
	  "both of them pierced with option 3.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce1));
    }
    if(what == "pierce2")
    {
	NF("You already have your right ear pierced.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	NF("You already have both ears pierced.\n");
	if(TP->query_prop(KALAD_RING_EAR_BOTH))
	    return 0;
	NF("If you want both ears pierced, remove the left one, and get "+
	  "both of them pierced with option 3.\n");
	if(TP->query_prop(KALAD_RING_EAR_LEFT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce2));
    }
    if(what == "pierce3")
    {
	NF("You already have both ears pierced.\n");
	if(TP->query_prop(KALAD_RING_EAR_BOTH))
	    return 0;
	NF("You have to remove your left one to get this option.\n");
	if(TP->query_prop(KALAD_RING_EAR_LEFT))
	    return 0;
	NF("You have to remove your right one to get this option.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce3));
    }
    if(what == "pierce4")
    {
	NF("You already have your nose pierced.\n");
	if(TP->query_prop(KALAD_RING_NOSE))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce4));
    }
    if(what == "pierce5")
    {
	NF("You already have your left eyebrow pierced.\n");
	if(TP->query_prop(KALAD_RING_EYEB_LEFT))
	    return 0;
	NF("You already have both eyebrows pierced.\n");
	if(TP->query_prop(KALAD_RING_EYEB_BOTH))
	    return 0;
	NF("If you want both eyebrows pierced, remove the right one, and get "+
	  "both of them pierced with option 7.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce5));
    }
    if(what == "pierce6")
    {
	NF("You already have your right eyebrow pierced.\n");
	if(TP->query_prop(KALAD_RING_EYEB_RIGHT))
	    return 0;
	NF("You already have both eyebrows pierced.\n");
	if(TP->query_prop(KALAD_RING_EYEB_BOTH))
	    return 0;
	NF("If you want both eyebrows pierced, remove the left one, and get "+
	  "both of them pierced with option 7.\n");
	if(TP->query_prop(KALAD_RING_EYEB_LEFT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce6));
    }
    if(what == "pierce7")
    {
	NF("You already have both eyebrows pierced.\n");
	if(TP->query_prop(KALAD_RING_EYEB_BOTH))
	    return 0;
	NF("You have to remove your left one to get this option.\n");
	if(TP->query_prop(KALAD_RING_EYEB_LEFT))
	    return 0;
	NF("You have to remove your right one to get this option.\n");
	if(TP->query_prop(KALAD_RING_EYEB_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce7));
    }
    if(what == "pierce8")
    {
	NF("You already have your tongue pierced.\n");
	if(TP->query_prop(KALAD_RING_TONGUE))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce8));
    }
    if(what == "pierce9")
    {
	NF("You already have your lip pierced.\n");
	if(TP->query_prop(KALAD_RING_LIP))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce9));
    }
    if(what == "pierce10")
    {
	NF("You already have your left nipple pierced.\n");
	if(TP->query_prop(KALAD_RING_NIP_LEFT))
	    return 0;
	NF("You already have both nipples pierced.\n");
	if(TP->query_prop(KALAD_RING_NIP_BOTH))
	    return 0;
	NF("If you want both nipples pierced, remove the right one, and get "+
	  "both of them pierced with option 12.\n");
	if(TP->query_prop(KALAD_RING_NIP_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce10));
    }
    if(what == "pierce11")
    {
	NF("You already have your right nipple pierced.\n");
	if(TP->query_prop(KALAD_RING_NIP_RIGHT))
	    return 0;
	NF("You already have both nipples pierced.\n");
	if(TP->query_prop(KALAD_RING_NIP_BOTH))
	    return 0;
	NF("If you want both nipples pierced, remove the left one, and get "+
	  "both of them pierced with option 12.\n");
	if(TP->query_prop(KALAD_RING_NIP_LEFT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce11));
    }
    if(what == "pierce12")
    {
	NF("You already have both nipples pierced.\n");
	if(TP->query_prop(KALAD_RING_NIP_BOTH))
	    return 0;
	NF("You have to remove your left one to get this option.\n");
	if(TP->query_prop(KALAD_RING_NIP_LEFT))
	    return 0;
	NF("You have to remove your right one to get this option.\n");
	if(TP->query_prop(KALAD_RING_NIP_RIGHT))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce12));
    }
    if(what == "pierce13")
    {
	NF("You already have your navel pierced.\n");
	if(TP->query_prop(KALAD_RING_NAVEL))
	    return 0;
	buy_ob = clone_object(NOBLE(arm/pierce13));
    }
    NF("Buy what?\n");
    if(!buy_ob)
	return 0;
    price=buy_ob->query_prop(OBJ_I_VALUE);
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) {
	buy_ob->remove_object();
	NF("Buy what?\n");
	return 0;
    }
    if(buy_ob->query_name() == "ring" || buy_ob->query_name() == "rings")
    {
	if (buy_ob->move(this_player())) {
	    write("You droped the rings.\n");
	    buy_ob->move(environment(this_player()));
	}
	else {
	    write("You get yourself the special rings.\n");
	    say(QCTNAME(TP) + " gets something special!\n");
	}
	write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
	if (change)
	    write("You get " + change + " as change.\n");
	return 1;
    } 
    if (buy_ob->move(this_player())) {
	write("For some reason, the piercer messed up.\n");
	say(QCTNAME(TP) + " tried to get his body pierced done, but the piercer messed up.\n");
	buy_ob->move(environment(this_player()));
    }
    else {
	write("You get yourself pierced.\n");
	say(QCTNAME(TP) + " gets body piercing done!\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}

