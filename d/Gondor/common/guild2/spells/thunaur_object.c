/*
 * /d/Gondor/common/guild2/spells/thunaur_object.c
 *
 *     This is the object that executes the attack when the spell
 *     'thunaur' is cast by a Morgul Mage
 *
 * Attack spell
 * (thu-naur = breath fire)
 * 
 * Class 3 damage spell
 * Element Fire; Form Conjuration
 * Area of effect: living target
 *
 * Ingredient: leftover
 * Mana: 60..90
 * Skills: SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: F_PENMOD(75 + 25..50, 100 + 100..200)
 * Requirements: Morgul Mage, Guild level >= 14
 *               mage robe must be present
 *               mage must have quaffed nennaur potion
 *
 * Arren, 25 july 1994
 *
 * Maintenance:
 * ------------
 * March 26 2000, Morbeche - Added logging
 */
#pragma save_binary

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

#define MS_THUNA_INGR     ({ "leftover", })
#define MS_THUNA_MANA     30
#define MS_THUNA_TASK     TASK_SIMPLE
#define MS_THUNA_LIST     ({ SS_SPELLCRAFT, SS_FORM_CONJURATION, \
                             SS_ELEMENT_FIRE, SS_ELEMENT_AIR })
#define MS_THUNA_TARGET   ({ SS_ELEMENT_EARTH, SS_FORM_ABJURATION, })
#define MS_THUNA_PEN_MIN  75
#define MS_THUNA_SKILL_MIN  100

#define DEBUG 0

mixed
do_thunaur(string str)
{
    if ((!objectp(present(MORGUL_S_NENNAUR_EFFECT_NAME, TP))) &&
      (!TP->query_npc()))
	return "You are not properly prepared to cast this spell!\n";

    TP->catch_msg("With the power the Dark Lord has bestowed "+
      "upon you, you call the Firebreath.\n");

    return cast_spell(str, MS_THUNA_INGR, MS_THUNA_MANA, MS_THUNA_MIN);
}

int
spell_success(object attacker, object target)
{
    int     result;

    if ((result = attacker->resolve_task(
	  MS_THUNA_TASK, MS_THUNA_LIST, target, MS_THUNA_TARGET)) <= 0)
	return 0;
#if DEBUG
    attacker->catch_msg("DEBUG thunaur object: result = " + result + ".\n");
#endif
    if (result < 100)
	result = 100;
    if (result > 200)
	result = 200;

    return result;
}

int
spell_damage(object attacker, object target)
{
    int     power = attacker->query_prop(MORGUL_I_SPELL_POWER);
    /*
     *  mana is already reduced in cast_spell()
     *  this is the additional mana reduction for successful spell
     */ 
    attacker->add_mana(- (MS_THUNA_MANA * power / 100) );
    return F_PENMOD(MS_THUNA_PEN_MIN + power/4, MS_THUNA_SKILL_MIN + power);
}

int
spell_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_FIRE);
}

void
spell_message(object attacker, object target, mixed hitresult)
{
    string flame, how;
    int    phit, dam;

    flame = "a stab of fire, ";
    how = "miss ";
    phit = hitresult[0];
    dam = hitresult[3];
#if DEBUG
    attacker->catch_msg("DEBUG: spell_message: phit = "+phit+", dam = "+dam+"\n");
#endif

    switch(phit)
    {
    case -1: break;
    case 0..5:
	how = "lick "; break;
    case 6..15:
	how = "scorch "; break;
    case 16..30:
	how = "burn "; break;
    case 31..50:
	how = "wither "; break;
    case 51..90:
	how = "shrivel "; break;
    case 91..100:
    default:
	how = "consume "; break;
    }
    if (dam > 600)
	flame = "fierce white-hot flames, ";
    else if (dam > 300)
	flame = "fierce flames, ";

    attacker->catch_msg("You inhale deeply and then spout forth " + flame +
      "the flames " + how + QTNAME(target) + ".\n");
    target->catch_msg(QCTNAME(attacker) + " inhales deeply and then spouts forth "+
      flame + "the flames " + how + "you.\n");
    tell_watcher(QCTNAME(attacker) + " inhales deeply and then spouts forth "+
      flame + "the flames " + how + QTNAME(target) + ".\n", attacker, target);

    // Logging - Morbeche
    if (find_player(target->query_real_name()))
    {
	log_file("mm_player_fight", ctime(time()) +" : "+attacker->query_name()+
	  " thunaur " + target->query_name() + " with " +
	  "phit " + phit + " and dam " + dam + ".\n");
    }
    log_file("mm_fire_attack", ctime(time()) + " : " + attacker->query_name() +
      " cast thunaur on " + target->query_name() + " with " +
      "phit of " + phit + " and dam of " + dam + ".\n");

}

int query_mana_cost() { return MS_THUNA_MANA; }
