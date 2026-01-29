/*
 * /d/Gondor/common/guild2/spells/dramalgos_object.c
 *
 *     This is the object that executes the attack when the spell
 *     'dramalgos' is cast by a Morgul Mage
 *
 * Attack spell
 * (dramm-alagos = stroke-stormwind)
 * 
 * Class 2 damage spell
 * Element Air; Form Enchantment
 * Area of effect: living target
 *
 * Ingredient: tarragon, chervil, oregano or basil, a leftover
 * Mana: 20 + random(10), depending on success of spell
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description: F_PENMOD(MS_DRAMA_PEN_MIN + 10..30, 
 *              MIN((SS_OCCUP + SS_ELEMENT_AIR + SS_FORM_ENCHANTMENT, 80))
 * Requirements: Morgul Mage, guild level > 5
 *               mage robe must be present
 *
 * Olorin, 01-jun-1994
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


#define MS_DRAMA_INGR     ({ "dramalgos_ingr1", "leftover" })
#define MS_DRAMA_MANA      20
#define MS_DRAMA_TASK     TASK_SIMPLE
#define MS_DRAMA_LIST     ({ SS_SPELLCRAFT, SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT })
#define MS_DRAMA_TARGET   ({ SS_ELEMENT_EARTH, SS_FORM_ABJURATION })
#define MS_DRAMA_PEN_MIN   30

#undef DEBUG

mixed
do_dramalgos(string str)
{
    this_player()->catch_msg("With the power the Dark Lord has bestowed upon you, you call the Stormwind.\n");

    return cast_spell(str, MS_DRAMA_INGR, MS_DRAMA_MANA, MS_DRAMA_MIN);
}

int
spell_success(object attacker, object target)
{
    int     result;

    if ((result = attacker->resolve_task(
	  MS_DRAMA_TASK, MS_DRAMA_LIST, target, MS_DRAMA_TARGET)) <= 0)
	return 0;

#if DEBUG
    attacker->catch_msg("DEBUG dramalgos object: result = " + result + ".\n");
#endif
    if (result < 100)
	result = 100;
    if (result > 300)
	result = 300;
    // result to be in the range 10..30 for use in spell_damage()
    result /= 10;
    return result;
}

int
spell_damage(object attacker, object target)
{
    int     power = attacker->query_prop(MORGUL_I_SPELL_POWER);

    // mana is already reduced in cast_spell()
    // this is the additional mana reduction for successful spell
    attacker->add_mana(- (MS_DRAMA_MANA * (power-10) / 40) );
    // MAX: F_PENMOD(20..40, 80) with skills/stat at max, depending on power
    return F_PENMOD(MS_DRAMA_PEN_MIN + power, 
      attacker->query_stat(SS_OCCUP) + MIN(
	attacker->query_skill(SS_ELEMENT_AIR) +
	attacker->query_skill(SS_FORM_ENCHANTMENT), 80));
}

int
spell_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_AIR);
}

void
spell_message(object attacker, object target, mixed hitresult)
{
    int     phit = hitresult[0];
    string  what,
    how,
    bolt;

    bolt = "a single bolt"; what = "misses "; how = "";
    if (phit > 0)
	what = "strikes ";
    if (phit > 10)
	how = " hard";
    if (phit > 20)
	bolt = "a sharp bolt";
    if (phit > 30)
    {
	bolt = "three small bolts";
	what = "strike ";
	how = "";
    }
    if (phit > 40)
	bolt = "three spear-shaped bolts";
    if (phit > 50)
	what = "slam against ";
    if (phit > 60)
	bolt = "three large spear-shaped bolts";
    if (phit > 70)
	how = ", driving you back";
    if (phit > 80)
    {
	what = "smash ";
	how = " onto the ground";
    }
    if (phit > 90)
    {
	what = "squash ";
	how = " to pulp on the ground";
    }

    tell_watcher(QCTNAME(attacker) + " makes a low whistling noise, then quickly gestures in " +
      QTNAME(target) + "'s direction.\n" +
      CAP(bolt) + " of wind " + what + target->query_objective() + how + ".\n", attacker, target); 
    attacker->catch_msg("With a quick gesture you release the Stormwind against " + QTNAME(target) + ".\n" +
      CAP(bolt) + " of wind " + what + target->query_objective() + how + ".\n");
    target->catch_msg(QCTNAME(attacker) + " makes a low whistling noise, then quickly gestures in your direction.\n" +
      CAP(bolt) + " of wind " + what + "you" + how + ".\n");

    // Logging - Morbeche
    if (find_player(target->query_real_name()))
    {
	log_file("mm_player_fight", ctime(time()) + " : " + attacker->query_name() +
	  " dramalgos " + target->query_name() +
	  " with hit result " + phit + ".\n");
    }
    log_file("mm_wind_attack", ctime(time()) + " : " + attacker->query_name() +
      " casts dramalgos on " + target->query_name() + 
      " with hit result of " + phit + ".\n");
}

int query_mana_cost() { return MS_DRAMA_MANA; }
