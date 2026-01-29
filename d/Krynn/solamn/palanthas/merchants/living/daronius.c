/* 
 * Mortis 01.2006
 *
 * The master leather worker in the Arms district of
 * Palanthas.  Crafts armour, packs, scabbards, etc.
 * Armour crafting routine is in Daronius.  Packs and
 * scabbards are sold by his apprentice (leather.c).
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

#define MY_SHOP			MERCH + "leather"
#define FRIEND_HOME		MERCH + "smith"
#define MY_KNIFE		MERCH + "arms/smith_knife"
#define MY_SWORD		MERCH + "arms/smith_sword"
#define MY_POLEARM		MERCH + "arms/smith_polearm"
#define MY_CLUB			MERCH + "arms/smith_club"
#define MY_AXE			MERCH + "arms/smith_axe"

inherit M_FILE
inherit "/std/act/action";

#define MY_CLOTHING		NOBLE + "arms/parmour"
#define MY_ARMOUR		MERCH + "arms/larmour"
#define MY_GENERAL		MERCH + "obj/lgeneral"

int attacked = 0;
string he_crafts();
string he_crafts2();
string he_crafts3(string arm);
string he_crafts4(string sty, string col, string mat, string arm);
string exa_it();
string exa_it2();
object myhome = find_object(MY_SHOP);
object friendhome = find_object(FRIEND_HOME);

string *armour_desc = ({"style", "colour", "material", "armour"});

mapping armour_desc_values = (["style":({"dark", "fur-trimmed", "glistening",
	"heavy", "light", "noble", "ornate", "plain", "rich","skin-tight",
	"supple", "tight", "thick", "thin", "tight"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "mottled-brown",
	"crimson", "maroon", "yellow", "forest-green", "mottled-green",
	"olive-green", "blue", "raven-blue", "silvery"}),
	"material":({"hard", "hide", "leather", "soft", "studded", "suede"}),
	"armour":({"gloves", "bracers", "pauldrons", "sleeves", "breastplate",
	"cuirasse", "vest", "greaves", "leggings", "belt", "cap", "helmet",
	"boots", "tall-boots", "armet", "coat", "suit", "liner"})]);

string *general_desc = ({"style", "colour", "material", "general"});

mapping general_desc_values = (["style":({"dark", "flat", "fur-trimmed",
	"glistening", "light", "noble", "ornate", "plain", "rich", "supple",
	"thin"}),
	"colour":({"black", "white", "charcoal", "grey", "brown", "mottled-brown",
	"crimson", "maroon", "yellow", "forest-green", "mottled-green",
	"olive-green", "blue", "raven-blue", "purple", "silvery"}),
	"material":({"hard", "hide", "leather", "soft", "studded", "suede"}),
	"general":({"backpack", "belt-pouch", "knapsack", "lootsack", "rucksack",
	"sack", "satchel", "thigh-pouch", "bandeleria", "saddlebag",
	"back-holster", "belt-sheath", "boot-sheath", "forearm-sheath", "scabbard",
	"side-holster", "thigh-sheath", "wrist-sheath"})]);

/*prototype*/
void arm_me();

