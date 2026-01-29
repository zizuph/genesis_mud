/* 
 * Leader of the Brix gang in his hq in the back
 * alleys of Jems Court in the Aesthetics quarter
 * of Palanthas.
 *
 * Mortis 05.2006
 *
 * Still needs heal potion for pack.  Have potion randomly
 * appear in one of three packs.  That way a thief will have
 * to try more often to get it and risk getting caught and
 * kicked out the window.
 */

#include "../../local.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#define MY_HOME			MONKS + "brix_kirk_hq"
#define OUT_WINDOW		MONKS + "alley055"

inherit BRIX_GANGER;
inherit "/lib/unique";

/*prototype*/
void arm_me();
int dsheathe_knife();
int special_attack1(object enemy);
int special_attack2(object enemy);
int special_attack3(object enemy);
int special_attack4(object enemy);
int special_attack5(object enemy);
string cact_it();

int knife_out = 0;
object kirk_knife, kirk_sword, kirk_axe, kirk_club, kirk_polearm;
object myhome = find_object(MY_HOME);

void
create_brix_ganger()
{
    seteuid(getuid(TO));

	set_name("kirk");
	add_name(({"_brix_ganger", "ganger", "gangster", "hoodlum"}));
	set_adj("boyish");
	add_adj(({"boyishly", "good-looking", "athletic"}));
	set_gender(G_MALE);
	set_short("boyishly good-looking athletic male human");
	set_long("Possessing an athletically built body with a stout chest, "
	+ "round biceps, and strong legs, this man is undoubtedly naturally "
	+ "gifted.  A lock of sandy blond hair curls down over his forehead "
	+ "between his blue eyes, and his chiseled cheeks accentuate his "
	+ "disarming smile.  He bears no visible scars, unusual for anyone "
	+ "in this neighborhood, and walks with a confident step among his "
	+ "hoodlums who appear to admire his every move.\n"
	+ "He has a tattoo of a curving sword pointing down across a circle "
	+ "containing a war galleon on his right bicep.\n");
	set_race_name("human");
	set_living_name("kirk");
	set_title("the Alley King of Jems Court and Leader of the Brix");
	
	set_size_descs("of normal length", "of normal width");
	set_appearance(7);

	set_all_hitloc_unarmed(35);
	set_all_attack_unarmed(18, 28);

	set_skill(SS_DEFENCE,      88);
	set_skill(SS_PARRY,        75);
	set_skill(SS_2H_COMBAT,    60);
	set_skill(SS_UNARM_COMBAT, 95);
	set_skill(SS_AWARENESS,    60);
	set_skill(SS_WEP_CLUB,     85);
	set_skill(SS_WEP_AXE,      85);
	set_skill(SS_WEP_SWORD,    85);
	set_skill(SS_WEP_POLEARM,  85);
	set_skill(SS_WEP_KNIFE,    85);
    set_skill(SS_BLIND_COMBAT, 75);

	set_stats((({150, 145, 200, 145, 175, 145})), 2);

	set_alignment(-725);
	set_knight_prestige(50);

	set_introduce(1);

	add_prop(OBJ_I_RES_ELECTRICITY, 33);
	add_prop(OBJ_I_RES_DEATH, 40);
	add_prop(OBJ_I_RES_FIRE, 10);
	add_prop(OBJ_I_RES_WATER, 10);
	add_prop(OBJ_I_RES_MAGIC, 15);


    set_default_answer("@@def_answer");

	add_ask(({"palanthas", "city"}), "asay smil Palanthas is great?  "
	+ "Palanthas is... safe?  It is!  Thanks to the Brix... thanks... to "
	+ "me.  That's right.", 1);
	add_ask(({"chief", "constable", "hagen"}), "asay aci Hagen?  Ol'red "
	+ "doesn't show his face on my court.  Not... anymore.", 1);
	add_ask(({"brix", "gang", "gangs", "hoodlum", "hoodlums", "ganger",
		"gangers"}), "asay proud I... own Jems Court.  The Brix own Jems "
	+ "court, see?  We look out for our own and provide protection.  No one "
	+ "missteps here, or we... deal with them.  I... deal with them.", 1);
	add_ask(({"brick", "bricks"}), "asay remin We started with nothing... "
	+ "nothing but the streets.  So we made them our weapons... we made them"
	+ "... our weapons.  Now we have it all.  We... have it all.", 1);
	add_ask(({"leader", "kirk"}), "asay conf I'm the leader here.  I'm... "
	+ "the king... of Jems Court, and I earned it too, mister.", 1);
	add_ask(({"gamble", "gambling", "dice", "onjat", "game"}), "asay secret "
	+ "Yeah, we run a little game of onjat down through the tunnel, "
	+ "but you better not try your hand there if you're spoiling for "
	+ "trouble.  You won't -walk- back out.", 1);
	add_ask(({"monk", "monks", "aesthetic", "aesthetics"}), "asay amus I "
	+ "don't mind the scroll heads coming down here for a game every once "
	+ "in a while provided they don't cause trouble... not on my court.", 1);

	set_act_time(60);
	add_act("get it");
	add_act("emote grins with boyish charm and so much confidence even you "
	+ "believe he's unstoppable.");
	add_act("smile disarm");
	add_act("asay inq Who has an ale?");
	add_act("asay gre Oh, yes.  Onjat revenues are... up, you could say.");
	add_act("asay grave Last time I saw someone pull that, they dragged "
	+ "him out of the tunnel...  one sackfull at a time.");
	add_act("emote tosses an old, red brick up in the air a few times, "
	+ "catching it easily in his hand each time.");
	add_act("asay ang Gambling?  Who the frung said anything about... "
	+ "gambling, mister?");

	set_cact_time(1);
	add_cact(cact_it);

	set_alarm(1.0, 0.0, arm_me);
	set_alarm(3.0, 0.0, cact_it);
}

