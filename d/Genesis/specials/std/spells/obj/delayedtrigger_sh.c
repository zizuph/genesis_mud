/*
 * Delayed Trigger Shadow
 * 
 * This is a default shadow that adds the delayed trigger shadow.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 * TODO: still need to add capability of specifying spell to trigger
 *
 * Created by Petros, November 2012
 */
 
#pragma strict_types
#pragma save_binary

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         invoke_triggered_spell(string spell_filename);

// Global Variables
public string       trigger_spell_filename = 0;
public mapping      stored_inputs = ([ ]);

/*
 * Function:    has_delayedtrigger_shadow
 * Description: Indicates that the person shadowed has the delayedtrigger
 *              effect on them.
 */
public int
has_delayedtrigger_shadow()
{
    return has_spell_shadow();
}

/*
 * Function:    remove_delayedtrigger_shadow
 * Description: Removes this particular shadow
 */
public void
remove_delayedtrigger_shadow()
{
    remove_spell_shadow();
}

/*
 * Function:    set_trigger_spell_filename
 * Description: Sets the spell that will be triggered when this
 *              delayed trigger expires.
 */
public void
set_trigger_spell_filename(string file)
{
    stored_inputs["triggered spell"] = file;
}

/* 
 * Function:    query_trigger_spell_filename
 * Description: Returns the filename of the spell that should fire.
 */
public string
query_trigger_spell_filename()
{
    return stored_inputs["triggered spell"];
}

/*
 * Function:    set_resolve_spell_parameters
 * Description: Sets the resolve spell parameters that will be passed to the
 *              triggered spell. By default, this takes in the values as
 *              originally cast for the delayed trigger spell. All the
 *              parameters can be replaced before the actual call happens.
 */
public void
set_resolve_spell_parameters(object caster, mixed * targets, int * resist, int result)
{
    stored_inputs["caster"] = caster;
    stored_inputs["targets"] = targets;
    stored_inputs["resist"] = resist;
    stored_inputs["result"] = result;
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("delayed trigger");
    spell_object->set_short("delayedtrigger spell object");
    // There's no mana cost to maintain a trigger spell. Make sure to set this
    // to zero if you override this function.
    spell_object->set_maintain_mana(0);
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);
    
    set_trigger_spell_filename(spell_input["triggered spell"]);
    set_resolve_spell_parameters(spell_input["caster"], spell_input["targets"], spell_input["resist"], spell_input["result"]);
    
    // As an example, invoke the spell after 10 seconds.
    set_alarm(10.0, 0.0, &invoke_triggered_spell(query_trigger_spell_filename()));
}

/*
 * Function:    invoke_triggered_spell
 * Description: This is the function that triggers the spell to be cast. Call
 *              this from whatever function you shadow.
 */
public void
invoke_triggered_spell(string spell_filename)
{
    // Just in case there are multiple delay spell shadows, we have a check
    // here to call to the next shadow if the spell filename doesn't match.
    if (query_trigger_spell_filename() != spell_filename)
    {
        shadow_who->invoke_triggered_spell(spell_filename);
        return;
    }
    
    object spell_object = find_object(query_trigger_spell_filename());
    if (!objectp(spell_object))
    {
        send_debug_message("delayedtrigger_sh", "Cannot find the spell object for "
            + query_trigger_spell_filename() + ".\n");
        return;
    }
    
    // Do the actual spell invocation here.
    spell_object->resolve_spell(stored_inputs["caster"], stored_inputs["targets"],
        stored_inputs["resist"], stored_inputs["result"]);
   
    // Now dispel this
    m_spell_object->dispel_effect(m_spell_object->query_effect_caster());
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel a delayed trigger spell activated.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to have a delayed "
            + "trigger spell activated on " + target->query_objective() + ".\n", 
            ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your delayed trigger spell disappears.\n");
        tell_room(environment(target), QCTNAME(target) + " no longer has "
            + "a delayed trigger spell activated.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your delayed trigger spell about to expire.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the delayed trigger effect.\n");
    }    
}

