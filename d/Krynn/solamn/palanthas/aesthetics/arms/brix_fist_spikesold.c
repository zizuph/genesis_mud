/* 
 * Fist spikes used by lowly Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming
 * gloves found on Lyden in Tyr.
 *
 * On a successful hit with either hand that does more
 * than 20 points of damage, the spikes will inflict
 * bonus impalation damage.
 *
 * Cannot be worn with shields.  Cannot hold or wield
 * while wearing spikes.
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

#define SPIKES_SHADOW (MONKS + "arms/brixx_fist_spikes_sh")

void
create_armour()
{
	seteuid(getuid());

	set_name("spikes");
	set_pname("spikes");

	set_adj("fist");
	add_adj("pair of");

	set_short("pair of fist spikes");
	set_pshort("pairs of fist spikes");

	set_at(A_HANDS);
	set_ac(3);
	set_am(({1, -2, 1}));
	set_af(TO);

	LONG("Worn on the middle two fingers of each hand with a palm bar "
	+ "for secure grasping, this pair of contoured iron knuckles stretches "
	+ "across the knuckles with four thick nail-like spikes creating a "
	+ "punching surface capable of inflicting nasty, piercing damage.\n");

	add_prop(OBJ_I_VALUE,  168);
	add_prop(OBJ_I_WEIGHT, 650);
	add_prop(OBJ_I_VOLUME, 525);
}

/* Called when the spikes are worn, this function
 * adds a shadow that takes care of some of the spikes'
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
		+ "grip the fist spikes.\n";

	if ((sh = clone_object(SPIKES_SHADOW)) && sh->shadow_me(TP))
	{
		sh->set_spikes_ob(TO);
	}

	else
		sh->remove_shadow();

	return 0;
}    

/* Called when the spikes are removed, this function
 * removes the spikes shadow.
 */
int
remove(object obj)
{
	if (TP->query_npc() == 1)
		return 0;

	TP->remove_spikes_shadow();
    return 0;
}

/* This is called from the spikes shadow to do impale damage
 * to opponents when a successful unarmed attack is made while
 * wearing the spikes.
 */
int
special_damage(int aid, string hdesc, int phurt, object enemy, int phit, 
	int dam)
{
	int hurt, impale_dmg, bonus_dmg, bonus_unarm, bonus_str;
	object wearer;
	string with, where, how, what, owhat, impaley;

    // Make sure we hit with the spikes.
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
	impale_dmg = random(22 + bonus_dmg / 9);
	hurt = enemy->hit_me(impale_dmg, W_IMPALE, wearer, -1)[2];

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
		case 1..9:
			impaley = "piercing the skin beneath";
			break;
		case 10..19:
			impaley = "impaling the flesh beneath";
			break;
		case 20..34:
			impaley = "impaling deeply into the flesh beneath";
			break;
		default:
			impaley = "impaling all the way into the flesh beneath";
			break;
	}

	if (interactive(wearer))
		wearer->catch_tell("You " + what + where + enemy->query_the_name(wearer)
		+ how + " with your " + with + ", your fist spikes "
		+ impaley + ".\n");
		// Original used enemy->query_the_name(wearer)

	if (interactive(enemy))
		enemy->catch_tell(wearer->query_The_name(enemy) + " " + owhat + 
		" your " + hdesc + how + " with " + HIS(wearer) + " " + with + ", "
		+ HIS(wearer) + " fist spikes " + impaley + ".\n");

	wearer->tell_watcher(QCTNAME(wearer) + " " + owhat + where + QTNAME(enemy)
	+ how + ", " + HIS(wearer) + " fist spikes " + impaley + ".\n", enemy);

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
