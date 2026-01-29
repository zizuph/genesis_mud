/* 
 * Proprietor of general equipment shop off Jems Court
 * in Aesthetics quarter of Palanthas.
 *
 * Mortis 04.2006
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define NUM	sizeof(MONEY_TYPES)

inherit CITIZEN;
inherit "/std/act/action";
inherit "/lib/trade";

/* prototypes */
void arm_me();
int good = 0, enter_alrm = 0, attacked = 0, test;
int move_item(mixed arg);
mixed my_own = ({});


void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("manny");
	set_living_name("manny");
	add_name(({"human", "shopkeep", "shopkeeper", "bowyer"}));
	set_adj("well-equipped");
	add_adj("adventurous");
	set_gender(G_MALE);
	set_short("well-equipped adventurous male shopkeeper");
	set_long("The shopkeep has a strong chest, muscular biceps, trim figure, "
	+ "and is well-equipped with pouches, holsters, packs, and adventuring "
	+ "gear of all types.  His thin beard cannot conceal his smile curling "
	+ "up to the left, and his brown eyes gaze playfully about.\n");
	set_race_name("human");
	set_title("the General Equipment Supplier of Palanthas");
	
	set_size_descs("tall", "of normal width");
	set_appearance(1);
	
	set_skill(SS_DEFENCE,      50);
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_AWARENESS,    35);
    set_skill(SS_BLIND_COMBAT, 20);

	set_stats((({120, 105, 110, 100, 65, 100})), 3);
	set_all_attack_unarmed(15, 15);
	set_all_hitloc_unarmed(10);

	set_alignment(600);
	set_knight_prestige(-90);
	set_introduce(1);

	set_cact_time(45);
	add_cact("say I used this pick to climb out of a dreshan harbinger "
	+ "crevasse.  I'll use it to climb out of that fat one behind you, "
	+ "too.");
	add_cact("say It used to be you punks stayed in the alleys behind the "
	+ "court.  Now I'll send you back so perforated, your homies' opinions "
	+ "of you will forever be blemished.");
	add_cact("say In Ergoth they talk all about how no good you are.  "
	+ "Everyone says so.  They all know it.");
	add_cact("say Have fun in jail.");
	add_cact("emote shows you the business end of his light steel pick "
	+ "saying:  Want me to add another hole in your back end?  They're "
	+ "going to love you in the city jail.");

	add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering' / 'equipment' / 'gear' / 'goods'",
	  "say Have a look at the sign, good customer.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
def_answer()
{
	if (TP->query_gender() != G_FEMALE)
	{
		command("emote goes hmmmm:  Good question, customer.  I haven't come "
		+ "across the answer to that one in my travels.");
		return "";
	}

	command("hmm");
    command("say In all my travels I don't think I've come across such an "
	+ "intriguing question or more worldly lady.");
	command("gaze " + TP->query_real_name());
	command("say Tell me more about yourself.");
    return "";
}

void
arm_me()
{
	// Manny's Bandolier
	object mband = clone_object(MERCH + "obj/lgeneral");
	mband->set_general_data("dark" + "&&" + "grey" + "&&" + "hard" + "&&"
						    + "bandeleria");
	mband->move(TO);

	// Manny's Pouch
	object mpouch = clone_object(MERCH + "obj/lgeneral");
	mpouch->set_general_data("dark" + "&&" + "grey" + "&&" + "hard" + "&&"
						    + "belt-pouch");
	mpouch->move(TO);
	MONEY_MAKE_GC(5 + random(13))->move(mpouch);


	// Manny's vest.
	object kvest = clone_object(MERCH + "arms/larmour");
	kvest->set_armour_data("plain" + "&&" + "brown" + "&&" + "leather"
						   + "&&" + "vest");
	kvest->move(TO);

	// Manny's belt.
	object kbelt = clone_object(MERCH + "arms/larmour");
	kbelt->set_armour_data("dark" + "&&" + "grey" + "&&" + "hard" + "&&"
						   + "belt");
	kbelt->move(TO);

	// Manny's custom pants.
	object kpants = clone_object(NOBLE + "arms/parmour");
    kpants->set_armour_data("Manny" + "&&" + "plain" + "&&" + "grey" + "&&"
						    + "wool" + "&&" + "capris");
	kpants->move(TO);

	// Manny's custom shoes.
	object kshoes = clone_object(MONKS + "arms/lurr_shoes");
    kshoes->set_footwear_data("buckled" + "&&" + "grey" + "&&" + "hard" + "&&"
							+ "shoes");
	kshoes->move(TO);

	command("wear all");
	command("close pouch");
}

