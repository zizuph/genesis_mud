/*
 * Ear and nose piercer, the "Perforian", at
 * Laethorian Spa and Body.  Also sells rings,
 * studs, and gems for them.  Unpierces as well.
 *
 * Mortis 01.2006
 * Based off open pierce code from Kalad
 *
 */

#include "../../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Kalad/common/noble/arm/ring.h"

inherit CITIZEN;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES)

void
create_krynn_monster()
{
    set_name("sturk");
    add_name("perforian");
    set_living_name("sturk");
    set_race_name("human");
    set_adj("gaunt");
    add_adj("white-coated");
    set_long("The perforian is a rather tall, thin, and gaunt faced man "
	+ "with a serious, emotionless expression, tiny spectacles at the end "
	+ "of his hooked nose, and a long, white coat that hangs down to his "
	+ "knees.  He appears to take his work very seriously.\n");
	set_title("the Licensed Perforian of Laethorian Spa and Body");
    set_stats(({75,75,100,60,60,50}));
    set_alignment(-50);
	set_knight_prestige(-50);
	set_introduce(1);

    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 36);
	set_all_hitloc_unarmed(20);

	set_size_descs("very tall", "lean");
	set_appearance(1);

    set_act_time(12);
    add_act("smile serious");
	add_act("nod serious");
	add_act("say Welcome to the piercery of the Laethorian.");
	add_act("say We are a licensed piercery.  You won't find a cleaner, more "
	+ "professional environment for your piercing needs.");
	add_act("emote cleans and polishes a set of sharp needles behind the "
	+ "semi-circular counter.");
	add_act("emote changes a jar of sterilization fluid behind the "
	+ "semi-circular counter.");
	add_act("bow curt");

	set_cact_time(10);
    add_cact("shout Alarm!  Alarm!");

	add_ask("license", "say The Laethorian Piercery is licensed by the "
	+ "city.  That means monthly inspections and the highest sanitation "
	+ "standards in any realm.  We take your safety very seriously.", 1);
	add_ask("piercery", "say A piercery is licensed by the city to perform "
	+ "body piercings under sanitary conditions.  We are so licensed.", 1);
	add_ask(({"service", "services", "pierce", "pierces", "piercing",
		"piercings", "price", "prices"}), "say Have a look at our sign on "
	+ "the counter and feel free to peruse our display.  We offer ear and "
	+ "nose piercings and sell a variety of rings and studs to fit them.  "
	+ "Our jewelry is all custom designed by Harnoncourt jewelers.", 1);
	add_ask(({"laethorian", "spa", "dayspa"}), "say Laethorian Spa and "
	+ "Body is the finest bath and spa in the city.  The service is "
	+ "impeccable and services unmatched.  It is very popular with the "
	+ "nobles and has always been welcome in the quarter.", 1);
	add_ask(({"palanthas", "city"}), "say Palanthas, the noble quarter in "
	+ "particular, is the finest in the realm and renowned among "
	+ "cities.  You will find everything you're looking for here.", 1);

    set_default_answer("say I am not licensed to qualify that question.", 1);

	config_default_trade();
}

void
arm_me()
{
    seteuid(getuid(TO));

	object dgloves = clone_object(NOBLE + "arms/parmour");
    dgloves->set_armour_data("sturk" + "&&"
							+ "formal" + "&&"
							+ "white" + "&&"
							+ "arrasene" + "&&"
							+ "long-gloves");
	dgloves->move(TO);

	command("wear all");
	MONEY_MAKE_PC(random(1))->move(TO);
	MONEY_MAKE_GC(10 + random(10))->move(TO);
}

void
init_living()
{
    ADD("buy_pierce", "pierce");
    ::init_living();
}

int
buy_pierce(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;
    if(!str)
    {
	NF("Pierce what?\n");
	return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;

    if(what == "left ear")
    {
		NF("You already have your left ear pierced.\n");
		if(TP->query_prop(KALAD_RING_EAR_LEFT))
			return 0;
		NF("You already have both ears pierced.\n");
		if(TP->query_prop(KALAD_RING_EAR_BOTH))
			return 0;
		NF("If you want both ears pierced, remove the right one, and get "+
		  "both of them pierced.\n");
		if(TP->query_prop(KALAD_RING_EAR_RIGHT))
			return 0;
		buy_ob = clone_object(NOBLE + "/obj/pierce1");
    }
    if(what == "right ear")
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
		buy_ob = clone_object(NOBLE + "/obj/pierce2");
    }
    if(what == "both ears")
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
		buy_ob = clone_object(NOBLE + "/obj/pierce3");
    }
    if(what == "nose")
    {
		NF("You already have your nose pierced.\n");
		if(TP->query_prop(KALAD_RING_NOSE))
			return 0;
		buy_ob = clone_object(NOBLE + "/obj/pierce4");
    }
/*    if(what == "pierce5")
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
    }*/

	NF("Pierce what?\n");
    if(!buy_ob)
		return 0;
	
	price=buy_ob->query_prop(OBJ_I_VALUE);
	
	result=pay(price,this_player(),for_c,0,0,get_c);
	
	if (sizeof(result)==1)
	{
		buy_ob->remove_object();
		NF("You require more funds.\n");
		return 0;
	}
	
	if(buy_ob->query_name() == "ring" || buy_ob->query_name() == "rings")
	{
		if (buy_ob->move(this_player()))
		{
			write("You dropped the rings.\n");
		
			buy_ob->move(environment(this_player()));
		}
		else
		{
			write("You get yourself the special rings.\n");
			say(QCTNAME(TP) + " gets something special!\n");
		}
		write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
		if (change)
			write("You get " + change + " as change.\n");
		return 1;
    } 

    if (buy_ob->move(this_player()))
	{
	write("For some reason, the perforian was unable to set the piercing.\n");
	say(QCTNAME(TP) + " tried to get " + HIS(TP) + " body pierced, but the "
	+ "perforian encountered an unusual problem.\n");
	buy_ob->move(environment(this_player()));
    }
    else {
	write("The perforian procures a stainless steel tray from beneath the "
	+ "counter, selects a long, sharp, and sterilized needle from it, and in "
	+ "one professionally precise movement pierces your " + what + ".\n");
	say("The perforian procures a stainless steel tray from beneath the "
	+ "counter, selects a long, sharp, and sterilized needle from it, and in "
	+ "one professionally precise movement pierces the " + what + " of "
	+ QCTNAME(TP) + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
	write("You get " + change + " as change.\n");
    return 1;
}
