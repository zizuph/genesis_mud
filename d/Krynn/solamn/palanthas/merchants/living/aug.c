/* 
 * Mortis 03.2006
 *
 * Custom bowyer outside Arms district in Palanthas.
 * Hooded and mysterious.  Actually a hobgoblin from
 * the caves in the east mts who fled as a renegade to
 * make his way in Palanthas.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE
inherit "/std/act/action";

#define MY_BOW			MERCH + "arms/aug_bow"
#define MY_BOWSTRING	"/std/bowstring"
#define MY_ARROWS		MERCH + "arms/aug_arrows"
#define MY_QUIVER		MERCH + "arms/aug_quiver"

/* prototypes */
void arm_me();
int alrm; /* the alarm while preparing a bow */
int good = 0;
int enter_alrm = 0;
int attacked = 0;
mixed my_own = ({});
string my_cacts();
string prep_bow(string sty1, string sty2, string wep);

mapping stock = ([ ]);

string *weapon_desc = ({"style1", "style2", "weapon"});

mapping bow_desc_values = (["style1":({"black", "blue", "dark", "dark-brown",
	"dark-green", "golden", "grey", "pale", "polished", "plain", "red",
	"shaded", "silvery", "white", "yellow"}),
	"style2":({"composite", "darkwood", "horseman", "hunting", "lacquered",
	"mahogany", "oaken", "ornate", "pinewood", "poplar"}),
	"weapon":({"bow", "longbow", "shortbow"})]);


void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("aug");
	set_living_name("aug");
	add_name(({"hobgoblin", "bowyer"}));
	set_adj("huge");
	add_adj("grey-hooded");
	set_gender(G_MALE);
	set_short("huge grey-hooded male bowyer");
	set_long("If this bowyer is an elf, he is the largest you've ever seen "
	+ "with broad, muscular shoulders and powerfully built legs.  Dressed "
	+ "for archery with bare arms and light armour, he certainly has the "
	+ "style of an elven archer.\nHe is breathing gruffly beneath his "
	+ "enshrouding grey hood.\nHis chest expands and contracts powerfully "
	+ "with each breath.\n");
	set_race_name("hobgoblin");
	set_title("the Kal'tok Renegade of Palanthas");
	
	set_size_descs("extremely tall", "of normal width");
	set_appearance(1);
	
	set_skill(SS_DEFENCE,      70);
	set_skill(SS_UNARM_COMBAT, 65);
	set_skill(SS_AWARENESS,    55);
    set_skill(SS_WEP_MISSILE,  90);
    set_skill(SS_BLIND_COMBAT, 65);

	set_stats((({190, 180, 180, 110, 135, 170})), 2);
	set_all_attack_unarmed(30, 35);
	set_all_hitloc_unarmed(5);

	set_alignment(0);
	set_knight_prestige(-20);
	set_introduce(0);

	set_cact_time(11);
	add_cact("@@my_cacts");

	add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering' / 'bow' / 'weapon' / 'weapons' / 'bows'",
	  "say Read the sign please, master, for information.", 1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");

}

string
def_answer()
{
	command("emote grumbles quietly beneath his hood.");
    command("say The sign, please, master.");
    return "";
}

void
arm_me()
{
	// Aug's vest.
	object kvest = clone_object(MERCH + "arms/aug_vest");
	kvest->move(TO);

	// Aug's hood.
	object khood = clone_object(MERCH + "arms/aug_hood");
	khood->move(TO);

	// Aug's custom gloves.
	object kgloves = clone_object(MERCH + "arms/larmour");
    kgloves->set_armour_data("thick" + "&&"
							+ "grey" + "&&"
							+ "leather" + "&&"
							+ "gloves");
	kgloves->move(TO);

	// Aug's custom boots.
	object kboots = clone_object(MERCH + "arms/larmour");
    kboots->set_armour_data("thick" + "&&"
							+ "grey" + "&&"
							+ "hard" + "&&"
							+ "boots");
	kboots->move(TO);

	command("wear all");
}

