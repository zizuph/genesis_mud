/* This spell is based off /d/Genesis/newmagic/spells/darkvision.c
 *
 * A self spell that allows the caster to see in 1 level of darkness. 
 * It requires a hazelnut component, and lasts for 5 minutes in duration.
 *
 * Arman Kharas 01/07/2003
 */


#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/elven_archers/guild.h"
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define ELF_VISION "_ansalon_archers_elf_vision"

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You take a deep breath and concentrate.\n");
    tell_room(environment(caster), QCTNAME(caster) + 
        " takes a deep breath and concentrates.\n", caster);

}

public void
create_spell()
{
    set_spell_name("elf-vision");
    set_spell_desc("Enhance your elven sight to see in darkness");
    set_spell_time(8);
    set_spell_mana(70);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_ingredients(({ }));
    set_spell_visual(0);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object("/d/Ansalon/guild/elven_archers/spells/darkvision_obj");

    set_spell_target(spell_target_caster);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
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
    object target = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    if (caster->query_prop(ELF_VISION))
    {
        caster->catch_tell("Your eyes are already focused to see " +
            "in the dark!\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result);

    caster->catch_tell("Your feel your eyes become more focused. " +
        "That which was previously hidden in shadows is now " +
        "more clearly defined.\n");
    tell_room(environment(caster), QCTNAME(caster)+ " eyes "+
        "suddenly dilate, then become more focused.\n", caster);
}
