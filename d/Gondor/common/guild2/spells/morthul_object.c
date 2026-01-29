/*
 * /d/Gondor/common/guild2/spells/morthul_object.c
 *
 *     This is the object that executes the attack when the spell
 *     'morthul' is cast by a Morgul Mage
 *
 * Attack spell
 * (morn-thul = black-breath)
 * 
 * Class 3 damage spell
 * Element Death; Form Conjuration
 * Area of effect: living target
 *
 * Ingredient: morgurth herb
 * Mana: 106 .. 160
 * Skills: SS_ELEMENT_DEATH, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: nazgul poison
 * Requirements: Morgul Mage, SS_OCCUP >= 19
 *               mage robe must be present
 *               caster must have quaffed morgurth potion
 *
 * Olorin, 15-jul-1994
 * - Added logging of players being poisoned to /d/Gondor/log/curses
 *   Elessar, Oct 11th 1995
 *
 * March 27 2000, Morbeche - Changed logging to Mage pfight log
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/spells/attack_object.c";

#include <cmdparse.h>
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_MORTH_INGR     ({ "morthul_ingr1",  })
#define MS_MORTH_MANA       80
#define MS_MORTH_TASK     TASK_ROUTINE
#define MS_MORTH_LIST     ({ SS_SPELLCRAFT, SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT })
#define MS_MORTH_TARGET   ({ SS_ELEMENT_LIFE, SS_FORM_ABJURATION })

#define DEBUG 0

mixed
do_morthul(string str)
{
    if ((!objectp(present(MORGUL_S_MORGURTH_EFFECT_NAME, TP))) &&
      (!TP->query_npc()))
	return "You are not properly prepared to cast this spell!\n";

    TP->catch_msg(
      "With the power the Dark Lord has bestowed upon you, " +
      "you call the Black Breath.\n");

    return cast_spell(str, MS_MORTH_INGR, MS_MORTH_MANA, MS_MORTH_MIN);
}

int
spell_success(object attacker, object target)
{
    int     result;

    if ((result = attacker->resolve_task(
	  MS_MORTH_TASK, MS_MORTH_LIST, target, MS_MORTH_TARGET)) <= 0)
	return 0;
#if DEBUG
    attacker->catch_msg("DEBUG morthul object: result = " + result + ".\n");
#endif
    if (result < 50)
	result = 50;
    // effective max is 168.
    if (result > 150)
	result = 150;
    return result;
}

int
spell_damage(object attacker, object target)
{
    int     power = attacker->query_prop(MORGUL_I_SPELL_POWER);
    object  breath;

    seteuid(getuid());
    breath = clone_object(MORGUL_S_BLACK_BREATH);
    if (breath->move(target))
	breath->move(target, 1);
    // strength of the poison is between 90 + 51/3 = 107 and
    // 90 + (150 + 150)/3 = 190
    breath->set_strength(attacker->query_skill(SS_ELEMENT_DEATH) +
      (power + random(power) + 1) / 3);
    breath->start_poison();

    if (!target->query_npc())
	log_file("mm_player_fight", attacker->query_name() + " used "
	  + "Black Breath on " + target->query_name()
	  + " in " + file_name(environment(attacker)) + ". "
	  + ctime(time()) + ".\n");
    // sucess dependent part of mana reduction
    attacker->add_mana(- (MS_MORTH_MANA*power)/150 );
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
    tell_watcher(QCTNAME(attacker) + " hisses coldly at " +
      QTNAME(target) + ".\n", attacker, target); 
    attacker->catch_msg("With a cold hiss, you poison " +
      QTNAME(target) + " with the Black Breath.\n");
    target->catch_msg(QCTNAME(attacker) + " hisses coldly at you.\n");
}

int
query_mana_cost()
{
    return MS_MORTH_MANA;
}
