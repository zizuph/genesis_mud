/*
 * General blind spell
 * 
 * This is a generic blindness spell that should be used as the basis 
 * for all blindness spells under the Genesis Magic system.
 *
 * Created by Navarre, March 2010.
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <ss_types.h>

inherit "/d/Genesis/specials/std/spells/blind";

/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_element(SS_ELEMENT_AIR, 0);
    set_spell_form(SS_FORM_ENCHANTMENT, 0);

    // Set the effect object filename
    set_spell_object("/d/Krynn/guilds/wohs/test/spells/blind_obj");
}


/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" avoids your dirt.\n");
    target->catch_msg("You avoid the dirt thrown by " + QTNAME(caster)+
        ".\n");
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // The blind spell cannot be cast if it is already in effect. At some
    // point, if this spell is going to be mass cast, we should allow the
    // spell to be cast even if some of the targets have the blind spell on.
    // We just need to be careful not to stack the effects.
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }
    return result;    
}

// HOOKS TO BE DEFINED

public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    object target = targets[0];

    caster_message = "You reach into your pouch and grab a handful " +
        "of dirt.\n";
    watcher_message = QCTNAME(caster) + " reaches into his pouch.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public void
hook_describe_blind(object caster, mixed * targets, int result)
{
    caster->catch_msg("You throw a handful of dirt into "+ 
                      COMPOSITE_LIVE(targets) + " face!\n");
    targets->catch_msg(QCTNAME(caster) + " throws dirt into your face!\n");
    tell_room(environment(caster), 
        QCTNAME(caster) + " throws dirt into the eyes of " + 
        COMPOSITE_LIVE(targets) +"!\n", ({ caster }) + targets, caster);
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg("But " + QTNAME(target) + " is already " +
            "blinded!\n");
    }
}

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string *
query_blind_ingredients(object caster)
{
    return ({ });
}
