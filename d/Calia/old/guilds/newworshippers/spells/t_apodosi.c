/*

  This is the Apodosi (returning) spell for the Worshippers.

  Coded by Bishop of Calia, June 2003.

*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spell.c";

#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

object comp;

/*
  Targeting routine so we can handle the possible removal of a gem. 
  Need this since use_component can't be defined in a gem.
*/
public mixed 
special_target(object caster, string str)
{
    object *gems = filter(deep_inventory(caster), &operator(==)("opal") @ 
        &->query_gem_name());
    
    if (!sizeof(gems))
    {
        caster->catch_tell("You need an iridescent opal in order to" +
            " successfully cast this spell!\n");
        return ({ });
    }
    
    comp = gems[0];
    
    return ({caster});
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
    set_spell_name("apodosi");
    set_spell_desc("Return to the Temple");
    set_spell_target(special_target);
    set_spell_time(10);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_EARTH, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_ingredients(); //Dealing with component elsewhere.
    set_spell_peaceful(1);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to murmur the Apodosi incantation.\n");
    say(QCTNAME(caster) + " begins to murmur a strange" +
        " incantation.\n");
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
    
    if (environment(caster)->query_prop(ROOM_M_NO_TELEPORT) ||
        environment(caster)->query_prop(ROOM_M_NO_TELEPORT_FROM))
    {
        caster->catch_tell("Some force prevents you from transporting" +
            " away from this room.\n");
    }
    else if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER
       || environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER
       || environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
    {
        caster->catch_tell("You can't transport from this place, get" +
            " solid ground under your feet!\n");
    }        
    else
    {
        if (random(100) >= 85)
        {
            caster->catch_tell("You sacrificed an iridescent opal.\n");
            comp->set_heap_size(comp->num_heap() - 1);
        }
    
        caster->catch_tell("You complete the Apodosi incantation, and call" +
            " out to Lady Gu to transport you back to the Temple.\n" +
            " You close your eyes and sink into the ground. After what seems" +
            " like only a few seconds you sense that you are home and open" +
            " your eyes again.\n");
        say(QCTNAME(caster) + " closes " + caster->query_possessive() + 
            " eyes and descends into the ground.\n", caster);
        caster->move_living("M", "/d/Calia/worshippers/temple/s_chamber.c");
        say(QCTNAME(caster) + " ascends from the depths of the earth.\n", 
            caster);
    }
}