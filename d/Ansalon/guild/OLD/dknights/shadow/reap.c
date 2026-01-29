/* This file is included in the guild shadow.  It contains the code
 * for the guild's special attack.  We keep it in a separate file to
 * keep from cluttering the shadow and for easier debugging.
 *
 * Guild name: Death Knights of Krynn.
 * Tax: Max tax for Occ and Layman.
 * Special: Reap
 * Avg. damage: 450
 * Note: Can not be used on undeads.
 *       Uses mana instead of fatigue.
 *       If killed with the special, it will add 200 mana and 200 hp's
 *       to the killer.
 *
 *
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

static private int reap_alarm = 0;

/* Prototypes */
void reap2(object target);

mixed
can_attack_with_reap_special(object target, string attack)
{
    mixed why;
    object who = query_shadow_who();

    if (!target || !living(target) || !present(target, environment(who)))
	return attack + " whom?\n";

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
      who->query_prop(LIVE_I_STUNNED))
    {
	return "You are too stunned to " + attack + ".\n";
    }

    if (  stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) 
       || stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
        return why;
    else if (why)
	return "You sense a force protecting "+target->query_the_name(who)+".\n";

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
	return "";

    if (!F_DARE_ATTACK(who, target))
	return "You don't dare attack.\n";

    if (target->query_prop(LIVE_I_UNDEAD))
	return "You can not reap someone who hasn't got a soul.\n";

    if ((!who->query_npc()) && (who->query_met(target)) &&
      !(who == target->query_attack()) &&
      (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
	who->add_prop(LIVE_O_LAST_KILL, target);
	return "Attack " + target->query_the_name(who) + 
	"?!? Please confirm by trying again.\n";
    }

    return 0;
}

void
reset_reap()
{
    object who = query_shadow_who();
    who->catch_tell("You can once again reap the souls of the living.\n");
    reap_alarm = 0;
}