void
arm_weapon()
{
	string wepname;
	object mywep, myquiver, myarrows;

	command("say So be it.");
	if (attacked == 0)
	{
		mywep = clone_object(MY_BOW);
		mywep->set_weapon_data("grey" + "&&"
							   + "composite" + "&&"
							   + "shortbow");
		mywep->move(TO);
		wepname= mywep->short();

		myquiver = clone_object(MY_QUIVER);
		myquiver->move(TO);

		myarrows = clone_object(MY_ARROWS);
		myarrows->set_heap_size(125);
		myarrows->move(myquiver);

		command("emote takes a " + wepname + " and a quiver from a rack on "
		+ "the north wall.");
		command("wield weapon");
		command("emote grasps his " + wepname + " in his large "
		+ "paws gruffly.");
		attacked = 1;
	}
}

string
my_cacts()
{
	object mybowstring;

    if (!sizeof(query_weapon(-1)))
	{
		command("emote fetches a spare bowstring from his work table.");
		mybowstring = clone_object("/std/bowstring");
		mybowstring->move(TO);
		command("string bow");
		command("wield bow");
		command("emote wields his bow grunting gruffly.");
	}

	command("emote growls throatily from beneath his hood.");
	return "";
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
    ADA("order");
    ADA("collect");
	ADA("buy");
    ::init_living();
}

int
buy(string str)
{
	object purchase;
	string who_purch;

	NF("Buy what?  Arrows, a quiver, or a bowstring?\n");
	if (!str)
		return 0;

	if (parse_command(str, ({}), "'arrow' / 'arrows'"))
	{
		if (!MONEY_ADD(TP, -144))
		{
			command("say You need coins to pay me.  One gold.");
			return 1;
		}

		write("You pay the bowyer a gold coin.\n");
		say(QCTNAME(TP) + " pays the bowyer a gold coin.\n");

		purchase = clone_object(MY_ARROWS);
		purchase->move(TO);

		who_purch = TP->query_real_name();

		if (!command("give arrows to " + who_purch))
			command("drop arrows");

		return 1;
	}

	if (parse_command(str, ({}), "[bow] 'string' / 'strings' / 'bowstring' / 'bowstrings'"))
	{
		if (!MONEY_ADD(TP, -36))
		{
			command("say You need coins to pay me.  Three silver.");
			return 1;
		}

		write("You pay the bowyer three silver coins.\n");
		say(QCTNAME(TP) + " pays the bowyer three silver coins.\n");

		purchase = clone_object(MY_BOWSTRING);
		purchase->move(TO);

		who_purch = TP->query_real_name();

		if (!command("give bowstring to " + who_purch))
			command("drop bowstring");

		return 1;
	}

	if (parse_command(str, ({}), "'quiver' / 'quivers'"))
	{
		if (!MONEY_ADD(TP, -288))
		{
			command("say You need coins to pay me.  Two gold.");
			return 1;
		}

		write("You pay the bowyer two gold coins.\n");
		say(QCTNAME(TP) + " pays the bowyer two gold coins.\n");

		purchase = clone_object(MY_QUIVER);
		purchase->move(TO);

		who_purch = TP->query_real_name();

		if (!command("give quiver to " + who_purch))
			command("drop quiver");

		return 1;
	}

	return 0;
}

int
collect(string str)
{
    object weapon;
	if (alrm)
	{
		command("asay gruffly I am preparing a bow.  Wait.");
		return 1;
	}

    command("emote removes your bow from a rack upon the wall.");
    command("emote bows saying:  Your bow, master.");
    weapon = stock[TP->query_real_name()];
    alrm = set_alarm(2.0,0.0,"give_out_weapon",TP->query_real_name(),
             weapon, 1);
    return 1;
}
/*
 * returns an array: ({ style1, style2, weapon })
 */
