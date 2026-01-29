/*
  This is the Evimero (Haste) spell for the Worshippers.

  Coded by Bishop of Calia, June 2003.

 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell.c";
 
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

public mixed
special_target(object caster, string str)
{
    if (caster->query_prop(LIVE_I_EVIMERO_HASTE))
    {
        caster->catch_tell("You're already under the effects of the Evimero" +
            " enchantment!\n");
        return ({ });
    }
    else if(caster->query_prop(LIVE_I_HAD_EVIMERO_HASTE))
    {
        caster->catch_tell("You feel that your body would be unable to" +
            " handle the strain of the Evimero enchantment again so soon.\n");
        return ({ });
    }

    return ({ caster });
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
    set_spell_name("evimero");
    set_spell_desc("Infuse yourself with the speed of Lady Aeria");
    set_spell_target(special_target);
    set_spell_time(6);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 35);
    set_spell_ingredients(({"chicory" }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object("/d/Calia/newworshippers/spells/evimero_ob");
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to murmur the Evimero incantation.\n");
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
}

public void
evimero_recast(object caster)
{
    caster->remove_prop(LIVE_I_HAD_EVIMERO_HASTE);
    caster->catch_tell("You feel the strain from your last casting of" +
        " Evimero dissipating, and think you're ready to attempt the" +
        " spell again.\n");
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
        resist, result);
    set_alarm(540.0, 0.0, &evimero_recast(caster));
  
}