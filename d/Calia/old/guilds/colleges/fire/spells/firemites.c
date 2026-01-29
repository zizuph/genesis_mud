/*
    Fire mites. A spell where a caster summons a cloud of insect-
    like beings from the Plane of Fire, surrounding him. As usual
    the action is in the spell effect object. 
    
    In addition to hurting people who attack the caster, some 
    adventurous mites will leave the swarm and slam into anyone
    the caster happens to be attacking.
    
    Coded by Bishop, July 2003.
*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"


public object *
special_target_caster(object caster, string str)
{
    if (present("college_fire_mites", caster))
    {
        caster->catch_tell("You have already summoned the fire" +
            " mites!\n");
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
    set_spell_name("firemites");
    set_spell_desc("Summon a small swarm of fire mites");
    set_spell_time(10);
    set_spell_mana(160);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(special_target_caster);    
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);
    set_spell_ingredients(({ }));
    set_spell_peaceful(1);
    set_spell_target_verify(spell_verify_present);
    set_spell_object(FIRE_SPELLS + "firemites_ob");
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("Drawing power from the Plane of Fire, you" +
        " begin to trace the complex wards and symbols required" +
        " to summon and bind a swarm of fire mites.\n");
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
            " the fire mites won't materialize in this location.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result)->move(targets[0]);
}