string
def_answer()
{
	if (TP->query_gender() == G_FEMALE)
	{
		string whofem = QNAME(TP);

		command("emote throws his head back and laughs cheerfully.");
		command("asay suave Don't worry your pretty head about that.");
		command("smile endear " + whofem);
		command("asay soft We have all the time in the world to talk... "
		+ "afterwards.");
		return "";
	}

	command("say Take your questions and get off my ship, Mister.  "
	+ one_of_list(({"The Brix don't care a whit for that.", "Now get lost.  "
	+ "This is my court.", "Don't mess with the Brix unless you like getting "
	+ "smashed.", "You ask too many questions."})));
	return "";
}

/* Ddraw/dsheathe knife
 * Whip out axe
 * Whip out club
 * Whip out polearm
 * Whip out sword
 * Drink healing potion
 * Default:  Unarmed
 */
string
cact_it()
{
//  command("say cacting");

  switch (random(10))
  {
	case 0:	// Ddraw/dsheathe knife
		if (knife_out == 1)
		{
			command("emote spins around in an agile circle swiping his "
			+ "black-handled grensh knife at your throat.");
			return "";
		}

		if (!kirk_polearm)
		{
			knife_out = 1;
			command("ddraw from thigh-sheath");
			command("asay clev When you enter the alleys, you... take your "
			+ "life into your own hands.");
			set_alarm(20.0, 0.0, "dsheathe_knife");
			return "";
		}
		break;
	case 1:	// Whip out axe
		if (kirk_axe)
			return "";

		if (kirk_polearm)
		{
			if (command("unwield all"))
				command("emote stows his polearm in his rucksack.");

			kirk_polearm->remove_object();
		}
		if (kirk_sword)
		{
			if (command("unwield sword"))
				command("emote stows his sword in his rucksack.");

			kirk_sword->remove_object();
		}
		if (kirk_club)
		{
			if (command("unwield club"))
				command("emote stows his club in his rucksack.");

			kirk_club->remove_object();
		}
			
		kirk_axe = clone_unique(MONKS + "arms/brix_axe_kirk", 3,
			MONKS + "arms/brix_axe_mid", 1, 100);
		kirk_axe->move(TO);

		if (command("wield axe"))
			command("emote whips an axe out of his rucksack and "
			+ "wields it.");
		break;
	case 2: // Whip out club
		if (kirk_club)
			return "";

		if (kirk_polearm)
		{
			if (command("unwield all"))
				command("emote stows his polearm in his rucksack.");

			kirk_polearm->remove_object();
		}
		if (kirk_sword)
		{
			if (command("unwield sword"))
				command("emote stows his sword in his rucksack.");

			kirk_sword->remove_object();
		}
		if (kirk_axe)
		{
			if (command("unwield axe"))
				command("emote stows his axe in his rucksack.");

			kirk_axe->remove_object();
		}
			
		kirk_club = clone_unique(MONKS + "arms/brix_club_kirk", 3,
			MONKS + "arms/brix_club_mid", 1, 100);
		kirk_club->move(TO);

		if (command("wield chain"))
			command("emote whips a chain out of his rucksack and "
			+ "wields it.");

		if (command("wield board"))
			command("emote whips a board with nails out of his rucksack "
			+ "and wields it.");
		break;
	case 3: // Whip out polearm
		if (kirk_polearm)
			return "";

		if (knife_out == 1)
			dsheathe_knife();

		if (kirk_sword)
		{
			if (command("unwield sword"))
				command("emote stows his sword in his rucksack.");

			kirk_sword->remove_object();
		}
		if (kirk_axe)
		{
			if (command("unwield axe"))
				command("emote stows his axe in his rucksack.");

			kirk_axe->remove_object();
		}
		if (kirk_club)
		{
			if (command("unwield club"))
				command("emote stows his club in his rucksack.");

			kirk_club->remove_object();
		}
			
		kirk_polearm = clone_unique(MONKS + "arms/brix_polearm_kirk", 3,
			OBJ + "gwep_polearm", 1, 100);
		kirk_polearm->move(TO);

		if (command("wield weapon"))
			command("emote whips a polearm out of his rucksack and "
			+ "wields it.");
		
		break;
	case 4: // Whip out sword
		if (kirk_sword)
			return "";

		if (kirk_polearm)
		{
			if (command("unwield all"))
				command("emote stows his polearm in his rucksack.");

			kirk_polearm->remove_object();
		}
		if (kirk_club)
		{
			if (command("unwield club"))
				command("emote stows his club in his rucksack.");

			kirk_club->remove_object();
		}
		if (kirk_axe)
		{
			if (command("unwield axe"))
				command("emote stows his axe in his rucksack.");

			kirk_axe->remove_object();
		}
			
		kirk_sword = clone_object(MONKS + "arms/brix_sword_kirk");
		kirk_sword->move(TO);

		if (command("wield sword"))
			command("emote whips a sword out of his rucksack and "
			+ "wields it.");

		break;
	case 5: // Drink healing potion
		command("emote reaches into his flat black leather belt-pouch, pulls "
		+ "out a long vial, pops its cork with his thumb, and throws back "
		+ "the lumpy green liquid within.");
		command("emote goes, \"Glug, glug, glug... ahhhhh!\"");
		TO->heal_hp(500);
		break;
	default: // Go unarmed
		if (knife_out == 1)
			dsheathe_knife();

		if (kirk_polearm)
		{
			if (command("unwield all"))
				command("emote stows his polearm in his rucksack.");

			kirk_polearm->remove_object();
		}
		if (kirk_sword)
		{
			if (command("unwield sword"))
				command("emote stows his sword in his rucksack.");

			kirk_sword->remove_object();
		}
		if (kirk_axe)
		{
			if (command("unwield axe"))
				command("emote stows his axe in his rucksack.");

			kirk_axe->remove_object();
		}
		if (kirk_club)
		{
			if (command("unwield club"))
				command("emote stows his club in his rucksack.");

			kirk_club->remove_object();
		}
			
		command("asay devil Let's see how you are at fisticuffs, mister.  "
		+ "Though you should know... I... scored first in my class... in "
		+ "the martial arts.");
		break;
  }
  return "";
}

