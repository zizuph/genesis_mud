/*
 * cilenze
 *
 * Description: Silence someone
 * Class:       2
 * Ingredients:
 * Mana:        40 (1/3)
 * Tax:         N/A
 * Skills:      SS_ELEMENT_FIRE     3
 *              SS_FORM_CONJURATION 4
 * Task:        TASK_ROUTINE
 * Restriction: Must not be engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("cilenze");
    set_spell_desc("Silence someone");

    set_spell_element(SS_ELEMENT_FIRE, 3);
    set_spell_form(SS_FORM_CONJURATION, 4);

    set_spell_time(4);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(80);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(({ "copper", "copper coin" }));

    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob;
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int size;

    tell_room(E(caster), QCTNAME(caster) + " moves " + POSSESSIVE(caster) +
             " hands slowly in the air. " + QTNAME(tar) +
             "seems to choke on something.\n", (({ caster, tar })));

    caster->catch_msg("Moving your hands and speaking the words of power " +
             "you direct the energy towards " + QTNAME(tar) + " and " +
             "silences " + HIM(tar) + ".\n");

    tar->catch_msg(QCTNAME(caster) + " moves " + POSSESSIVE(caster) +
             " hands slowly in the air. You feel your throat grow hotter " +
             "its as if you tongue is burning wildly. You seem to be choking, " +
             "as your tonque is growing and burning wildly.\n");
    tar->command("$choke");

    ob = make_spell_effect_object(SPELL_OBJ + "cilenze", caster, tar, 0,
        result);
    ob->set_spell_duration((result > 120 ? 120: result) * 2);
}






