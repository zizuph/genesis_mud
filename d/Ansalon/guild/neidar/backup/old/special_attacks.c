/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define STAND_STRONG "_stand_strong_clan_special"

/* A global variable to hold the id for the alarm used for the special */
static private int chop_alarm = 0;

/* Prototypes */
void chop2(object target);

/*
 * Function name: can_attack_with_occ_special
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
can_attack_with_occ_special(object target, string attack)
{
    mixed why;
    object who = query_shadow_who();

    if (!target || !living(target) || !present(target, environment(who)))
    {
	return attack + " whom?\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
    {
	if(who->query_prop(STAND_STRONG))
	{
	    return "You are too focused on defending yourself, " +
	    "and can't do that.\n";
	}
	return "You are too stunned to " + attack + ".\n";
    }

    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
      stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
	return why;
    }
    else if (why)
    {
	return "You sense a force protecting " + 
	target->query_the_name(who) + ".\n";
    }

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
	/* A message should be given by query_not_attack_me(), so
	 * no need to specify one here.
	 */
	return "";
    }

    if ((!who->query_npc()) && (who->query_met(target)) &&
      !(who == target->query_attack()) &&
      (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
	who->add_prop(LIVE_O_LAST_KILL, target);
	return "Attack " + target->query_the_name(who) + 
	"?!? Please confirm by trying again.\n";
    }

    if (!F_DARE_ATTACK(who, target))
    {
	return "You don't dare attack.\n";
    }


    return 0;
}