mapping compute_all_necessary_weapon_data(string *argdata)
{
	int i, j, k;
	string wepcomp = argdata[2];
	mapping order;
	order = (["type":0,"style1":"","style2":"","weapon":""]);

	for(i=0,j=sizeof(weapon_desc);i<j;i++)
	{
		k = member_array(argdata[i],bow_desc_values[weapon_desc[i]]);
		if (k == -1)
		{
			command("say Sorry, but " + argdata[i] + " is not an "
			+ "available " + weapon_desc[i] + " choice for a " + wepcomp
			+ ".");
			return (["type":0]); // invalid weapon
		}
		order[weapon_desc[i]] = bow_desc_values[weapon_desc[i]][k];
	}
	order["type"] = 1;

	return order;
}

void
give_out_weapon(string who_name, object weapon, int flag)
{
	int price;
	object who;
	string what_is_it = weapon->short();
	string wepprice = weapon->query_name();

	if (what_is_it == 0)
	{
		what_is_it = "weapon";
	}

	if (who_name)
		who = find_player(who_name);

	if (!who || E(TO) != E(who))
	{
		if (flag)
			command("asay gruffly Some customers are too impatient to pick up "
			+ "their " + what_is_it + ".");
		else
			command("asay gruffly Some customers are too impatient to see the "
			+ "completion of their " + what_is_it + ".");

		command("emote grunts gruffly from beneath his hood.");

		if (weapon)
        {
			if (flag)
				command("emote places " + what_is_it + " on a rack upon the "
				+ "wall to be collected later.");
			else
			{
				command("emote places " + what_is_it + " on a rack upon the "
				+ "wall to be collected later.");
				stock += ([ who_name:weapon ]);
			}
        }
		command("asay gruffly Sometimes human cities are less than "
		+ "civilized.");
		alrm = 0;
		return;
	}

	if (!weapon)
	{
		if (flag)
			command("asay gruffly I don't remember an order for a "
			+ what_is_it + " placed by you.");
		else
			command("asay gruffly Sorry, something went wrong with your "
			+ "order.");

		command("emote snorts gruffly");
		alrm = 0;
		return;
	}
	weapon->move(TO);
	command("asay gruffly Your " + what_is_it + ".");
	command("emote snorts from beneath his hood.");
    alrm = 0;

	price = 1152;
	
	if (!MONEY_ADD(who, -price))
	{
		command("say Come back when you have enough to pay.");
		command("say Your " + what_is_it + " will be here for you until "
		+ "then.");
		command("emote places " + what_is_it + " on a rack upon the wall.");
		weapon->move(VOID);
		stock += ([ who_name:weapon ]);
		return;
	}
    who->catch_msg("You pay the bowyer " + price + " copper coins.\n");

    weapon->remove_shadow();

	if (!command("give " + weapon->query_name() + " to " + who_name))
		command("drop " + weapon->query_name());

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
		command("asay gruffly I am preparing a bow.  Wait.");
		return 1;
	}

    NF(C(query_verb()) + " what?\n");

	if (!str)
		return 0;

	if (stock[TP->query_real_name()])
	{
		  NF("There is already a weapon in stock for you.  "
		  + "Collect it first.\n");
		  return 0;
	}

    /* syntax is: 'order <style1> <style2> <weapon>' */
	argdata = explode(str," ");

    NF(C(query_verb()) + " <style1> <style2> <weapon>.\n");

    if(sizeof(argdata) != 3)
	{ return 0; }

	my_order = compute_all_necessary_weapon_data(argdata);

    if (my_order["type"])
	{
		alrm = set_alarm(7.0, 0.0, "finished_weapon",
		TP->query_real_name(), my_order["style1"],
		my_order["style2"], my_order["weapon"]);
		write("You place your order.\n");
		say(QCTNAME(TP) + " orders a weapon.\n");

		command("asay gruffly I will prepare your bow now.  If you aren't "
		+ "here when I finish, return later and <collect> it.");

		add_prop(TSIT, 1);
		add_prop(LIVE_S_EXTRA_SHORT," is preparing an impressive "
		+ argdata[0] + " " + argdata[1] + " " + argdata[2]);

		set_alarm(3.0, 0.0, "prep_bow", argdata[0], argdata[1], argdata[2]);

      return 1;
	}
    NF("You failed to order a valid bow type.  Read the sign again for "
	+ "valid bow choices.\n");
    return 0;
}