int
dsheathe_knife()
{
	if (!present("knife", TO))
	{
		knife_out = 0;
		command("asay confid Keep the knife, you fool... keep it, and I'll... "
		+ "take it off your shattered corpse.");
		return 1;
	}

	if (command("dsheathe knife in thigh-sheath"))
	{
		knife_out = 0;
		command("wink it");
		return 1;
	}
}

void
arm_me()
{
	object wpants, wshirt, wshoes, wbelt, wsheath, wpouch;

	wshirt = clone_object(NOBLE + "arms/parmour");
	wshirt->set_armour_data("Kirk" + "&&"
							+ "light" + "&&"
							+ "forest-green" + "&&"
							+ "hemp" + "&&"
							+ "sleeveless-shirt");
	wshirt->set_condition(1);
	wshirt->move(TO);

	wshoes = clone_object(MONKS + "arms/lurr_shoes");
	wshoes->set_footwear_data("glistening" + "&&" + "black" + "&&"
							  + "hard" + "&&" + "boots");
	wshoes->move(TO);

	wsheath = clone_object(MERCH + "obj/lgeneral");
	wsheath->set_general_data("glistening" + "&&"
						   + "black" + "&&"
						   + "hard" + "&&"
						   + "thigh-sheath");
	wsheath->move(TO);

	wpants = clone_object(NOBLE + "arms/parmour");
	wpants->set_armour_data("Kirk" + "&&"
							+ "jaunty" + "&&"
							+ "black" + "&&"
							+ "dupion" + "&&"
							+ "pantaloons");
	wpants->move(TO);

	wpouch = clone_object(MERCH + "obj/lgeneral");
	wpouch->set_general_data("flat" + "&&"
						   + "black" + "&&"
						   + "leather" + "&&"
						   + "belt-pouch");
	wpouch->move(TO);

	wbelt = clone_object(MERCH + "arms/larmour");
	wbelt->set_armour_data("glistening" + "&&"
						   + "black" + "&&"
						   + "hard" + "&&"
						   + "belt");
	wbelt->move(TO);

	kirk_knife = clone_unique(MONKS + "arms/brix_knife_kirk", 3,
		MONKS + "arms/brix_knife_low", 1, 80);
	kirk_knife->move(TO);

	MONEY_MAKE_GC(18 + random(13))->move(TO);
	MONEY_MAKE_SC(40 + random(60))->move(TO);

	command("put coins in pouch");
	command("close pouch");
	command("dsheathe knife in thigh-sheath");
	command("wear all");
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

	if (ob->query_gender() == G_FEMALE)
	{
		command("chuckle calm");
		command("asay amus I can think of... several more enjoyable ways "
		+ "we could... resolve this.");
	}

	else
	{
		command("smirk");
		command("asay conf You picked the wrong king to tangle with, mister.");
	}
}

