/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 */

/* Navarre December 29th 2006
   I removed the fatigue drain from the attacks. It caused the players to
   become too tired to move in just a few fights.
   It made it even worse that several occ guilds also drain fatigue,
   like the Dragonarmy, the monks etc.
   We had a few players leave the minotaurs for this reason.
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

static private int gore_alarm = 0;
static private int preparing_gore = 0;
static string *horn_desc = ({"undeveloped horns",
  "growing horns","horns","sharp horns","long horns",
  "deadly horns", "deadly horns", "deadly horns",
  "impressive horns", "impressive horns", 
  "impressive horns", "regal horns",});

/* Prototypes */
void gore2(object target);

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
reset_gore()
{
    object who = query_shadow_who();

    who->catch_tell("You feel ready to gore your foes again!\n");
    gore_alarm = 0;
}


float
query_gore_prepare_time(object who)
{
    float delay;
    delay = who->query_speed(3+random(15));
    return delay;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
gore(object target)
{
    object who = query_shadow_who();
    
    who->catch_msg("You prepare to gore " + target->query_the_name(who) + 
                   " with your horns.\n");


    gore_alarm = set_alarm(query_gore_prepare_time(who), 0.0, &gore2(target));

    preparing_gore = 1;
    
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
gore2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts, guild_bonus;

    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object* enemies;
    object enemy;
    object attacker = query_shadow_who();
    int horn_level = MIN(11, attacker->query_stat(SS_LAYMAN) /10);
    string horns = horn_desc[horn_level];

    preparing_gore = 0;

    guild_bonus = MIN(attacker->query_stat(SS_LAYMAN), 20);

    set_alarm(attacker->query_speed(10), 0.0, "reset_gore");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
        object enemy = attacker->query_enemy();
        if(enemy && environment(enemy) == environment(attacker))
        {
            target = enemy;
        }
        else
        {
            enemies = attacker->query_enemy(-1);
            for(int i = 0, num_enemies = sizeof(enemies); i < num_enemies; i++)
            {
                enemy = enemies[i];

                if(enemy && environment(enemy) == environment(attacker))
                {
                    target = enemy;
                    break;
                }
            }
            attacker->catch_msg("The target of your attack seems to " +
                                "have slipped away.\n");
            return;
        }
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_lay_special(target, "gore")))
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
		(attacker->query_stat(SS_STR) / 3) + guild_bonus,
		attacker->query_skill(SS_GUILD_SPECIAL_SKILL)),
	      W_IMPALE, attacker, -1);
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

    if (phurt >= 0) 
    {
	/* remove some of the attacker's panic */
	attacker->add_panic(-3 - phurt / 5);

        switch (phurt)
	{
	case 0:
	    attack_message = ({
	      "You charge past " +target->query_the_name(attacker)+
	      ", just missing " +HIM(target)+ " with your " +horns+ ".\n",
	      attacker->query_The_name(target)+ " charges past, " +
	      HIS(attacker)+ " " +horns+ " just missing you.\n",
	      QCTNAME(attacker)+ " charges past " +QTNAME(target) +
	      "as "+ HE(attacker)+ " tries to gore " +HIM(target)+
	      " with " +HIS(attacker)+ " " +horns+ ".\n"
	    });
	    break;
	case 1..2:
	    attack_message = ({
	      "You lightly rake your " +horns+ " along " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ", just drawing " +
              "blood.\n",
	      attacker->query_The_name(target)+ " lightly rakes " + HIS(attacker)+
	      " " +horns+ " along your " +hdesc + ", just drawing blood.\n",
	      QCTNAME(attacker)+ " lightly rakes " +HIS(attacker)+ 
              " " +horns+ " along " +QTNAME(target)+ "'s " +hdesc+ ", just " +
              "drawing blood.\n"
	    });
	    break;
	case 3..5:
	    attack_message = ({
	      "You snort in annoyance as you just graze " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ " with your " +
              horns+ ".\n",
	      attacker->query_The_name(target)+ " snorts in annoyance as " +
	      HE(attacker)+ " just grazes your " +hdesc + " with " +HIS(attacker)+
              " " +horns+ ".\n",
	      QCTNAME(attacker)+ " snorts in annoyance as " +HE(attacker)+ 
              " just grazes " +QTNAME(target)+ "'s " +hdesc+ " with " +
              HIS(attacker)+ " " +horns+ ".\n"
	    });              
	    break;
	case 6..10:
	    attack_message = ({
	      "You thrust your " +horns+ " deeply into " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ".\n",
	      attacker->query_The_name(target)+ " thrusts " + HIS(attacker)+
	      " " +horns+ " deeply into your " +hdesc + ".\n",
	      QCTNAME(attacker)+ " thrusts " +HIS(attacker)+ 
              " " +horns+ " deeply into " +QTNAME(target)+ "'s " +hdesc+ ".\n"
	    });
	    break;
	case 11..30:
	    attack_message = ({
	      "You viciously whip your " +horns+ " across " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ", tearing a " +
              "nasty wound.\n",
	      attacker->query_The_name(target)+ " viciously whips " + HIS(attacker)+
	      " " +horns+ " across your " +hdesc + ", tearing a nasty wound.\n",
	      QCTNAME(attacker)+ " viciously whips " +HIS(attacker)+ 
              " " +horns+ " across " +QTNAME(target)+ "'s " +hdesc+ ", tearing " +
              "a nasty wound.\n"
	    });
	    break;
	case 31..50:
	    attack_message = ({
	      "You impale " +target->query_the_name(attacker)+ "'s " +hdesc+ 
              " with your " +horns+ ", wounding " +HIM(target)+ " badly.\n",
	      attacker->query_The_name(target)+ " impales your " +hdesc + 
             " with " +HIS(attacker)+ " " +horns+ ", wounding you badly.\n",
	      QCTNAME(attacker)+ " impales " +QTNAME(target)+ "'s " +hdesc+ 
             " with " +HIS(attacker)+ " " +horns+ ", wounding " +HIM(target)+
             " badly.\n"
	    });
	    break;
	case 51..75:
	    attack_message = ({
	      "With a roar, you thrust your " +horns+ " repeatedly into " +
	      target->query_the_name(attacker)+ ", tearing massive wounds in " +
              HIS(target)+ " " +hdesc+ ".\n",
	      "With a roar, " +attacker->query_the_name(target)+ " thrusts " + HIS(attacker)+
	      " " +horns+ " repeatedly into you, tearing massive wounds in your " +hdesc + ".\n",
	      "With a roar, " +QTNAME(attacker)+ " thrusts " +HIS(attacker)+ 
              " " +horns+ " repeatedly into " +QTNAME(target)+ ", tearing massive wounds in " +
              HIS(target)+ " " +hdesc+ ".\n"
	    });
	    break;
	case 76..99:
	    attack_message = ({
	      "You bellow victoriously as you smash " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ " with your " +horns+ ", leaving " +
              HIM(target) +" at your mercy.\n",
	      attacker->query_The_name(target)+ " bellows victoriously as " + HE(attacker)+
	      " smashes you with " +HIS(attacker)+ " " +horns+ ", leaving you at deaths door!\n",
	      QCTNAME(attacker)+ " bellows victoriously as " +HE(attacker)+ " smashes " +
             QTNAME(target)+ "'s " +hdesc+ " with his " +horns+ ", leaving " +HIM(target)+ 
             " helpless and at " +HIS(attacker)+ " mercy.\n"
	    });
	    break;
	default:
	    attack_message = ({
	      "You thrust your " +horns+ " deeply into " +
	      target->query_the_name(attacker)+ "'s " +hdesc+ ", lifting " +HIM(target)+ 
              " into the air and then tossing " +HIS(target)+ " mortally wounded body " +
              "to the ground in victory!\n",
	      attacker->query_The_name(target)+ " thrusts " + HIS(attacker)+
	      " " +horns+ " deeply into your " +hdesc + ", lifting you into the air and tossing " +
              "your mortally wounded body to the ground like a rag doll.\n",
	      QCTNAME(attacker)+ " thrusts " +HIS(attacker)+ 
              " " +horns+ " deeply into " +QTNAME(target)+ "'s " +hdesc+ ", lifting " +HIM(target)+ 
              " into the air and tossing " +HIS(target)+ " mortally wounded body to the " +
              "ground in victory!\n"
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

    /* message to attacker */
    attacker->catch_msg("You snarl in frustration as "+
                         QTNAME(target)+ " easily avoids your " +horns+ ".\n");

    /* message to target */
    target->catch_msg(QCTNAME(attacker) + " snarls in frustration as " +
                      "you easily avoid " +HIS(attacker)+ " " +horns+ ".\n");

    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " snarls in frustration as " +
                           QTNAME(target)+ " easily avoids " +HIS(attacker)+
                           " " +horns+ ".\n", target);
}

int
query_gore()
{
    return !!gore_alarm;
}

/*
 * Description:   See if we are currently preparing to perform
 *                the special attack
 * Returns:       1 / 0 - preparing / not preparing
 */
int
query_prepare_gore()
{
    return !!preparing_gore;
}