void
finished_weapon(string for_who, string sty1, string sty2, string wep)
{
	object weapon = clone_object(MY_BOW);
    weapon->set_weapon_data(sty1 + "&&"
							+ sty2 + "&&"
							+ wep);

	remove_prop(TSIT);
	remove_prop(LIVE_S_EXTRA_SHORT);

    give_out_weapon(for_who, weapon, 0);
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

string prep_bow(string sty1, string sty2, string wep)
{
	command("emote takes a " + sty1 + " " + sty2 + " " + wep + " off a rack "
	+ "on the north wall, prepares it, and strings it.");
	return "";
}

int
special_attack(object enemy)
{
    int pen, wloc, elec_resist;
    string hitloc, how, how2;
    mixed hitres;

    if (!sizeof(query_weapon(-1)))
		return 0;

    if (random(5) == 1)
    {
		pen = 325 + random(275);
		wloc = one_of_list(({A_HEAD, A_TORSO, A_LEGS, A_R_ARM, A_L_ARM}));
		
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
		
		elec_resist = enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY);
		elec_resist = 100 - elec_resist;
		pen = pen / 100 * elec_resist;

		hitres = enemy->hit_me(pen, MAGIC_DT, TO, -1, wloc);

		switch (hitres[0])
		{
			case -1..0:
				how = "but misses.\nThe arrow explodes behind you in a "
				+ "dazzling flash of blue light";
				how2 = "but misses.\nThe arrow explodes behind " +
				HIM(enemy) + " in a dazzling flash of blue light";
				break;
			case 1..9:
				how = "which explodes in a dazzling flash of blue light "
				+ "as it grazes you, sending a buzz through your " + hitloc;
				how2 = "which explodes in a dazzling flash of blue light "
				+ "as it grazes " + HIM(enemy) + "\n" + QCTNAME(enemy)
				+ "'s " + hitloc + " vibrates visibly";
				break;
			case 10..14:
				how = "sending blackened blood flying as it impacts and "
				+ "arcs into pure lightning coursing through your body";
				how2 = "sending blackened blood flying as it impacts and "
				+ "arcs into pure lightning coursing through "
				+ HIS(enemy) + " body";
				break;
			case 15..26:
				how = "numbing it completely as blackened blood spurts "
				+ "out and the arrow explodes into pure lightning "
				+ "coursing through your body and numbing your " + hitloc;
				how2 = "sending blackened blood spurting as it impacts "
				+ "and explodes into pure lightning.\n" + QCTNAME(enemy)
				+ "'s " + hitloc + " trembles and vibrates visibly";
				break;
			case 27..90:
				how = "and ruptures into an arcing explosion of pure, "
				+ "blue lightning knocking you back stunned and in "
				+ "blinding pain";
				how2 = "and ruptures into an arcing explosion of pure, "
				+ "blue lightning knocking " + HIM(enemy) + " back stunned "
				+ "and in obvious pain.\n" + QCTNAME(enemy) + " stumbles "
				+ "forward blindly, " + HIS(enemy) + " entire body vibrating "
				+ "visibly";
				break;
			default:
				how = "and nearly blows it to bits as blackened blood "
				+ "sprays everywhere.\nYou go blind momentarily as you "
				+ "feel death coming for you";
				how2 = "and nearly blows it to bits as blackened blood "
				+ "sprays everywhere.\n" + QCTNAME(enemy) + " shudders, "
				+ HIS(enemy) + " eyes rolling back in " + HIS(enemy)
				+ " head as blue lightning arcs and crackles across "
				+ HIS(enemy) + " entire body";
				break;
		}

		enemy->catch_msg(QCTNAME(TO) + " fires a crackling, lightning-"
		+ "imbued arrow at your " + hitloc + " " + how + ".\n");
		tell_room(E(TO), QCTNAME(TO) + " fires a crackling, lightning-"
		+ "imbued arrow at " + QTNAME(enemy) + "'s " + hitloc + " "
		+ how2 + ".\n", ({enemy, TO}));

		if (enemy->query_hp() <= 0)
			enemy->do_die(TO);

		return 1;
    }

    return 0;
}