/* Special attacks:
 * 1 Neck/shoulder chop			 0..4
 * 2 Double fisted backhand		 5..9
 * 3 Judo flip					10..14
 * 4 Flying drop kick			15..17
 * 5 Double handled axe punch	18..19
 */
int
special_attack(object enemy)
{
    int pen, att, wloc, damtype;
    string hitloc, attack, how, how2;
    mixed hitres;

	if (random(6) == 1)	// Specials only go off if 1.
		return 0;

	switch (random(20))
	{
		case 0..4:
			special_attack1(enemy);
			break;
		case 5..9:
			special_attack2(enemy);
			break;
		case 10..14:
			special_attack3(enemy);
			break;
		case 15..17:
			special_attack4(enemy);
			break;
		case 18..19:
			special_attack5(enemy);
			break;
		default:
			return 0;
			break;
	}

    return 0;
}

int
special_attack1(object enemy)	// Neck/shoulder chop -- Fatigue
{
	int pen, damtype = W_BLUDGEON, kfatigue = 0, wloc = A_NECK;
	string how, how2, stunmsg, where = "neck";
	mixed hitres;
		
	if (random(2) == 1)
	{
		wloc = A_ARMS;
		where = "shoulder";
	}
	pen = 225 + random(76);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	switch (hitres[0])
	{
		case -1..0:
			how = "with expert precision but misses";
			how2 = how;
			stunmsg = "with a feeling of relief";
			break;

		case 1..6:
			how = "landing with expert accuracy";
			how2 = how;
			kfatigue = hitres[0];
			stunmsg = "weakened";
			break;

		case 7..14:
			how = "landing with the force of a crowbar";
			how2 = how;
			kfatigue = hitres[0];
			stunmsg = "weakened";
			break;

		case 15..30:
			how = "and lands with a spine deadening \"Crack\"";
			how2 = how;
			kfatigue = hitres[0];
			stunmsg = "weakened";
			if (kfatigue > 25)
			{
				kfatigue = 25;
				stunmsg = "weakened and reeling";
			}
			break;

		case 31..49:
			how = "and lands with a spine deadening \"CRACK\"";
			how2 = how;
			kfatigue = 25;
			stunmsg = "weakened and reeling";
			break;

		default:
			how = "nearly crushing your " + where + " with a spine "
			+ "deadening \"CRACK\"";
			how2 = "nearly crushing " + HIS(enemy) + " " + where + " with "
			+ "a spine deadening \"CRACK\"";
			kfatigue = 25;
			stunmsg = "weakened, reeling, and on the verge of collapse";
			break;
	}

	enemy->add_fatigue(-kfatigue);

	enemy->catch_msg(QCTNAME(TO) + " aims an open-hand chop at your "
	+ where + " " + how + " leaving you " + stunmsg + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " aims an open-hand chop at "
	+ QTNAME(enemy) + "'s " + where + " " + how2 + " leaving " + HIM(enemy)
	+ " " + stunmsg + ".\n", ({enemy, TO}));

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}

