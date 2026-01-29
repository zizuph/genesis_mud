/*
 * /d/Gondor/common/guild2/spells/faugoroth_object.c
 *
 *     This is the object that executes the attack when the spell
 *     'faugoroth' is cast by a Morgul Mage
 *
 * Attack spell
 * (faug-goroth = choke-horror)
 * 
 * Class 2 damage spell
 * Element Death; Form Enchantment
 * Area of effect: living target
 *
 * Ingredient: mint
 * Mana: 55..100, depending on the power of the spell
 * Skills: SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description:  increase panic, decrease fatigue of victim
 * Requirements: Morgul Mage, Guild level >=  7
 *               mage robe must be present
 *
 * Olorin, 10-jun-1994
 *
 * Maintenance:
 * -----------
 * March 26 2000, Morbeche - Added logging
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/spells/attack_object";

#include <cmdparse.h>
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_FAUGO_INGR     ({ "faugoroth_ingr1", })
#define MS_FAUGO_MANA     50
#define MS_FAUGO_TASK     TASK_SIMPLE
#define MS_FAUGO_LIST     ({ SS_SPELLCRAFT, SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT })
#define MS_FAUGO_TARGET   ({ SS_ELEMENT_LIFE, SS_FORM_ABJURATION })

/*
 * Function name: spell_attack
 * Description:   this function is called from within the combat system.
 * Arguments:     attacker - we
 *                target - the attacked living.
 */
public void
spell_attack(object attacker, object target)
{
    int hurt,
    phurt,
    res,
    delay;

    hurt = spell_damage(attacker, target);
    res = spell_resist(target);
    hurt -= (hurt * res) / 100;

    /* add here panic increase, decrease of fatigue points */
    target->add_fatigue(-hurt);
    target->add_panic(hurt);
    if (hurt > 0)
    {
	/* don't delay attack if spell completely resisted
	 *	-- gorboth, gnadnar, 27 dec 98
	 * reduce delay by % resistance 
	 *	-- gorboth, gnadnar, 22 mar 99
	 */
	delay = (30 + target->query_panic() / 10);	/* orig value */
	delay -= (delay * res) / 100;          /* per shiva's request */
	if (delay > 0)
	{
	    target->add_attack_delay(delay);
	}
    }
    phurt = (hurt * target->query_max_fatigue()) / 100;

    spell_message(attacker, target, ({phurt, 0, hurt, hurt}));
#if DEBUG
    attacker->catch_msg("DEBUG attack object: damage " + hurt + "; phurt " + phurt + ".\n");
#endif

}

int
do_faugoroth(string str)
{
    this_player()->catch_msg("With the power the Dark Lord has bestowed upon " +
      "you, you call the Choking Horror.\n");

    return cast_spell(str, MS_FAUGO_INGR, MS_FAUGO_MANA, MS_FAUGO_MIN);
}

int
spell_success(object attacker, object target)
{
    int     result;

    if ((result = attacker->resolve_task(
	  MS_FAUGO_TASK, MS_FAUGO_LIST, target, MS_FAUGO_TARGET)) <= 0)
    {
#if DEBUG
	attacker->catch_msg("DEBUG faugoroth object: result = " + result + ".\n");
#endif
	return 0;
    }
#if DEBUG
    attacker->catch_msg("DEBUG faugoroth object: result = " + result + ".\n");
#endif
    if (result <  90)
	result =  90;
    if (result > 300)
	result = 300;
    result /= 3;
    // range 30..100
    return result;
}

int
spell_damage(object attacker, object target)
{
    int     power = attacker->query_prop(MORGUL_I_SPELL_POWER),
    dark;
    object  room;

    if (objectp(room = environment(attacker)))
	dark = ((room->query_prop(ROOM_I_LIGHT) > 0) ? 0 : 1);

    // mana is already reduced in cast_spell()
    // this is the additional mana reduction for successful spell
    attacker->add_mana(-(MS_FAUGO_MANA*power)/100);

#if DEBUG
    attacker->catch_msg("DEBUG faugorth_object spell_damage: " + power);
#endif
    power *= (100 + attacker->query_stat(SS_OCCUP));
    power /= 100;
    // range 30..200
    if (dark)
	power *= 2;
#if DEBUG
    attacker->catch_msg(" -> " + power + "\n");
#endif

    return power;
}

int
spell_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_DEATH);
}

void
spell_message(object attacker, object target, mixed hitresult)
{
    int     phit = hitresult[0];
    string  he = target->query_pronoun(),
    his = target->query_possessive(),
    him = target->query_objective(),
    target_how,
    watcher_how,
    attacker_how = 0;

    switch (phit)
    {
    case 0:
	target_how = "You tremble a little.\n";
	watcher_how = " trembles a little.\n";
	break;
    case 1..10:
	target_how = "You are quaking as if you are bitter cold.\n";
	watcher_how = " is quaking as if "+he+" were bitter cold.\n";
	break;
    case 11..25:
	target_how = "You feel utter desperation and exhaustion " +
	"creeping over you.\n";
	watcher_how = " looks desperate and exhausted.\n";
	break;
    case 26..50:
	target_how = "You struggle with panic as a dark terror creeps over " +
	"you, making it impossible to flee.\n";
	watcher_how = " struggles with panic as a dark shadow creeps over "+
	him+".\n";
	break;
    case 51..100:
    default:
	target_how = "You slump to your knees, overcome with despair.\n";
	watcher_how = " slumps to "+his+" knees, overcome with despair.\n";
	break;
    }
    if (!stringp(attacker_how))
	attacker_how = watcher_how;

    tell_watcher(
      QCTNAME(attacker)+" stares threateningly at "+QTNAME(target)+".\n" +
      QCTNAME(target)+watcher_how,attacker,target);
    attacker->catch_msg(
      "You cast the Choking Horror against "+QTNAME(target)+".\n" +
      CAP(he)+attacker_how);
    target->catch_msg(
      QCTNAME(attacker)+" stares at you with eyes like burning coals.\n" +
      target_how);

    // Logging - Morbeche
    if (find_player(target->query_real_name()))
    {
	log_file("mm_player_fight", ctime(time())+" : "+attacker->query_name() +
	  " faugoroth "+ target->query_name() + " with " +
	  "hitresult " + phit + ".\n");
    }
    log_file("mm_fatigue_drain", ctime(time())+ ": "+attacker->query_name() +
      " cast faugoroth on "+target->query_name()+" with a " +
      "hitresult of "+ phit +".\n");
}

int query_mana_cost() { return MS_FAUGO_MANA; }
