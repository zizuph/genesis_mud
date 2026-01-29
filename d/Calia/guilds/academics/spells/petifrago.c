/*
 * Shatter Spell for Academy of Elemental Arts
 * 
 * Created by Petros, April 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shatter";

/*
 * Function:    config_shatter_spell
 * Description: Config function for shatter spells. Redefine this in your
 *              own shatter spells to override the defaults.
 */
public void
config_shatter_spell()
{
    set_spell_name("petifrago");
    set_spell_desc("Shatter component gems");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_SIMPLE);    
    // Setting lower skill requirements since it's the most basic spell for Academics
    set_spell_element(SS_ELEMENT_EARTH, 5);
    set_spell_form(SS_FORM_TRANSMUTATION, 5);    
}

/*
 * Function:    query_shatter_ingredients
 * Description: This function defines what components are required for
 *              this shatter spell.
 */
public string *
query_shatter_ingredients(object caster)
{
    return ({ });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a member of the Academy!\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Returns whether this spell is available to this guild
 *              member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    // This basic spell is always available
    return 1;    
}

// HOOKS TO BE DEFINED

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    object * valid_gems = get_valid_gems_for_spell(caster);
    string caster_message, watcher_message;
    switch (random(2))
    {
    case 0:
        caster_message = "You stretch out your right hand toward "
            + COMPOSITE_DEAD(valid_gems) + " upon the ground.\n";
        watcher_message = QCTNAME(caster) + " stretches out "
            + caster->query_possessive() + " right hand toward the "
            + "ground and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You draw upon your inner reserves as you "
            + "focus on " + COMPOSITE_DEAD(valid_gems)
            + " upon the ground.\n";
        watcher_message = QCTNAME(caster) + " has a faraway look in "
            + caster->query_possessive() + " eyes as "
            + caster->query_pronoun() + " concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

/*
 * Function:    resolve_shatter_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shatter_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    is_valid_gem_for_spell
 * Description: This returns whether this particular gem is valid to
 *              be shattered by this spell. This should be masked so that
 *              gem shards are only available for the specific guild's
 *              spells.
 */
public int
is_valid_gem_for_spell(object caster, object obj)
{
    if (!::is_valid_gem_for_spell(caster, obj))
    {
        return 0;
    }
    
    // We only allow gems that are used by the Academics
    switch (obj->query_gem_name())
    {
    case "onyx":   // used by lithodermu
    case "quartz": // used by pyrofosti
        return 1;
    }
    
    return 0;
}

/*
 * Function:    hook_describe_cast_shatter
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_shatter(object caster, object * targets)
{
}

/*
 * Function:    hook_describe_shatter_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and gems are shattered. It
 *              gives a list of all the gems prior to shattering and all the
 *              shards resulting from the shatter.
 */
public void
hook_describe_shatter_success(object caster, object * all_gems, object * all_shards)
{
    caster->catch_tell("A brilliant burst of light temporarily blinds you, "
        + "accompanied by a loud shattering noise from " 
        + COMPOSITE_DEAD(all_gems) + ".\nAs the light fades, you see "
        + COMPOSITE_DEAD(all_shards) + " in their place.\n");
    tell_room(environment(caster), "A brilliant burst of light temporarily "
        + "blinds you, accompanied by a loud shattering noise from the "
        + "ground.\n", ({ caster }) );
}

/*
 * Function:    hook_describe_shatter_no_valid_gems_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find any gems. Called from check_valid_action
 */
public void
hook_describe_shatter_no_valid_gems_precast(object caster)
{
    caster->catch_tell("You don't find anything on the ground that you "
        + "can use petifrago upon.\n");
}

/*
 * Function:    hook_describe_shatter_no_valid_gems_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid gems
 *              to shatter. This can occur if someone picks up the gems,
 *              for example.
 */
public void
hook_describe_shatter_no_valid_gems_postcast(object caster)
{
    caster->catch_tell("You realize much too late that there are no gems "
        + "on the ground and your invocation of petifrago has no effect.\n");
}
