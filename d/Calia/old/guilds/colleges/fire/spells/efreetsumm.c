/*
    This spell summons a minor efreet that acts as a messenger, and
    can be sicced at a target, acting as a minor persistant damage
    spell.

    Bishop of Calia, July 2003.
*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

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
    set_spell_name("efreetsumm");
    set_spell_desc("Summon a small efreet to act as a messenger");
    set_spell_time(6);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(spell_target_caster);    
    set_spell_element(SS_ELEMENT_FIRE, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_ingredients(({ }));
    set_spell_peaceful(1);
    set_spell_target_verify(spell_verify_present);
    set_spell_object(FIRE_SPELLS + "efreetsumm_ob");
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("Drawing power from the Plane of Fire, you" +
        " begin to trace the complex wards and symbols required" +
        " to summon and bind a fire efreet.\n");
    say(QCTNAME(caster) + " appears to focus, " + 
        caster->query_possessive() + " eyes flashing deep red." +
        " Tracing arcane symbols in the air, " + 
        caster->query_pronoun() + " begins to perform some" +
        " kind of ritual.\n", caster);
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to have "+
            "no effect.\n");
        return;
    }
    
    if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You complete the spell, but sense that" +
            " the efreet won't materialize in this location.\n");
        return;
    }    
    

    setuid();
    seteuid(getuid());

    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0]);
}