/*
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
reap(object target)
{
    object who = query_shadow_who();

    who->catch_msg("You prepare to reap " +target->query_the_name(who)+
      "'s soul.\n");

    reap_alarm = set_alarm(
      itof(20 - who->query_skill(SS_GUILD_SPECIAL_REAP) / 10),
      0.0, &reap2(target));

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
reap2(object target)
{
    mixed hitres;
    int hitsuc, phurt, att, atts;
    string how, why, weapon, hdesc, wdtype, watype;
    string *attack_type;
    string *attack_types;
    string *attack_message;
    object attacker = query_shadow_who();
    object corpse;
    string corpse_short;
    string corpse_name;

    set_alarm(10.0, 0.0, "reset_reap");

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	      attacker->catch_msg("The soul of your target seems to " +
	                "have slipped away.\n");
	      return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_reap_special(target, "reap")))
    {
       	attacker->catch_msg(why);
      	return;
    }

    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 95,
	  target)) > 0)
    {
               

	      /* attack successful! */
        hitres = target->hit_me(F_PENMOD(
                 (attacker->query_stat(SS_WIS) +
                  attacker->query_stat(SS_INT)) /2,
                  attacker->query_skill(SS_GUILD_SPECIAL_REAP)),
                  MAGIC_DT, attacker, -1);

        /* Heal the Death Knight with 50% of the damage given */
        attacker->heal_hp(hitres[2] / 2);

    }
    else
    {
   	    /* attack missed. */
      	hitres = target->hit_me(hitsuc, 0, attacker, -1);
    }

    phurt = hitres[0];
    hdesc = hitres[1];

    /* add mana drain */
    if (attacker->query_mana() < 3)
    {
	attacker->heal_hp(-(50 - attacker->query_mana()));
      	attacker->set_mana(0);
      	attacker->catch_msg("The strain of the attack drains you mentally.\n");
    }
    else
    {
	attacker->add_mana(-3);
    }

    if (phurt >= 0) 
    {
	      /* remove some of the attacker's panic */
	      attacker->add_panic(-25 - phurt / 5);

	  switch (phurt)
	  {
	    case 0..1:
	    attack_message = ({
                target->query_The_name(attacker)+ " body turns white as "+HIS(target)+
                " soul dissipates.\n",

                "Your entire body turns numb as your soul begins to dissipate.\n",

                target->query_The_name(attacker)+ "'s body turns white as "+HIS(target)+
                " soul begins to dissipate.\n"
	    });
	    break;

	    case 2..21:
	    attack_message = ({
                target->query_The_name(attacker)+ " arches back in a response "+
                "to the pain as you draw "+HIS(target)+ " soul from "+HIS(target)+
                " body.\n",

                "You arch back in a response to the pain, as you feel "+
                "your soul being drawn from your body.\n",

                target->query_The_name(attacker)+ " arches back in a response to "+
                "the pain, as "+HIS(target)+ " soul is draw from "+HIS(target)+
                " body.\n"
	    });
	    break;

	    case 22..41:
	    attack_message = ({
                "A sudden blackness washes over "+target->query_the_name(attacker)+
                "'s eyes as you desolve "+HIS(target)+ " lifeforce.\n",

                "A sudden blackness washes over your eyes...You can feel "+
                "your heart slowing down to a halt.\n",

                "A sudden blackness washes over "+target->query_the_name(attacker)+
                "'s eyes as "+HIS(target)+ " lifeforce desolves.\n"
	    });
	    break;

	    case 42..61:
	    attack_message = ({
                target->query_The_name(attacker)+ " collapses on the ground in "+
                "pain.\n",

                "An overwhelming pain in your chest causes you to "+
                "collaps on the ground.\n",

                target->query_The_name(attacker)+ " collapses on the ground in "+
                "pain.\n"
	    });
	    break;

	    case 62..81:
	    attack_message = ({
                "You scream out in a deep hollow voice: The Abyss awaits you!\n"+
                target->query_The_name(attacker)+ " attempts to scream, but "+
                HE(target)+ " begins to cough up blood instead.\n",

                QCTNAME(attacker)+ " screams out in a deep hollow voice: The Abyss "+
                "awaits you!\n"+
                "An overpowering pain washes over you, as you catch a vision of "+
                "the Abyss. You attempt to scream, but instead you begin to cough "+
                "up blood.\n",

                target->query_The_name(attacker)+ " attempts to scream, but "+
                "instead " +HE(target)+ " begins to cough up blood.\n"
	    });
	    break;


	    default:
	    attack_message = ({
                "",

                "",

                ""
	    });
	    break;
        }

        attacker->catch_tell("You silently point at " +
                  target->query_the_name(attacker)+ " with your skeletal finger.\n"+
                  attack_message[0]);

        target->catch_tell(attacker->query_The_name(target)+
                " silently points at you with "+HIS(attacker)+ " skeletal "+
                "finger.\n" +
                attack_message[1]);

     	attacker->tell_watcher(QCTNAME(attacker)+ " silently points "+
                  HIS(attacker)+ " skeletal finger at " +QTNAME(target)+".\n" +
                  attack_message[2], target);

	if (target->query_hp() <= 0)
	{
	    target->do_die(attacker);
	}

	return;
    }

    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    attacker->add_attack_delay(1);

    attacker->catch_tell("You silently point at " +
              target->query_the_name(attacker)+ " with your skeletal finger.\n"+
              QCTNAME(target)+ " resists your mental attack!", target);

    target->catch_tell(attacker->query_The_name(target)+
            " silently points at you with "+HIS(attacker)+ " skeletal "+
            "finger.\n" +
            "You resist the mental attack!", target);

    attacker->tell_watcher(QCTNAME(attacker)+ " silently points "+
              HIS(attacker)+ " skeletal finger at " +QTNAME(target)+".\n" +
              QCTNAME(target)+ " resists the mental attack!", target);
}

/*
* Description:   See if we are currently preparing to perform
*                the special attack
* Returns:       1 / 0 - preparing / not preparing
*/
int
query_reap()
{
    return !!reap_alarm;
}


