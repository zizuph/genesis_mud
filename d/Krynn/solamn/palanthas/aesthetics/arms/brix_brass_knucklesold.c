/* 
 * Brass knuckles used by lowly Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming
 * gloves found on Lyden in Tyr.
 *
 * On a successful hit with either hand that does more
 * than 25 points of damage, the knuckles will inflict
 * bonus bludgeoning damage.
 *
 * Cannot be worn with shields.  Cannot hold or wield
 * while wearing knuckles.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include "../../local.h"
#include <files.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <macros.h>

#define KNUCKLES_SHADOW (MONKS + "arms/brixx_brass_knuckles_sh")

void
create_armour()
{
	seteuid(getuid());

	set_name("knuckles");
	set_pname("knuckles");

	set_adj("brass");
	add_adj("pair of");

	set_short("pair of brass knuckles");
	set_pshort("pairs of brass knuckles");

	set_at(A_HANDS);
	set_ac(3);
	set_am(({1, -2, 1}));
	set_af(TO);

	LONG("Worn on the middle two fingers of each hand with a palm bar "
	+ "for secure grasping, this pair of contoured brass knuckles stretches "
	+ "across the knuckles creating a punching surface capable of inflicting "
	+ "nasty damage.\n");

	add_prop(OBJ_I_VALUE,  144);
	add_prop(OBJ_I_WEIGHT, 550);
	add_prop(OBJ_I_VOLUME, 400);
}

/* Called when the knuckles are worn, this function
 * adds a shadow that takes care of some of the knuckles'
 * functionality.
 */
mixed
wear(object obj)
{
	if (TP->query_npc() == 1)
		return 0;

	object sh;

	if (TP->query_tool(W_BOTH) || TP->query_tool(W_RIGHT) ||
		TP->query_tool(W_LEFT))
		return "You must free your hands up completely in order to properly "
		+ "grip the brass knuckles.\n";

	if ((sh = clone_object(KNUCKLES_SHADOW)) && sh->shadow_me(TP))
	{
		sh->set_knuckles_ob(TO);
	}

	else
		sh->remove_shadow();

	return 0;
}    

/* Called when the knuckles are removed, this function
 * removes the knuckles shadow.
 */
int
remove(object obj)
{
	if (TP->query_npc() == 1)
		return 0;

    TP->remove_knuckles_shadow();
    return 0;
}

/* This is called from the knuckles shadow to do bludgeon damage
 * to opponents when a successful unarmed attack is made while
 * wearing the knuckles.
 */
int
special_damage(int aid, string hdesc, int phurt, object enemy, int phit, 
	int dam)
{
	int hurt, bludgeon_dmg, bonus_dmg, bonus_unarm, bonus_str;
	object wearer;
	string with, where, how, what, owhat, bludge;

    // Make sure we hit with the knuckles.
    if (!(aid))
		return 0;

	if (!(wearer = query_worn()))
		return 0;

	// Use higher of unarmed/str with a cap of 100.
	bonus_unarm = wearer->query_skill(SS_UNARM_COMBAT);
	bonus_str = wearer->query_stat(SS_STR);

	bonus_dmg = bonus_unarm;

	if (bonus_str > bonus_unarm)
		bonus_dmg = bonus_str;

	if (bonus_dmg > 100)
		bonus_dmg = 100;

	// Calculate damage.
	bludgeon_dmg = random(20 + bonus_dmg / 10);
	hurt = enemy->hit_me(bludgeon_dmg, W_BLUDGEON, wearer, -1)[2];

	if (hurt < 1)
		return 0;

	// Give an attack description.
	with = (aid == W_RIGHT ? "right hand" : "left hand");

	where = " the " + hdesc + " of ";

	switch (phurt)
	{
		case -1..2:
			how = "";
			what = "barely connect with";
			owhat = "barely connects with";
			break;
		case 3..7:
			how = "";
			what = "connect with";
			owhat = "connects with";
			break;
		case 8..14:
			how = "";
			what = "thuddingly connect with";
			owhat = "thuddingly connects with";
			break;
		case 15..25:
			how = "";
			what = "pummel";
			owhat = "pummels";
			break;
		case 26..37:
			how = "";
			what = "smackingly pummel";
			owhat = "smackingly pummels";
			break;
		case 38..59:
			how = "";
			what = "knuckle-smash";
			owhat = "knuckle-smashes";
			break;
		case 60..95:
			how = " ruthlessly";
			what = "knuckle-smash";
			owhat = "knuckle-smashes";
//			where = " ";
			break;
		default:
			how = " brutally";
			what = "massacre";
			owhat = "massacres";
//			where = " ";
	}

	switch (hurt)
	{
		case 1..10:
			bludge = "bruising the flesh beneath";
			break;
		case 11..20:
			bludge = "shaking the bone beneath";
			break;
		case 21..35:
			bludge = "cracking the bone beneath";
			break;
		default:
			bludge = "cracking bone and rupturing flesh";
			break;
	}

	if (interactive(wearer))
		wearer->catch_tell("You " + what + where + enemy->query_the_name(wearer)
		+ how + " with your " + with + ", your brass knuckles "
		+ bludge + ".\n");
		// Original used enemy->query_the_name(wearer)

	if (interactive(enemy))
		enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
		" your " + hdesc + how + " with " + HIS(wearer) + " " + with + ", "
		+ HIS(wearer) + " brass knuckles " + bludge + ".\n");

	wearer->tell_watcher(QCTNAME(wearer) + " " + owhat + where + QTNAME(enemy)
	+ how + ", " + HIS(wearer) + " brass knuckles " + bludge + ".\n", enemy);

	return 1;
}

string
query_recover()
{
	return ::query_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
	init_keep_recover(arg);
	::init_recover(arg);
}
