/*
  This is the tell line spell for the Fire College.

  Bishop of Calia, July 2003.

*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spells/tell.c";

#include <ss_types.h>
#include <options.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h"


//We redefine this to use the built-in targeting function in tell.c.
public object *
find_tell_targets(object caster, string str)
{
    return tell_target_one_distant_guild_member(caster, str, 
        "Colleges of Elemental Magic");
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
    ::config_spell(caster, targets, argument);

    set_spell_time(1);
    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);

    set_spell_target(target_tell);
    set_spell_name("firetell");
    set_spell_desc("Send a message to a faraway College member.");

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
    string name;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but feel that your " +
            "message does not reach its target.\n");
        return;
    }
    
    if(targets[0]->query_met(caster))
    {
        name = caster->query_name(); // Met? -> 'Bishop'
    }
    else
    {
        name = LANG_ADDART(caster->query_gender_string()) + " " +
           caster->query_race_name(); // Unmet? -> 'a male human'
    }

    caster->catch_tell("You complete the spell, projecting your" +
        " message to " + targets[0]->query_the_name(caster) + ".\n");

    if (caster->query_option(OPT_ECHO))
    {
        caster->catch_msg("The message sent was: " + 
            query_tell_message() + "\n");
    }
    
    targets[0]->catch_tell("What begins as a sharp pain in the back"+
        " your head solidifies into the voice of " + name + 
        ", saying: " + query_tell_message() + "\n");
}