int alrm; /* the alarm while tailoring an item */
mapping stock = ([ ]);
int good = 0;
mixed my_own = ({});
int enter_alrm = 0;

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("daronius");
	set_living_name("daronius");
	add_name(({"human", "worker", "master", "leatherworker", "craftsman"}));
	set_adj("scruffy-bearded");
	add_adj("barrel-chested");
	add_adj("leather");
	set_gender(G_MALE);
	set_short("scruffy-bearded barrel-chested male leather worker");
	set_long("Stout of build with a booming barrel-chest, the master "
	+ "leather worker cuts an impressive figure.  His brown hair is cropped "
	+ "short and wavy, and his beard is thick and, though trim, a bit "
	+ "scruffy.\nHis eyes seem to see straight through you.\n");
	set_race_name("human");
	set_title("Barnicles, Master Leather Craftsman of Palanthas en "
	+ "Mystaclitas");
	
	set_size_descs("tall", "of normal width");
	set_appearance(6);
	
	set_skill(SS_DEFENCE,      75);
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_AWARENESS,    75);
	set_skill(SS_RIDING,       30);
    set_skill(SS_DEFENCE,      75);
    set_skill(SS_PARRY,        90);
    set_skill(SS_WEP_SWORD,    90);
	set_skill(SS_WEP_AXE,      85);
	set_skill(SS_WEP_KNIFE,    85);
	set_skill(SS_WEP_CLUB,     85);
	set_skill(SS_WEP_POLEARM,  85);
    set_skill(SS_BLIND_COMBAT, 75);

	set_stats((({215, 210, 220, 200, 250, 210})), 5);
	set_all_attack_unarmed(20, 30);
	set_all_hitloc_unarmed(40);

	set_alignment(1000);
	set_knight_prestige(-200);
	set_introduce(1);


	set_act_time(18);
	add_act("@@my_add_acts");

	set_cact_time(14);
	add_cact("emote say:  Why do you wish to die, friend?");

	add_ask(" [about] [how] [to] [do] [i] [general] 'pack' / 'packs' / 'item' / 'items' / 'order' / 'ordering' / 'armour' / 'armours' / 'arms' ",
	  "say These are the finest crafted leather products in the land.  "
	+ "Look at the marble sign upon the east wall. You may also "
	+ "<check> anything on it and the gemeral sign beneath.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
def_answer()
{
    command("say Huh?  Oh, I wasn't listening, but don't repeat yourself.");
    return "";
}

void
return_home()
{
	command("say Call upon Mystaclitas again should you need me, friend.");
	command("emote leaves returning to his shop.");
	TO->move(MY_SHOP);
	command("emote arrives from a harrowing journey.");
}

string
my_add_acts()
{
	string myact;
	string exa1 = exa_it();
	string exa2 = exa_it2();

	if (E(TO) != myhome)
		return_home();

	myact = one_of_list(({"emote declares all that has come before to be in "
	+ "the past.",
	"emote nods at you as he pats his barrel chest and swings his "
	+ "arms.",
	"emote goes:  Mmmm, that's good leather.",
	"smell",
	"time",
	"say I see things.  Things that happen.",
	"emote focuses his eyes sharply as he examines "
	+ exa1 + " fresh from the cauldron.",
	"peruse armours",
	"peruse general",
	"emote arranges his tools and models in their racks by the "
	+ "cauldron.",
	"emote says:  Oh, hello friend!",
	"pose",
	"emote delivers " + exa1 + " to " + exa2 + "."}));

	return myact;
}

void
arm_me()
{
	string dcus = one_of_list(({"light", "ornate", "supple", "tight"}));
	string dcol = one_of_list(({"mottled-brown", "mottled-green", "silvery"}));
	string dmat = one_of_list(({"hard", "hide", "soft", "studded", "suede"}));
	string dart = one_of_list(({"leggings", "greaves"}));

	// Daronius's custom gloves.
	object dshirt = clone_object(MY_ARMOUR);
    dshirt->set_armour_data(dcus + "&&"
							+ dcol + "&&"
							+ dmat + "&&"
							+ "gloves");
	dshirt->move(TO);

	// Daronius's custom legwear.
	dcus = one_of_list(({"fur-trimmed", "noble", "ornate"}));

	object dpants = clone_object(MY_ARMOUR);
    dpants->set_armour_data(dcus + "&&"
							+ dcol + "&&"
							+ dmat + "&&"
							+ dart);
	dpants->move(TO);

	// Daronius's custom boots.
	dcus = one_of_list(({"fur-trimmed", "noble", "ornate"}));

	object dboots = clone_object(MY_ARMOUR);
    dboots->set_armour_data("heavy" + "&&"
							+ dcol + "&&"
							+ dmat + "&&"
							+ "boots");
	dboots->move(TO);

	// Daronius's custom body armour.
	dart = one_of_list(({"coat", "breastplate", "cuirasse"}));
	dcus = one_of_list(({"fur-trimmed", "noble", "ornate", "thick"}));

	object dgloves = clone_object(MY_ARMOUR);
    dgloves->set_armour_data(dcus + "&&"
							+ dcol + "&&"
							+ dmat + "&&"
							+ dart);
	dgloves->move(TO);

	command("wear all");
}

void
arm_weapon()
{
	int wep1;
	string wepshort;
	object mywep;

	command("say Uhhhhh... Honey, where's my weapon?");
	if (attacked == 0)
	{
		wep1 = random(5);

		switch (wep1)
		{
		case 0:
			break;
			mywep = clone_object(MY_KNIFE);
			mywep->set_weapon_data("long" + "&&"
								   + "serrated" + "&&"
								   + "dagger");
		case 1:
			mywep = clone_object(MY_SWORD);
			mywep->set_weapon_data("heavy" + "&&"
								   + "long" + "&&"
								   + "sword");
			break;
		case 2:
			mywep = clone_object(MY_POLEARM);
			mywep->set_weapon_data("short" + "&&"
								   + "barbed" + "&&"
								   + "spear");
			break;
		case 3:
			mywep = clone_object(MY_CLUB);
			mywep->set_weapon_data("heavy" + "&&"
								   + "hooked" + "&&"
								   + "maul");
			break;
		default:
			mywep = clone_object(MY_AXE);
			mywep->set_weapon_data("long" + "&&"
								   + "spiked" + "&&"
								   + "battleaxe");
		}
		mywep->move(TO);
		wepshort = mywep->short();
		command("emote takes a " + wepshort + " from a tall woman "
		+ "with an all too knowing smirk.");
		command("wield weapon");
		command("emote wields his " + wepshort + " with eager battle "
		+ "readiness.");
		attacked = 1;
	}
}

void
assist_friend()
{
	command("say A friend is in need!");
	if (attacked == 0)
	{
		arm_weapon();
		attacked = 1;
	}
	command("west");
	command("north");
	command("say Friend, who are these troublemakers?");
	command("assist rock-muscled smith");
}

void
delay_call_friend()
{
	command("emote calls upon the power of Mystaclitas:  Friend to me!");
}

void
attacked_by(object ob)
{
	arm_weapon();
	friendhome->help_my_friend();
	set_alarm(4.5, 0.0, "delay_call_friend");

    ::attacked_by(ob);
}

void
init_living()
{
    ADA("order");
    ADA("collect");
	ADA("buy");
    ::init_living();
}

int
collect(string str)
{
    object armour;
	if (alrm)
	{
		command("say I'm crafting an item.  If you can wait a few more "
		+ "moments, I'll be right with you.");
		return 1;
	}
    command("say Your order.  Yes.");
    command("emote removes your armour from a rack upon the wall.");
    command("emote nods saying:  Your armour.");
    armour = stock[TP->query_real_name()];
    alrm = set_alarm(2.0,0.0,"give_out_armour",TP->query_real_name(),
             armour, 1);
    return 1;
}
/*
 * returns an array: ({ style, colour, material, armour })
 */
mapping compute_all_necessary_armour_data(string *argdata)
{
	int i, j, k, k1, s1, p1, c1, a1;
	string armcomp = argdata[3];
	mapping order;
	order = (["type":0,"style":"", "colour":"", "material":"", "armour":""]);
	k1 = IN_ARRAY(armcomp, armour_desc_values["armour"]);

	if (k1)
	{
		for(i=0,j=sizeof(armour_desc);i<j;i++)
		{
			k = member_array(argdata[i],armour_desc_values[armour_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + armour_desc[i] + " choice for a " + armcomp
				+ ".");
				return (["type":0]); // invalid armour
			}
			order[armour_desc[i]] = armour_desc_values[armour_desc[i]][k];
		}
		order["type"] = 1;
	}
	return order;
}

void
give_out_armour(string who_name, object armour, int flag)
{
	int price, k1;
	object who;
	string what_is_it = armour->short();
	string armprice = armour->query_name();

	k1 = IN_ARRAY(armprice, armour_desc_values["armour"]);

	if (what_is_it == 0)
	{
		what_is_it = "armour";
	}

	if (who_name)
		who = find_player(who_name);

	if (!who || E(TO) != E(who))
	{
		if (flag)
			command("say I see my last customer was too impatient to pick up "
			+ "their " + what_is_it + ".");
		else
			command("say I see my last customer was too impatient to see the "
			+ "completion of their " + what_is_it + ".");

		command("emote scratches his scruffy beard as he goes:  Hmmmmm.");

		if (armour)
        {
			if (flag)
				command("emote places " + what_is_it + " on a rack upon the "
				+ "south wall to be collected later.");
			else
			{
				command("emote places " + what_is_it + " on a rack upon the "
				+ "south wall to be collected later.");
				stock += ([ who_name:armour ]);
			}
        }
		command("say Such is the way of things at times for some.");
		alrm = 0;
		return;
	}

	if (!armour)
	{
		if (flag)
			command("say I have no recollection of an order for a " + what_is_it
			+ " placed by you.");
		else
			command("say Apologies.  Something went wrong with your "
			+ "order.");

		command("smirk");
		alrm = 0;
		return;
	}
	armour->move(TO);
	command("say Your " + what_is_it + ".  Say, that's a good one, too.");
    alrm = 0;

	switch(armprice)
	{
		case "cap":
		case "helmet":
			price = 576;	// 4 gc
			break;
		case "armet":
		case "liner":
			price = 432;	// 3 gc
			break;
		case "breastplate":
		case "cuirasse":
		case "vest":
			price = 1008;	// 7 gc
			break;
		case "suit":
			price = 1872;	// 13 gc
			break;
		case "coat":
			price = 1296;	// 9 gc
			break;
		case "bracers":
		case "pauldrons":
		case "sleeves":
			price = 576;	// 4 gc
			break;
		case "belt":
			price = 288;	// 2 gc
			break;
		case "gloves":
			price = 432;	// 3 gc
			break;
		case "greaves":
		case "leggings":
			price = 720;	// 5 gc
			break;
		case "tall-boots":
			price = 1152;	// 8 gc
			break;
		case "boots":
			price = 576;	// 4 gc
			break;
		default:
			price = 1000;
	}

	if (!MONEY_ADD(who, -price))
	{
		command("say You bear insufficient funds.  There are no discounts.");
		command("say Your " + what_is_it + " will be here for you to collect "
		+ "when you can pay.");
		command("emote places " + what_is_it + " on a rack upon the south "
		+ "wall.");
		armour->move(VOID);
		stock += ([ who_name:armour ]);
		return;
	}
    who->catch_msg("You pay the leather worker " + price + " copper coins.\n");

    armour->remove_shadow();

	if (!command("give " + armour->query_name() + " to " + who_name))
		command("drop " + armour->query_name());

	stock = m_delete(stock, who_name);
    
	if (enter_alrm)
      {
		  remove_alarm(enter_alrm);
		  enter_alrm = 0;
      }
}

int
order(string str)
{
	string cus, col, mat, art;
	string *argdata;
	mapping my_order;

	if (alrm)
	{
		command("say I'm crafting an item.  If you can wait a few more "
		+ "moments, I'll be right with you.");
		return 1;
	}

    NF(C(query_verb()) + " what?\n");

	if (!str)
		return 0;

	if (stock[TP->query_real_name()])
	{
		  NF("There is already an armour in stock for you.  "
		  + "Could you collect it first, friend?\n");
		  return 0;
	}

    /* syntax is: 'order <style> <colour> <material> <armour>' */
	argdata = explode(str," ");

    NF(C(query_verb()) + " <style> <colour> <material> <armour>.\n");

    if(sizeof(argdata) != 4)
	{ return 0; }

	my_order = compute_all_necessary_armour_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(30.0, 0.0, "finished_armour",
		TP->query_real_name(), my_order["style"],
		my_order["colour"], my_order["material"], my_order["armour"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders an armour.\n");

		command("say Alright, let me get started.  If you are not here when "
		+ "I finish, you may return later to <collect> it.");

		add_prop(TSIT, 1);
		add_prop(LIVE_S_EXTRA_SHORT," is crafting a masterful "
		+ argdata[0] + " " + argdata[1] + " " + argdata[2] + " "
		+ argdata[3]);

		set_alarm(2.0, 0.0, "he_crafts");
		set_alarm(10.0, 0.0, "he_crafts2");
		set_alarm(16.0, 0.0, "he_crafts3", argdata[3]);
		set_alarm(24.0, 0.0, "he_crafts4", argdata[0], argdata[1], argdata[2],
			argdata[3]);

      return 1;
	}
    NF("You failed to order a valid armour type.  Read the signs again for "
	+ "valid armour choices.\n");
    return 0;
}

void
finished_armour(string for_who, string sty, string col, string mat, string arm)
{
	int k1;
	string gentype;

	k1 = IN_ARRAY(arm, armour_desc_values["armour"]);

	if (k1)
		gentype = MY_ARMOUR;

	object armour = clone_object(gentype);
    armour->set_armour_data(sty + "&&"
							+ col + "&&"
							+ mat + "&&"
							+ arm);

    give_out_armour(for_who, armour, 0);
}

string
exa_it()
{
	return one_of_list(({"an armour", "a piece of leather", "a cut of hide",
	"a pair of greaves", "a set of pauldrons", "a cuirasse"}));
}

string
exa_it2()
{
	return one_of_list(({"a cloaked short figure", "a cloaked tall figure",
	"a young constable", "a well-dressed squire", "an aging mercenary",
	"a leather armoured male elf", "an old, wide-hatted traveller",
	"a swarthy, stubble-chinned mercenary", "a white-robed woman",
	"a pair of short-cloaked, young noblemen", "a long-bearded dwarf"}));
}

int
react_bow(object actor)
{
	command("emote bows with a hand across his barrel-chest, his bright "
	+ "eyes merrily watching you.");
	return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

string he_crafts()
{
	command("emote drops a piece of leather in the cauldron with a bloop "
	+ "and a burble of bubbles.");
	return "";
}

string he_crafts2()
{
	command("emote uses a pair of tongs to remove a piece of leather from "
	+ "the cauldron of boiling oil and places it on a mold where he begins "
	+ "to work it into shape.");
	return "";
}

string he_crafts3(string arm)
{
	command("emote goes:  \"Mmmm hmm, yes, hrmmmmm,\" as the armour begins "
	+ "to resemble the " + arm + " on the south wall.");
	return "";
}

string he_crafts4(string sty, string col, string mat, string arm)
{
	command("emote gives the " + arm + " to his wife, a tall woman with an "
	+ "all too knowing smirk who adds the professional touches that "
	+ "will make the " + arm + " " + sty + " and " + col + ".");
	command("say Ahh, that is a very good " + sty + " " + col + " " + arm
	+ ", my dear.");

	remove_prop(TSIT);
	remove_prop(LIVE_S_EXTRA_SHORT);
	return "";
}


/* GENERAL ITEMS
 *     START
 *      HERE
 */

/*
 * returns an array: ({ style, colour, material, armour })
 */
mapping compute_all_necessary_general_data(string *argdata)
{
	int i, j, k, k1, s1, p1, c1, a1;
	string gencomp = argdata[3];
	mapping gorder;
	gorder = (["type":0,"style":"", "colour":"", "material":"", "general":""]);
	k1 = IN_ARRAY(gencomp, general_desc_values["general"]);

	if (k1)
	{
		for(i=0,j=sizeof(general_desc);i<j;i++)
		{
			k = member_array(argdata[i],general_desc_values[general_desc[i]]);
			if (k == -1)
			{
				command("say I'm sorry, but " + argdata[i] + " is not an "
				+ "available " + general_desc[i] + " choice for a " + gencomp
				+ ".");
				return (["type":0]); // invalid general item
			}
			gorder[general_desc[i]] = general_desc_values[general_desc[i]][k];
		}
		gorder["type"] = 1;
	}
	return gorder;
}

void
give_out_general(string who_name, object general, int flag)
{
	int price, k1;
	object who;
	string what_is_it = general->short();
	string genprice = general->query_name();

	k1 = IN_ARRAY(genprice, general_desc_values["general"]);

	if (what_is_it == 0)
	{
		what_is_it = "general item";
	}

	if (who_name)
		who = find_player(who_name);

	if (!who || E(TO) != E(who))
	{
		if (flag)
			command("say I see my last customer was too impatient to pick up "
			+ "their " + what_is_it + ".");
		else
			command("say I see my last customer was too impatient to see the "
			+ "completion of their " + what_is_it + ".");

		command("emote scratches his scruffy beard as he goes:  Hmmmmm.");

		if (general)
        {
			if (flag)
				command("emote places " + what_is_it + " on a rack upon the "
				+ "south wall to be collected later.");
			else
			{
				command("emote places " + what_is_it + " on a rack upon the "
				+ "south wall to be collected later.");
				stock += ([ who_name:general ]);
			}
        }
		command("say Such is the way of things at times for some.");
		alrm = 0;
		return;
	}

	if (!general)
	{
		if (flag)
			command("say I have no recollection of an order for a " + what_is_it
			+ " placed by you.");
		else
			command("say Apologies.  Something went wrong with your "
			+ "order.");

		command("smirk");
		alrm = 0;
		return;
	}
	general->move(TO);
	command("say Your " + what_is_it + ".  Say, that's a good one, too.");
    alrm = 0;

	switch(genprice)
	{
		case "saddlebag":
			price = 720;	// 60 sc
			break;
		case "backpack":
		case "knapsack":
		case "rucksack":
		case "bandeleria":
			price = 600;	// 50 sc
			break;
		case "lootsack":
		case "back-holster":
		case "side-holster":
			price = 480;	// 40 sc
			break;
		case "scabbard":
			price = 432;	// 36 sc
			break;
		case "sack":
		case "satchel":
			price = 360;	// 30 sc
			break;
		case "thigh-pouch":
		case "belt-sheath":
		case "boot-sheath":
		case "forearm-sheath":
		case "thigh-sheath":
		case "wrist-sheath":
			price = 288;	// 24 sc
			break;
		case "belt-pouch":
			price = 144;	// 12 sc
			break;
		default:
			price = 144;
	}

	if (!MONEY_ADD(who, -price))
	{
		command("say You need more money, friend.  There are no discounts.");
		command("say Your " + what_is_it + " will be here for you to collect "
		+ "when you can pay.");
		command("emote places " + what_is_it + " on a rack upon the north "
		+ "wall.");
		general->move(VOID);
		stock += ([ who_name:general ]);
		return;
	}
    who->catch_msg("You pay the leather worker " + price + " copper coins.\n");

    general->remove_shadow();

	if (!command("give " + general->query_name() + " to " + who_name))
		command("drop " + general->query_name());

	stock = m_delete(stock, who_name);
    
	if (enter_alrm)
      {
		  remove_alarm(enter_alrm);
		  enter_alrm = 0;
      }
}

int
buy(string str)
{
	string cus, col, mat, gen;
	string *argdata;
	mapping my_order;

	if (alrm)
	{
		command("say I'm crafting an item.  If you can wait a few more "
		+ "moments, I'll be right with you.");
		return 1;
	}

    NF(C(query_verb()) + " what?\n");

	if (!str)
		return 0;

	if (stock[TP->query_real_name()])
	{
		  NF("There is already a general item on order for you.  "
		  + "Could you collect it first, friend?\n");
		  return 0;
	}

    /* syntax is: 'order <style> <colour> <material> <item>' */
	argdata = explode(str," ");

    NF(C(query_verb()) + " <style> <colour> <material> <item>.\n");

    if(sizeof(argdata) != 4)
	{
		if (argdata[0] == "saddlebag")
		{
			if (!MONEY_ADD(TP, -720))
			{
				write("You need more cash, friend.\n");
				return 1;
			}

			write("You order a saddlebag and pay 60 silver.\n");
			say(QCTNAME(TP) + " orders a saddlebag.\n");
			object sadbag = clone_object(MERCH + "obj/saddlebag");
			sadbag->move(TO);

			if (!command("give " + sadbag->query_name() + " to "
			+ TP->query_real_name()))
				command("drop " + sadbag->query_name());
			
			return 1;
		}

		return 0;
	}

	my_order = compute_all_necessary_general_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(2.0, 0.0, "finished_general", TP->query_real_name(),
		my_order["style"], my_order["colour"], my_order["material"],
		my_order["general"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders a general item.\n");

		command("say Alright, let me see here now.");
		command("emote rifles through the items hung on the north wall.");
		return 1;
	}
    NF("You failed to order a valid general item.  Read the signs again for "
	+ "valid item choices.\n");
    return 0;
}

void
finished_general(string for_who, string sty, string col, string mat, string gen)
{
	int k1;
	string gentype;

	k1 = IN_ARRAY(gen, general_desc_values["general"]);

	if (k1)
		gentype = MY_GENERAL;

	object general = clone_object(gentype);
    general->set_general_data(sty + "&&"
							+ col + "&&"
							+ mat + "&&"
							+ gen);

    give_out_general(for_who, general, 0);
	alrm = 0;
}

int
special_attack(object enemy)
{
    int pen, att, wloc;
    string hitloc, how, withweak, withstrong, withmold;
    mixed hitres;

    if (random(5) == 1)
    {
		pen = 350 + random(300);
		wloc = one_of_list(({A_HEAD, A_TORSO, A_LEGS, A_R_ARM, A_L_ARM}));
		withweak = one_of_list(({"a hard leather pouch off the wall",
		"a hide rucksack off the wall", "a hard leather lootsack off the wall",
		"a stiff hide scabbard off the wall", "a soft leather pouch of "
		+ "coins"}));
		withmold = one_of_list(({"a ceramic cuirasse mold off the counter",
		"a clay bracer mold off the counter", "a ceramic greave mold off "
		+ "the counter", "a clay armet mold off the counter"}));
		withstrong = one_of_list(({"a table", "a spare cauldron",
		"black brick"}));
		
		switch (wloc)
		{
			case A_HEAD:
				hitloc = "head";
				break;
			case A_TORSO:
				hitloc = "body";
				break;
			case A_LEGS:
				hitloc = "legs";
				break;
			case A_R_ARM:
				hitloc = "right arm";
				break;
			case A_L_ARM:
				hitloc = "left arm";
				break;
			default:		
		}

		hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1, wloc);

		switch (hitres[0])
		{
			case -1..0:
				enemy->catch_msg(QCTNAME(TO) + " swipes brazenly at your "
				+ hitloc + " but misses.\n");
				tell_room(E(TO), QCTNAME(TO) + " swipes brazenly at "
				+ QTNAME(enemy) + "'s " + hitloc + " but misses.\n",
				({enemy, TO}));
				break;
			case 1..10:
				enemy->catch_msg(QCTNAME(TO) + " clonks your " + hitloc
				+ " with " + withweak + ".\n");
				tell_room(E(TO), QCTNAME(TO) + " clonks " + QTNAME(enemy)
				+ "'s " + hitloc + " with " + withweak + ".\n",
				({enemy, TO}));
				break;
			case 11..17:
				enemy->catch_msg(QCTNAME(TO) + " clonks your " + hitloc
				+ " with " + withweak + " painfully.\n");
				tell_room(E(TO), QCTNAME(TO) + " clonks " + QTNAME(enemy)
				+ "'s " + hitloc + " with " + withweak + " painfully.\n",
				({enemy, TO}));
				break;
			case 18..32:
				enemy->catch_msg(QCTNAME(TO) + " smacks you upside your "
				+ hitloc + " with " + withweak + ".\n");
				tell_room(E(TO), QCTNAME(TO) + " smacks " + QTNAME(enemy)
				+ " upside " + HIS(enemy) + " " + hitloc + " with "
				+ withweak + ".\n", ({enemy, TO}));
				enemy->command("wince");
				break;
			case 33..43:
				enemy->catch_msg(QCTNAME(TO) + " shatters " + withmold
				+ " over your " + hitloc + " with a crash.\nYou stumble "
				+ "around in confusion.\n");
				tell_room(E(TO), QCTNAME(TO) + " shatters " + withmold
				+ " over " + QTNAME(enemy) + "'s " + hitloc + " with a "
				+ "crash.\n" + QCTNAME(enemy) + " stumbles around in "
				+ "confusion.\n", ({enemy, TO}));
				enemy->command("west");
				break;
			case 44..60:
				enemy->catch_msg(QCTNAME(TO) + " crushes your " + hitloc
				+ " with " + withstrong + ".\nYou groan:  Ohhhhh...\n");
				tell_room(E(TO), QCTNAME(TO) + " crushes " + QTNAME(enemy)
				+ "'s " + hitloc + " with " + withstrong + ".\n"
				+ QCTNAME(enemy) + " groans:  Ohhhh...\n", ({enemy, TO}));
				break;
			default:
				enemy->catch_msg(QCTNAME(TO) + " dunks your entire "
				+ hitloc + " into the cauldron of boiling oil.\n");
				tell_room(E(TO), QCTNAME(TO) + " dunks " + QTNAME(enemy)
				+ "'s entire " + hitloc + " into the cauldron of boiling "
				+ "oil.\n", ({enemy, TO}));
				enemy->command("scream");
				break;
		}

		if (enemy->query_hp() <= 0)
			enemy->do_die(TO);

		return 1;
    }

    return 0;
}