int
special_attack2(object enemy)	// Double fisted backhand -- Mental drain
{
	int pen, damtype = W_BLUDGEON, kmanadrain = 0, wloc = A_HEAD;
	string how, how2, stunmsg, where = one_of_list(({"right", "left"}))
	+ " cheek";
	mixed hitres;
		
	pen = 250 + random(101);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	switch (hitres[0])
	{
		case -1..0:
			how = "with expert precision but misses";
			how2 = how;
			stunmsg = "with a feeling of relief";
			break;

		case 1..6:
			how = "landing with uncanny accuracy";
			how2 = how;
			kmanadrain = hitres[0];
			stunmsg = "woozy";
			break;

		case 7..14:
			how = "landing with the force of three fists";
			how2 = how;
			kmanadrain = hitres[0];
			stunmsg = "woozy";
			break;

		case 15..30:
			how = "and lands with a mind deadening \"Thwack\"";
			how2 = how;
			kmanadrain = hitres[0];
			stunmsg = "woozy";
			if (kmanadrain > 25)
			{
				kmanadrain = 25;
				stunmsg = "woozy and dazed";
			}
			break;

		case 31..49:
			how = "and lands with a spine deadening \"THWACK\"";
			how2 = how;
			kmanadrain = 25;
			stunmsg = "woozy and dazed";
			break;

		default:
			how = "nearly crushing your skull with a mind deadening "
			+ "\"THWACK\"";
			how2 = "nearly crushing " + HIS(enemy) + " skull with a mind "
			+ "deadening \"THWACK\"";
			kmanadrain = 25;
			stunmsg = "woozy, dazed, and on the verge of unconsciousness";
			break;
	}

	enemy->add_mana(-kmanadrain);

	enemy->catch_msg(QCTNAME(TO) + " swings a double-fisted backhand at your "
	+ where + " " + how + " leaving you " + stunmsg + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " swings a double-fisted backhand at "
	+ QTNAME(enemy) + "'s " + where + " " + how2 + " leaving " + HIM(enemy)
	+ " " + stunmsg + ".\n", ({enemy, TO}));

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}

int
special_attack3(object enemy)	// Judo-flip
{
	int pen, damtype = W_BLUDGEON, wloc = A_TORSO;
	string how, where = one_of_list(({"left", "right"}));
	mixed hitres;
		
	pen = 225 + random(76);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	switch (hitres[0])
	{
		case -1..0:
			how = "";
			break;

		case 1..6:
			how = "heavy ";
			break;

		case 7..14:
			how = "resoundingly heavy ";
			break;

		case 15..30:
			how = "bone breaking ";
			break;

		case 31..49:
			how = "resounding, bone crunching ";
			break;

		default:
			how = "deafening, bone shattering ";
			break;
	}

	enemy->catch_msg(QCTNAME(TO) + " grabs your " + where + " arm, spins, "
	+ "and hurls you over his back high into the air.\n"
	+ "You land with a " + how + "thud on your back.\n");
	
	tell_room(E(TO), QCTNAME(TO) + " grabs " + QTNAME(enemy) + "'s " + where
	+ " arm, spins, and hurls " + HIM(enemy) + " over his back high into the "
	+ "air.\n" + QCTNAME(enemy) + " lands with a " + how + "thud on "
	+ HIS(enemy) + " back.\n", ({enemy, TO}));

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}

