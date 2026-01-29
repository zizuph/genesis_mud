/*
 *  faerun/spells/drow_levitate.c
 *
 *  Levitation spell which can be used by all standard faerun drows. It 
 *  will make them levitate which causes them to be out of reach for
 *  anything but ranged weapons and magic.
 *
 *  Created by Wully, 20-2-2004
 */

inherit "/d/Genesis/newmagic/spell";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
/*
 * Function name: create_spell
 * Description  : Construct the spell
 */
public void create_spell()
{
    set_spell_name("levitate");
    set_spell_desc("Levitate");
    set_spell_time(10 + random(10));
    set_spell_mana(20);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_ingredients(({ }));
    set_spell_object(P_FAERUN_SPELLS + "drow_levitate_obj");
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

    if(caster->query_drow_levitating())
    {
        caster->catch_msg("You are already levitating.\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result);

    caster->catch_tell("\nSuddenly you raise a few feet above the ground.\n");
    tell_room(environment(caster), "\n" + QCTNAME(caster) + " suddenly starts " +
        "levitating.\n\n", caster);
}
