/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 * Modified by Blizzard:
 * 25.08.2003 - Changed the chop prepare time (now random)
 * 1.10.2003  - Dis check only if we are not already fighting the target.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

#define STAND_STRONG "_stand_strong_clan_special"
#define AXEWIELDR query_weapon(W_RIGHT)->query_wt() == W_AXE
#define AXEWIELDL query_weapon(W_LEFT)->query_wt() == W_AXE
#define AXEWIELDB query_weapon(W_BOTH)->query_wt() == W_AXE

static private int chop_alarm = 0;
static private int preparing_chop = 0;

/* Prototypes */
void chop2(object target);

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

  /* Check only if not already in combat with this target */
    if ( member_array(target, who->query_enemy(-1)) == -1 )
    {
        if ( (!who->query_npc()) && (who->query_met(target)) &&
            ( who->query_prop(LIVE_O_LAST_KILL) != target))
        {
      	    who->add_prop(LIVE_O_LAST_KILL, target);
	    
	    return "Attack " + target->query_the_name(who) + 
	        "?!? Please confirm by trying again.\n";
         }

         if ( !F_DARE_ATTACK(who, target) )
         {
	     return "You don't dare to attack " + 
	         target->query_the_name(who) + ".\n";
         }
    }

    return 0;
}

void
reset_chop()
{
    object who = query_shadow_who();
    if(who->AXEWIELDR || who->AXEWIELDL || who->AXEWIELDB)
	who->catch_tell("You feel ready to chop again.\n");
    else
	who->catch_tell("You feel ready to crush your foes again.\n");
    chop_alarm = 0;
}

/* Function name: query_chop_prepare_time
 * Description  : Returns the time of chop preparation.
 * Returns      : float - time between command and actual attack.
 */
