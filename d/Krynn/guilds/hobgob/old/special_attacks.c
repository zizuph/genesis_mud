/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

static private int bludgeon_alarm = 0;
static private int preparing_bludgeon = 0;


/* Prototypes */
void bludgeon2(object target);

mixed
can_attack_with_lay_special(object target, string attack)
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
reset_bludgeon()
{
    object who = query_shadow_who();

    who->catch_tell("You feel ready to bludgeon your foes again!\n");
    bludgeon_alarm = 0;
}


float
query_bludgeon_prepare_time()
{
    return itof(3 + random(15));
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
bludgeon(object target)
{
    object who = query_shadow_who();
    
    who->catch_msg("You prepare to bludgeon " + target->query_the_name(who) + 
      " with your WEAPON.\n");


    bludgeon_alarm = set_alarm(query_bludgeon_prepare_time(), 0.0, &bludgeon2(target));

    preparing_bludgeon = 1;
    
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
bludgeon2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts, guild_bonus;

    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object attacker = query_shadow_who();

    preparing_bludgeon = 0;   

    set_alarm(10.0, 0.0, "reset_bludgeon");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	attacker->catch_msg("The target of your attack seems to " +
	  "have slipped away.\n");
	return;
    }


    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_lay_special(target, "bludgeon")))
    {
	attacker->catch_msg(why);
	return;
    }



    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 85,
	  target)) > 0)
    {
	/* attack successful! */

	    hitres = target->hit_me(F_PENMOD(
		(attacker->query_stat(SS_STR) / 3),
		attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	      W_BLUDGEON, attacker, -1);
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
	      "You.\n",
	      attacker->query_The_name(target)+ " just missing you.\n",
	      QCTNAME(attacker)+ " .\n"
	    });
	    break;
	case 1..2:
	    attack_message = ({
	      "You \n",
	      attacker->query_The_name(target)+ " \n",
	      QCTNAME(attacker)+ " \n"
	    });
	    break;
	case 3..5:
	    attack_message = ({
	      "You .\n",
	      attacker->query_The_name(target)+ " .\n",
	      QCTNAME(attacker)+ " .\n"
	    });              
	    break;
	case 6..10:
	    attack_message = ({
	      "You .\n",
	      attacker->query_The_name(target)+ " .\n",
	      QCTNAME(attacker)+ " .\n"
	    });
	    break;
	case 11..30:
	    attack_message = ({
	      "You \n",
	      attacker->query_The_name(target)+ " \n",
	      QCTNAME(attacker)+ " \n"
	    });
	    break;
	case 31..50:
	    attack_message = ({
	      "You \n",
	      attacker->query_The_name(target)+ " \n",
	      QCTNAME(attacker)+ " .\n"
	    });
	    break;
	case 51..75:
	    attack_message = ({
	      "\n",
	      "\n",
	      "\n"
	    });
	    break;
	case 76..99:
	    attack_message = ({
	      "\n",
	      attacker->query_The_name(target)+ " \n",
	      QCTNAME(attacker)+ " \n"
	    });
	    break;
	default:
	    attack_message = ({
	      "You \n",
	      attacker->query_The_name(target)+ " \n",
	      QCTNAME(attacker)+ " \n"
	    });
	    break;
	}


	/* message to the attacker */
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
    attacker->catch_msg("You swing wildly at "+
      QTNAME(target)+ " who easily avoids your WEAPON.\n");

    /* message to target */
    target->catch_msg(QCTNAME(attacker) + " swings wildly at you with "
      +HIS(attacker)+ " WEAPON, which you easily dodge.\n");

    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " swings wildly at " +
      QTNAME(target)+ " with " +HIS(attacker)+ " WEAPON, missing by a mile.\n", target);
}

int
query_bludgeon()
{
    return !!bludgeon_alarm;
}

/*
 * Description:   See if we are currently preparing to perform
 *                the special attack
 * Returns:       1 / 0 - preparing / not preparing
 */
int
query_prepare_bludgeon()
{
    return !!preparing_bludgeon;
}

