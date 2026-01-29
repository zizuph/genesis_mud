#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0 - configuration successful
 *                1 - configuration unsuccessful, abort spell
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("unseen");
    set_spell_desc("Go unseen");
    set_spell_time(5);
    set_spell_mana(180);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 70);
    set_spell_form(SS_FORM_ILLUSION, 70);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(0);

    set_spell_target(spell_target_caster);
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You concentrate, focusing on the shadows about you.\n");
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    make_spell_effect_object("/d/Emerald/vamp/spells/obj/unseen_obj",
        caster, caster, resist, result);
    caster->catch_tell("You attempt to fade into the darkness of the room.\n");
}
