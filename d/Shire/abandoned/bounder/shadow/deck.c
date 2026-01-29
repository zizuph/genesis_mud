/* deck.c created by Jaypeg
 * This file contains the code for the bounder guild "deck" special.
 * This is part of the bounder guild soul.
 */

/* Description
 * ===========
 * 
 * Deck is a comical name for the Bounder defensive special, where
 * the Bounder uses his/her weapon to knock, trip, or somehow cause
 * a larger opponent to become prone, or more vulnerable.
 * The game effect is simply a lowering of defence skill by 0-40%
 * for a random period influenced by the deck skill.
 */

#include "../guild.h"
#include <macros.h>
#include <formulas.h>
#include "/std/combat/combat.h"
#include <wa_types.h>

#define LIVE_M_NO_DECK  "_live_m_no_deck"
#define TARGET   0
#define ALARM_ID 1

/* A global variable to hold the id for the alarm used for the special */
static private int deck_alarm = 0;

/* Prototypes */
void punch2(object target);

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
    object target =

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


/*
 * Function name: prepdeck
 * Description:   Start up the guild's special attack
 * Arguments:     object target - the person to attack
 */
void
prepdeck(object target)
{
    object who = query_shadow_who();

    who->catch_msg("You prepare to deck " + target->query_the_name(who) + 
      ".\n");

    deck_alarm = set_alarm(
      itof(20 - who->query_skill(SS_DECK) / 5),
      0.0, &deck(target));

    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
}

/*
 * Function name: deck
 * Description:   Perform the actual special attack.
 * Arguments:     object target - the target of the attack
 */
void
deck(object target)
{
    int hitsuc, prone, height, hadjust;
    string how, why;
    object attacker = query_shadow_who();

    deck_alarm = 0;

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
	attacker->catch_msg("The target of your attack seems to " +
	  "have slipped away.\n");
	return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_occ_special(target, "punch")))
    {
	attacker->catch_msg(why);
	return;
    }

    /* Calculate bonuses/penalties according to the differences in 
     * attacker and target height.
     */

    height = (target->query_prop(CONT_I_HEIGHT) 
      -who->query_prop(CONT_I_HEIGHT)

      switch(height)
      {
      case < 0:
	  hadjust = 10
	  break;
      case 0..20:
	  hadjust = 20
	  break;
      default:
	  hadjust = 30
	  break;
      case 80..120:
	  hadjust = 25
	  break;
      case > 120:
	  hadjust = 10
	  break;
      }


      /* Test to see if the attacker hits.  cb_tohit() is the routine
       * used by the combat system to determine if a regular attack
       * hits, but it also works nicely for our purposes.
       */
      prone = (hitsuc = attacker->query_combat_object()->cb_tohit(-1, 90,
	    target))
      if prone > ((attacker->query_skill(SS_DECK)/2) - hadjust))
      {
	  /* attack successful! */
	
}
else
{
    /* attack missed. */
    prone = target->hit_me(hitsuc, 0, attacker, -1)[0];
}

if (prone >= 0) 
{
    /* remove some of the attacker's panic */
    attacker->add_panic(-3 - prone / 5);

    /* give combat descriptions based on the success */
    switch (prone)
    {
    case 0:
	how = "merely distracted";
	break;
    case 1..15:
	how = "off-balance";
	break;
    case 16..30:
	how = "disoriented";
	break;
    default:
	how = "decked";
	break;
    }

    /* message to the attacker */
    attacker->catch_msg("You punch " + target->query_the_name(attacker) +
      ".\n" + capitalize(target->query_pronoun()) + " appears to be  " +
      how + ".\n");

    /* message to the target */
    target->catch_msg(attacker->query_The_name(target) +
      " punches you!\nYou are " + how + ".\n");

    /* message to onlookers */
    attacker->tell_watcher(QCTNAME(attacker) + " punches " +
      QTNAME(target) + ".\n" + capitalize(target->query_pronoun()) +
      " appears to be " + how + ".\n", target);

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
attacker->catch_msg("You try to deck " +
  target->query_the_name(attacker) + " but miss.\n");

/* message to target */
target->catch_msg(attacker->query_The_name(target) +
  " tries to deck you but misses.\n");

/* message to onlookers */
attacker->tell_watcher(QCTNAME(attacker) + " tries to deck " +
  QTNAME(target) + " but misses.\n", target);
}