void
arm_weapon()
{
	string wepname;
	object mywep;

	command("say I've seen this before.");
	if (attacked == 0)
	{
		mywep = clone_object(MERCH + "arms/smith_club");
		mywep->set_weapon_data("light" + "&&" + "steel" + "&&" + "pick");
		mywep->move(TO);
		wepname= mywep->short();

		command("emote draws a " + wepname + " from his dark grey hard "
		+ "leather bandeleria.");
		command("wield weapon");
		command("emote readies his " + wepname + " to defend himself until "
		+ "the constable arrives to hurt you.");
		attacked = 1;
	}
}

void
attacked_by(object ob)
{
	arm_weapon();

    ::attacked_by(ob);
}


void
init_living()
{
	ADA("buy");
    ::init_living();
}

int
buy(string str)
{
    string name, str1, str2, str3;
    int price, num;
    
	NF("Buy what?  Read the sign for a list of goods.\n");
	if (!str)
		return 0;
    
    // Has the player defined how payment will be done and what change
	//to get back?  
	if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
	{
		// Well, maybe player has defined how payment will be done atleast?
		str3 = "";
		if (sscanf(str, "%s with %s", str1, str2) != 2)
		{
			str2 = "";
			str1 = str;
		}
	}
    
	if (sscanf(str1, "%d %s", num, str1) != 2)
		num = 1;

	if (num == 0)
		num = 1;

	if (parse_command(str1, ({}), "[great] 'lamp' / 'lamps'"))
	{
		name = "mlamp_great";
		price = num * 1728;
	}

	else if (parse_command(str1, ({}), "[hooded] 'lantern' / 'lanterns'"))
	{
		name = "mlantern_hooded";
		price = num * 432;
	}

	else if (parse_command(str1, ({}), "[bullseye] 'lantern' / 'lanterns'"))
	{
		name = "mlantern_bullseye";
		price = num * 576;
	}

	else if (parse_command(str1, ({}), "'oil' / 'flask' / 'flasks'"))
	{
		name = "moil_flask";
		price = num * 288;
	}

	else if (parse_command(str1, ({}), "[white] [phosphentus] [phosphent] 'torch' / 'torches'"))
	{
		name = "ptorch";
		price = num * 288;
	}

	else if (parse_command(str1, ({}), "[20m] [hemp] 'rope' / 'ropes'"))
	{
		name = "mhemp_rope";
		price = num * 288;
	}

	else if (parse_command(str1, ({}), "[20m] [silk] 'rope' / 'ropes'"))
	{
		name = "msilk_rope";
		price = num * 1152;
	}

	else if (parse_command(str1, ({}), "[iron] 'grapple' / 'grapples'"))
	{
		name = "mgrapple";
		price = num * 288;
	}

	else if (parse_command(str1, ({}), "[leather] 'guige' / 'guiges'"))
	{
		name = "guige";
		price = num * 720;
	}

	else if (parse_command(str1, ({}), "'piece' / 'pieces' / 'chalk' / 'chalks'"))
	{
		name = "mchalk";
		price = num * 120;
	}

	else if (parse_command(str1, ({}), "[suede] 'waterskin' / 'waterskins' / 'skin' / 'skins'"))
	{
		name = "mwaterskin";
		price = num * 144;
	}

	else
	{
		write("Smiling politely the shopkeeper says:  I don't understand "
		+ "what you want to buy.\n");
		return 1;
	}

	NF("Manny is good, but he can't carry more than ten items at once.\n");
	if (num > 10)
		return 0;
    
	NF("You have insufficient funds for that transaction.\n");
	if (!MONEY_ADD(TP, -price))
		return 0;
		
	write("You pay " + price + " copper coins.\n");

    write("The shopkeeper fetches your order.\n");
    
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)	// Confirm need for test.
{
	object purchase, ob;
	string file, name;
	int i, num;
    
	name = arg[0];
	num = arg[1];
	ob = arg[2];
    
	for (i = 0; i < 10; i++)
	{
		num--;
		file = MONKS + "obj/" + name;
		purchase = clone_object(file);
	  
		if (!test && (purchase->move(ob)))
		{
			ob->catch_msg("You drop the " + purchase->short() +
					  " on the floor.\n");
			say(QCTNAME(ob) + " drops a " + purchase->short() + 
				" on the floor.\n", ob);
			purchase->move(TO);
		}

		else if (!test) 
		{
			if (num == 0)
			{
				if (arg[1] > 1)
				{
					ob->catch_msg("You get some " + purchase->plural_short()
					+ ".\n");
					say(QCTNAME(ob) + " buys some " + purchase->plural_short()
					+ ".\n", ob);
				}

				else 
				{
					ob->catch_msg("You get your " + purchase->short() + ".\n");
					say(QCTNAME(ob) + " buys " + purchase->short() + ".\n",
						ob);
				}
			}
		}

		else 
		{
			say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
			return 1;
		}

		if (num < 1)
			break;
	}
    
	if (num > 0)
		set_alarm(1.0, 0.0, &move_item(({name, num, ob})));

	return 1;
}

int
react_bow(object actor)
{
	command("emote nods his hooded head briefly.");
	return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}