int
special_attack4(object enemy)	// Flying drop kick -- Ejection from room
{
	int pen, damtype = W_BLUDGEON, kkicked = 0, wloc = A_TORSO;
	string how, how2, where;
	mixed hitres;

	pen = 300 + random(201);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	switch (hitres[0])
	{
		case -1..0:
			how = "as he flies past barely missing and rolls back to his feet "
			+ "adeptly";
			how2 = how;
			break;

		case 1..6:
			how = "as he drop kicks you thuddingly across the room";
			how2 = "as he drop kicks " + HIM(enemy) + " thuddingly "
			+ "across the room";
			break;

		case 7..14:
			how = "and slamming into you with rampant force";
			how2 = "and slamming into " + HIM(enemy) + " with rampant "
			+ "force";
			kkicked = 1;
			break;

		case 15..30:
			how = "and drop kicking you with rampant force, knocking the "
			+ "wind out of your lungs";
			how2 = "an drop kicking " + HIM(enemy) + " with rampant "
			+ "force, knocking the wind out of " + HIS(enemy) + " lungs";
			kkicked = 1;
			break;

		case 31..49:
			how = "as he drop kicks you with bone crushing force, knocking "
			+ "the wind out of your lungs";
			how2 = "as he drop kicks " + HIM(enemy) + " with bone "
			+ "crushing force, knocking the wind out of " + HIS(enemy)
			+ "lungs";
			kkicked = 1;
			break;

		default:
			how = "with a deadly force rarely wielded by mortals as he drop "
			+ "kicks you to Lars";
			how2 = "with a deadly force rarely wielded by mortals as he "
			+ "drop kicks " + HIM(enemy) + " to Lars";
			kkicked = 1;
			break;
	}

	enemy->catch_msg(QCTNAME(TO) + " leaps into the air suddenly, aiming "
	+ "both feet at your chest " + how + ".\n");
	
	tell_room(E(TO), QCTNAME(TO) + " leaps into the air suddenly, aiming "
	+ "both feet at " + QCTNAME(enemy) + "'s chest " + how2 + ".\n",
		({enemy, TO}));

	if (E(TO) == myhome)
	{
	  if (enemy->query_skill(SS_UNARM_COMBAT) < 35 && kkicked == 1)
	  {
		switch (random(4))
		{
			case 0:
				where = "head";
				wloc = A_HEAD;
				break;
			case 1:
				where = "body";
				wloc = A_TORSO;
				break;
			case 2:
				where = one_of_list(({"right arm", "left arm"}));
				wloc = A_ARMS;
				break;
			case 3:
				where = "legs";
				wloc = A_LEGS;
				break;
			default:
				where = "nuglek";
				wloc = A_TORSO;
				break;
		}
		
		pen = 120 - enemy->query_skill(SS_ACROBAT) * 4 + random(100);

		if (pen > 0)
		{
			enemy->catch_msg("\nYou crash through a window as you go flying "
			+ "through the air slamming onto the bricks of the alley below "
			+ "as you land on your " + where + " and go tumbling through the "
			+ "trash and litter.\n\n");
		
			tell_room(myhome, QCTNAME(enemy) + " crashes through the window "
			+ "in the west wall as " + HE(enemy) + " goes flying through "
			+ "the air and slams into the bricks of the alley below as "
			+ HE(enemy) + " lands on " + HIS(enemy) + " " + where + " and "
			+ "goes tumbling through the trash and litter.\n", ({enemy, TO}));

			enemy->hit_me(pen, damtype, TO, -1, wloc);
		}

		else
		{
			enemy->catch_msg("\nYou crash through a window as you go flying "
			+ "through the air, acrobatically flipping yourself upright just "
			+ "in time to land on your feet in the alley below.\n\n");
		
			tell_room(myhome, QCTNAME(enemy) + " crashes through the window "
			+ "in the west wall as " + HE(enemy) + " goes flying through "
			+ "the air, acrobatically flipping " + HIMSELF(enemy) + " upright "
			+ "just in time to land on " + HIS(enemy) + " feet in the alley "
			+ "below.\n", ({enemy, TO}));
		}

		enemy->move_living("sailing out the window", OUT_WINDOW, 1, 0);

	  }
	}

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}

int
special_attack5(object enemy)	// Double handled axe punch
{
	int pen, damtype = W_BLUDGEON, wloc = A_TORSO;
	mixed hitres;
		
	pen = 350 + random(611);
	hitres = enemy->hit_me(pen, damtype, TO, -1, wloc);

	switch (hitres[0])
	{
		case -1..30:
			enemy->catch_msg(QCTNAME(TO) + " gutkicks you, doubling you over "
			+ "as he nearly crushes your back with his double handled axe "
			+ "drop!\n");
			
			tell_room(E(TO), QCTNAME(TO) + " gutkicks " + QTNAME(enemy) + ", "
			+ "doubling " + HIM(enemy) + " over as he nearly crushes "
			+ HIS(enemy) + " back with his double handled axe drop!\n",
				({enemy, TO}));
			break;

		default:
			enemy->catch_msg(QCTNAME(TO) + " gutkicks you sickeningly, "
			+ "doubling you over as he leaps off the wall and shatters the "
			+ "meat and bone of your back with an unstoppable double handled "
			+ "axe drop!\n");
			
			tell_room(E(TO), QCTNAME(TO) + " gutkicks "  + QTNAME(enemy)
			+ "sickeningly, doubling " + HIM(enemy) + " over as he leaps off "
			+ "the wall and shatters the meat and bone of " + HIS(enemy)
			+ " back with an unstoppable double handled axe drop!\n",
				({enemy, TO}));
			break;
	}

	if (enemy->query_hp() <= 0)
		enemy->do_die(TO);

	return 1;
}