float
query_chop_prepare_time(object who)
{
    float delay;
    delay = who->query_speed(3 + random(15));
    return delay;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
chop(object target)
{
    object who = query_shadow_who();

    if ( who->query_prepare_slam() )
    {
        notify_fail("You are too focused on preparing a shield slam, " +
            "and can't do that.\n");
        return;
    }
    
    who->catch_msg("You prepare to take a mighty " +
        "swing at " + target->query_the_name(who) + ".\n");

    /* New formula, 25.08.2003, Blizzard */
    chop_alarm = set_alarm(query_chop_prepare_time(who), 0.0, &chop2(target));

    preparing_chop = 1;
    
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
    int racial_hatred = 0;
    int wielding_axe;
    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object attacker = query_shadow_who();
    object wep;

    preparing_chop = 0;
    
    if(present("battlerage_agg_obj", attacker))
	set_alarm(attacker->query_speed(itof(10 - attacker->query_skill(SLAM_SPECIAL_SKILL) / 15)), 0.0, "reset_chop");
    else
	set_alarm(attacker->query_speed(10), 0.0, "reset_chop");

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
	  "continue your wild attack.\n");
	return;
    }
    if(member_array(W_AXE, TP->query_weapon(-1)->query_wt()) < 0 &&
      member_array(W_CLUB, TP->query_weapon(-1)->query_wt()) < 0)
    {
	write("Without a weapon, you find yourself unable to continue " +
	  "with your wild attack!\n");
	return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_occ_special(target, "chop")))
    {
	attacker->catch_msg(why);
	return;
    }

    if(TP->query_weapon(-1)[0]->query_wt() == W_AXE ||
      TP->query_weapon(-1)[0]->query_wt() == W_CLUB)
    {
	weapon = attacker->query_weapon(-1)[0]->short();
	wep = attacker->query_weapon(-1)[0];
    }
    else
    {
	weapon = attacker->query_weapon(W_LEFT)->short();
	wep = attacker->query_weapon(W_LEFT);
    }

    if(attacker->AXEWIELDR || attacker->AXEWIELDL || attacker->AXEWIELDB)
	wielding_axe = 1;


    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 85,
	  target)) > 0)
    {
	/* attack successful! */
	if(target->query_race() == "goblin" || target->query_race() == "troll" ||
	  target->query_race() == "giant" || target->query_race() == "ogre" ||
	  target->query_race() == "orc" || target->query_race() == "half-ogre" ||
	  target->query_race() == "hill giant" || target->query_race() == "uruk" ||
	  target->query_race_name() == "minotaur" || target->query_race_name() == "hobgoblin")
	{
	    hitres = target->hit_me(F_PENMOD(
		(attacker->query_stat(SS_STR) + (wep->query_pen() *2)) /2,
		attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	      wep->query_dt(), attacker, -1);
	    racial_hatred = 1;
	}
	else
	    hitres = target->hit_me(F_PENMOD(
		(attacker->query_stat(SS_STR) /2 + (wep->query_pen() * 2)) /2,
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


	switch (phurt)
	{
	case 0:
	    attack_message = ({
	      "You curse foully in dwarven as your wild swing " +
	      "with your " +weapon+ " at " +target->query_the_name(attacker)+
	      " just misses.\n",
	      attacker->query_The_name(target)+ " curses foully in dwarven " +
	      "as " +HIS(attacker)+ " wild swing just misses you.\n",
	      QCTNAME(attacker)+ " curses foully in dwarven as " +
	      HIS(attacker)+ " wild swing at " +QTNAME(target) +
	      " just misses.\n"
	    });
	    break;
	case 1..2:
	    attack_message = ({
	      "You strike out wildly with your " +weapon+ ", just " +
	      "grazing " +target->query_the_name(attacker)+
	      "'s " +hdesc+ ".\n",
	      attacker->query_The_name(target)+ " strikes out wildly " +
	      "at you with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
	      "your " +hdesc + ".\n",
	      QCTNAME(attacker)+ " strikes out wildly at " +QTNAME(target)+
	      "with " +HIS(attacker)+ " " +weapon+ ", just grazing " +
	      QTNAME(target)+ "'s " +hdesc+ ".\n"
	    });
	    break;
	case 3..5:
	    if(wielding_axe)
		wdtype = "slicing a minor flesh wound";
	    else
		wdtype = "bruising it moderately";

	    attack_message = ({
	      "You grin fiercely as you bring your " +weapon+
	      " down upon " +target->query_the_name(attacker)+ "'s " +
	      hdesc+ ", " +wdtype+ ".\n",
	      attacker->query_The_name(target)+ " grins fiercely as " +HE(attacker)+
	      " brings " +HIS(attacker)+ " " +weapon+ " down upon your " +hdesc+
	      ", " +wdtype+ ".\n",
	      QCTNAME(attacker)+ " grins fiercely as " +HE(attacker)+ " brings " +
	      HIS(attacker)+ " " +weapon+ " down upon " +QTNAME(target)+ "'s " +hdesc+
	      ", " +wdtype+ ".\n"
	    });              
	    break;
	case 6..10:
	    attack_message = ({
	      "You swing furiously at " +target->query_the_name(attacker)+ ", " +
	      "slamming the face of your " +weapon+ " into " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ".\n",
	      attacker->query_The_name(target)+ " swings furiously at you, slamming " +
	      "the face of " +HIS(attacker)+ " " +weapon+ " into your " +hdesc+ ".\n",
	      QCTNAME(attacker)+ " swings furiously at " +QTNAME(target)+ ", " +
	      "slamming the face of " +HIS(attacker)+ " " +weapon+ " into " +QTNAME(target)+ "'s " +
	      hdesc + ".\n"
	    });
	    break;
	case 11..20:
	    if(wielding_axe)
	    {
		watype = "chop";
		wdtype = "slashing a nasty wound";
	    }
	    else
	    {
		watype = "slam";
		wdtype = "striking a painful blow";
	    }
	    attack_message = ({
	      "You " +watype+ " down mightily upon " +target->query_the_name(attacker)+
	      "'s " +hdesc+ " with your " +weapon+ ", " +wdtype+ ".\n",
	      attacker->query_The_name(target)+ " " +watype+ "s down mightily upon " +
	      "your " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n",
	      QCTNAME(attacker)+ " " +watype+ "s down mightily upon " +QTNAME(target)+
	      "'s " +hdesc+ " with " +HIS(attacker)+ " " +weapon+ ", " +wdtype+ ".\n"
	    });
	    break;
	case 21..30:
	    if(wielding_axe)
	    {
		watype = "slice a deep wound upon";
		wdtype = "slices a deep wound upon";
	    }
	    else
	    {
		watype = "smash";
		wdtype = "smashes";
	    }
	    attack_message = ({
	      "You roar gleefully as you " +watype+ " " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ " with your " +
	      weapon + ".\n",
	      attacker->query_The_name(target)+ " roars gleefully as " +
	      HE(attacker)+ " " +wdtype+ " your " +hdesc+ " with " +
	      HIS(attacker)+ " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " roars gleefully as " +HE(attacker)+ " " +
	      wdtype+ " " +QTNAME(target)+ "'s " +hdesc+ " with " +
	      HIS(attacker)+ " " +weapon+ ".\n"
	    });
	    break;
	case 31..50:
	    if(wielding_axe)
		wdtype = "burying it deeply in";
	    else
		wdtype = "smashing it powerfully upon";
	    attack_message = ({
	      "You swing your " +weapon+ " in a deadly arc, " +
	      wdtype+ " " +target->query_the_name(attacker)+ "'s " +hdesc+
	      ".\n",
	      attacker->query_The_name(target)+ " swings " +HIS(attacker)+
	      " " +weapon+ " in a deadly arc, " +wdtype+ " your " +
	      hdesc+ ".\n",
	      QCTNAME(attacker)+ " swings " +HIS(attacker)+ " " +weapon+
	      " in a deadly arc, " +wdtype+ " " +QTNAME(target)+ "'s " +
	      hdesc+ ".\n"
	    });
	    break;
	case 51..75:
	    if(wielding_axe)
		wdtype = "tearing a great wound in";
	    else
		wdtype = "gleefully pulping";
	    attack_message = ({
	      "You launch yourself into the air, bringing your " +weapon+ 
	      " down powerfully upon " +target->query_the_name(attacker)+
	      ", " +wdtype+ " " +HIS(target)+ " " +hdesc+ ".\n",
	      attacker->query_The_name(target)+ " launches " +HIM(attacker)+
	      "self into the air, bringing " +HIS(attacker)+ " " +weapon+
	      " powerfully down upon you, " +wdtype+ " your " +hdesc+ ".\n",
	      QCTNAME(attacker)+ " launches " +HIM(attacker)+ "self into " +
	      "the air, bringing " +HIS(attacker)+ " " +weapon+
	      " powerfully down upon " +QTNAME(target)+ ", " +wdtype+ " " +
	      HIS(target)+ " " +hdesc+ ".\n"
	    });
	    break;
	case 76..99:
	    if(wielding_axe)
		wdtype = "rips to shreads";
	    else
		wdtype = "pulverises";
	    attack_message = ({
	      "You begin to sing a dwarven warsong of victory, as your blow " +
	      "with the " +weapon+ " " +wdtype+ " " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ", splattering " +
	      "blood everywhere.\n",
	      attacker->query_The_name(target)+ " begins to sing a dwarven " +
	      "warsong of victory, as " +HIS(attacker)+ " blow with the " +
	      weapon + " " +wdtype+ " your " +hdesc+ ", splattering blood " +
	      "everywhere.\n",
	      QCTNAME(attacker)+ " begins to sing a dwarven warsong of victory, " +
	      "as " +HIS(attacker)+ " blow with the " +weapon+ " " +wdtype+ " " +
	      QTNAME(target)+ "'s " +hdesc+ ", splattering blood everywhere.\n"
	    });
	    break;
	default:
	    attack_message = ({
	      "You roar in victory as you deal a mortal wound to " +
	      target->query_the_name(attacker)+ " with your " +weapon+ ".\n",
	      attacker->query_The_name(target)+ " roars in victory as " +
	      HE(attacker)+ " deals you a mortal wound with " +HIS(attacker)+
	      " " +weapon+ ".\n",
	      QCTNAME(attacker)+ " roars in victory as " +HE(attacker)+
	      " deals " +QTNAME(target)+ " a mortal wound with " +HIS(attacker)+
	      " " +weapon+ ".\n"
	    });
	    break;
	}


	/* message to the attacker */
	if(target->query_race() == "goblin" || target->query_race() == "troll" ||
	  target->query_race() == "giant" || target->query_race() == "ogre" ||
	  target->query_race() == "hill giant" || target->query_race() == "orc" ||
	  target->query_race() == "half-ogre" || target->query_race() == "uruk" ||
	  target->query_race_name() == "minotaur" || target->query_race_name() == "hobgoblin")
	{
	    attacker->catch_msg("Your racial hatred of " +QTNAME(target)+
	      " gives you renewed strength!\n");
	    attacker->tell_watcher(QCTNAME(attacker)+ "'s eyes seem to blaze " +
	      "with pure hatred!\n");
	}


	attacker->catch_tell(attack_message[0]);

	/* message to the target */
	target->catch_tell(attack_message[1]);

	/* message to onlookers */
	attacker->tell_watcher(attack_message[2], target);

	if (target->query_hp() <= 0)
	{
	    target->do_die(attacker);
	}

	return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
  //  attacker->add_attack_delay(5); 

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

int
query_chop()
{
    return !!chop_alarm;
}

/*
 * Description:   See if we are currently preparing to perform
 *                the special attack
 * Returns:       1 / 0 - preparing / not preparing
 */
int
query_prepare_chop()
{
    return !!preparing_chop;
}

