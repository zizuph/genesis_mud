/*
  This is the Light spell for the College of Fire Magic.

  Coded by Bishop of Calia, July 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h"


public object *
special_target_caster(object caster, string str)
{
    if (present("_steadyflame_ob_", caster))
    {
        caster->catch_tell("You have already summoned the flame!\n");
        return ({ });
    }
    else
    {
        return ({caster});
    }
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("steadyflame");
    set_spell_desc("Summon a flame to light your way");
    set_spell_target(special_target_caster);
    set_spell_time(3);
    set_spell_mana(25);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object(FIRE_SPELLS + "steadyflame_ob");
    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You draw power from the Plane of Fire.\n");
    say(QCTNAME(caster) + " appears to focus, " + 
        caster->query_possessive() + " eyes flashing deep red.\n");
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
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }
    
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist[0], result)->move(caster);
}