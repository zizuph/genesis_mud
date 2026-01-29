/*
 Elven archers regrowth spell:

 This spell enables the caster to 'refresh' a room of herbs that may
 have been herbed out.  A property is temporarily added to the room
 in which the regrowth spell will not have any further
 affect until the property is automatically approximately
 20 minutes later.  The required spell component for this spell is
 a gem of any sort.

 Arman Kharas  2 July 2003

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

#define REGROWTH_SPELL_PROP   "_ansalon_regrowth_spell_prop"


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You close your eyes and begin concentrating.\n");
    tell_room(environment(caster), QCTNAME(caster) + 
        " closes " +HIS(caster)+ " eyes and begins concentrating.\n", caster);

}


public void
create_spell()
{
    set_spell_name("regrowth");
    set_spell_desc("Restore the bounty of the land to areas harvested");
    set_spell_time(10);
    set_spell_mana(120);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_vocal(1);
    set_spell_ingredients(({"_gem_ingredient"}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_object("/d/Ansalon/guild/elven_archers/spells/regrowth_obj");

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

    if (environment(caster)->query_prop(REGROWTH_SPELL_PROP))
    {
        caster->catch_tell("You complete the spell, but it seems the " +
            "land has already benefited recently from regrowth.\n");
        return;       
    }

    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result);

    caster->catch_tell("You lower yourself to the ground and begin "+
                "chanting, pouring your mystical energies into the "+
                "land around you.\n");
    tell_room(environment(caster), QCTNAME(caster)+ " lowers "+
                HIM(caster)+ "self to the ground and begins "+
                "chanting in elvish, pouring mystical energies "+
                "into the surrounding land.\n", caster);
}