void
reset_chop()
{
    object who = query_shadow_who();
    who->catch_msg("You feel ready to chop again.\n");
    chop_alarm = 0;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
chop(object target)
{
    object who = query_shadow_who();

    who->catch_msg("You prepare to take a mighty " +
      "swing at " +target->query_the_name(who)+
      ".\n");

    chop_alarm = set_alarm(
      itof(20 - who->query_skill(SS_GUILD_SPECIAL_SKILL) / 10),
      0.0, &chop2(target));

    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
}

/*
* Description:   Perform the actual special attack.
* Arguments:     object target - the target of the attack
*/
void
chop2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts;
    int rage_bonus = 0;
    string how, why, weapon, hdesc;
    string *attack_type;
    string *attack_types;
    object attacker = query_shadow_who();
    object wep;

    set_alarm(10.0, 0.0, "reset_chop");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	attacker->catch_msg("The target of your attack seems to " +
	  "have slipped away.\n");
	return;
    }

    if(!sizeof(attacker->query_weapon(-1)))
    {
	write("You have been disarmed! You cannot " +
	  "chop an opponent without an axe!\n");
	return;
    }
    if(member_array(W_AXE, TP->query_weapon(-1)->query_wt()) < 0)
    {
	write("You are no longer wielding an axe, " +
	  "so you cannot chop your target.\n");
	return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_occ_special(target, "chop")))
    {
	attacker->catch_msg(why);
	return;
    }

    if(TP->query_weapon(-1)[0]->query_wt() == W_AXE)
    {
	weapon = attacker->query_weapon(-1)[0]->short();
	wep = attacker->query_weapon(-1)[0];
    }
    else
    {
	weapon = attacker->query_weapon(W_LEFT)->short();
	wep = attacker->query_weapon(W_LEFT);
    }

    if(present("battlerage_agg_obj", attacker))
    {
	rage_bonus = attacker->query_skill(SLAM_SPECIAL_SKILL) / 10;
    }



    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 90,
	  target)) > 0)
    {
	/* attack successful! */
	if(target->query_race() == "goblin" || target->query_race() == "troll" ||
	  target->query_race() == "giant" || target->query_race() == "ogre" ||
	  target->query_race() == "orc" || target->query_race() == "half-ogre" ||
	  target->query_race() == "hill giant" ||
	  target->query_race() == "minotaur" || target->query_race() == "hobgoblin")
	{
	    hitres = target->hit_me(F_PENMOD(
		(attacker->query_stat(SS_STR) /2 + (wep->query_pen() *2)) /2 + rage_bonus,
		attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	      wep->query_dt(), attacker, -1);
	}
	else
	    hitres = target->hit_me(F_PENMOD(
		(attacker->query_stat(SS_STR) /2 + (wep->query_pen() * 5/4)) /2 + rage_bonus,
		attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	      wep->query_dt(), attacker, -1);
    }
    else
    {
	/* attack missed. */
	hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }
    phurt = hitres[0];
    hdesc = hitres[1];

    /* add fatigue */
    if (attacker->query_fatigue() < 5)
    {
	attacker->heal_hp(-(5 - attacker->query_fatigue()));
	attacker->set_fatigue(0);
	attacker->catch_msg("The strain of the attack drains you.\n");
    }
    else
    {
	attacker->add_fatigue(-5);
    }

    if (phurt >= 0) 
    {
	/* remove some of the attacker's panic */
	attacker->add_panic(-3 - phurt / 5);

	attack_type = ({"chop furiously","hack wildly","swing mightily"});
	/*
		att = random(3);
	*/
	attack_types = ({"chops furiously","hacks wildly","swings mightily"});
	atts = random(3);

	/* give combat descriptions based on the percent damage done */
	switch (phurt)
	{
	case 0:
	    how = "just missing ";
	    break;
	case 1..2:
	    how = "nicking ";
	    break;
	case 3..5:
	    how = "slicing a minor flesh wound in ";
	    break;
	case 6..10:
	    how = "slamming the face of the " +weapon+ " hard into ";
	    break;
	case 11..20:
	    how = "slashing a nasty wound in ";
	    break;
	case 21..30:
	    how = "slicing deeply into ";
	    break;
	case 31..50:
	    how = "burying it deeply into ";
	    break;
	case 51..75:
	    how = "tearing a great wound in ";
	    break;
	case 76..90:
	    how = "splattering blood everywhere as the "+weapon+
	    " almost removes ";
	    break;
	default:
	    how = "dealing a mortal wound to ";
	    break;
	}


	/* message to the attacker */
	if(target->query_race() == "goblin" || target->query_race() == "troll" ||
	  target->query_race() == "giant" || target->query_race() == "ogre" ||
	  target->query_race() == "hill giant" || target->query_race() == "orc" ||
	  target->query_race() == "half-ogre" || 
	  target->query_race() == "minotaur" || target->query_race() == "hobgoblin")
	{
	    attacker->catch_msg("Your racial hatred of " +QTNAME(target)+
	      " gives you renewed strength!\n");
	    attacker->tell_watcher(QCTNAME(attacker)+ "'s eyes seem to blaze " +
	      "with pure hatred!\n");
	}
	attacker->catch_msg("You " +attack_type[atts]+ " at " +
	  target->query_the_name(attacker)+ " with your " +weapon+
	  ", " +how+ HIS(target)+ " " +hdesc+ ".\n");

	/* message to the target */
	target->catch_msg(QCTNAME(attacker) + " " +attack_types[atts]+
	  " at you with " +HIS(attacker)+ " " +weapon+
	  ", " +how+ "your " +hdesc+ ".\n");

	/* message to onlookers */
	attacker->tell_watcher(QCTNAME(attacker) + " " +attack_types[atts]+
	  " at " +QTNAME(target)+ " with " +HIS(attacker)+ " " +weapon+
	  ", " +how+ HIS(target)+ " " +hdesc+ ".\n", target);

	if (target->query_hp() <= 0)
	{
	    target->do_die(attacker);
	}

	return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    attacker->add_attack_delay(5);

    /* message to attacker */
    attacker->catch_msg("You swing your " +weapon+ " at "+
      QTNAME(target)+ " but miss by a mile.\n");

    /* message to target */
    target->catch_msg(QCTNAME(attacker) + " swings at you with "
      +HIS(attacker)+ " " +weapon+ " but misses by a mile.\n");

    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " swings at " +
      QTNAME(target)+ " but misses by a mile.\n", target);
}

/*
* Description:   See if we are currently preparing to perform
*                the special attack
* Returns:       1 / 0 - preparing / not preparing
*/
int
query_chop()
{
    return !!chop_alarm;
}
