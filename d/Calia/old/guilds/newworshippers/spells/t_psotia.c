/*

   Psotia (fire elemental summon) spell for the Worshippers.

   Coded by Bishop of Calia, 02/07/03.

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
    object *gems = filter(deep_inventory(caster), &operator(==)("bloodstone") @ 
        &->query_gem_name());
    
    if (!sizeof(gems))
    {
        caster->catch_tell("You need a bloodstone in order to successfully cast" +
            " this spell!\n");
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
    set_spell_name("psotia");
    set_spell_desc("Summon a fire elemental");
    set_spell_target(special_target);
    set_spell_time(8);
    set_spell_mana(100);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 35);
    set_spell_form(SS_FORM_CONJURATION, 30);
    set_spell_object(WOR_OBJECTS + "fire_summ.c");
    set_spell_ingredients(({ }));
    set_spell_peaceful(1);
    set_spell_visual(0); //This spell needs to work in darkness.
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You begin to murmur the Psotia incantation, calling" +
        " out to Lord Pyros to send you one of his servants.\n");
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
    object elemental;

    if (caster->query_prop(WOR_CREATURE_SUMMONED))
    {
        caster->catch_tell("You can only control one creature at a time -" +
            " your spell fails!\n");
    }
    else if (environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER ||
        environment(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You sense that the elemental refuses to" +
            " materialize here.\n");
    }
    else
    {
        setuid();
        seteuid(getuid());
        elemental = make_spell_effect_object(query_spell_object(), caster, 
            caster, resist, result);
            
        if (random(100) >= 90)
        {
            caster->catch_tell("You sacrificed a bloodstone.\n");
            comp->set_heap_size(comp->num_heap() - 1);
        }            
            
        tell_room(environment(caster), 
            "A wave of heat suddenly blows into the area, oppressing and" +
            " fearful.\n" + QCNAME(elemental) + " forms from a massive" +
            " swirl of smoke and ash.\n");
       
        elemental->move_living("M", environment(caster));
        
        caster->catch_tell("Do <ehelp> to see what commands you can give to" +
            " your elemental.\n");
    }
}