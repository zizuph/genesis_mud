/*
 * General Gem Shattering Spell
 * 
 * This is a generic gem shattering spell that should be used as the 
 * basis for all gem shattering spells in the new Genesis Magic system.
 * The purpose of shattering gems is to make a single gem into multiple
 * spell component parts. This helps to reduce the cost of the spell
 * components while also providing casters with a gem/money based
 * requirement.
 *
 * Created by Petros, April 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_shatter_spell(object caster, mixed * targets, int * resist, int result);
public void hook_describe_shatter_success(object caster, object * all_gems, object * all_shards);
public void hook_describe_shatter_no_valid_gems_precast(object caster);
public void hook_describe_shatter_no_valid_gems_postcast(object caster);
 
/*
 * Function:    config_shatter_spell
 * Description: Config function for shatter spells. Redefine this in your
 *              own shatter spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shatter_spell()
{

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

private nomask void
config_required_parameters()
{
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("shatter");
    set_spell_desc("Shatter Gems");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_mana(30);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_shatter_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_shatter_spell();
    
    // Call this after the config_shatter_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
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
    if (!objectp(obj) || !obj->query_gem() 
        || obj->query_gem_shard() || obj->id("shard"))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    get_valid_gems_for_spell
 * Description: Gets all the valid spells in the area by filtering against
 *              the maskable function is_valid_gem_for_spell.
 * Returns:     The object list of valid gems
 */
static nomask object *
get_valid_gems_for_spell(object caster)
{
    if (!objectp(caster) || !objectp(environment(caster)))
    {
        return ({ });
    }
    return filter(all_inventory(environment(caster)), &is_valid_gem_for_spell(caster,));    
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
    
    if (!sizeof(get_valid_gems_for_spell(caster)))
    {
        hook_describe_shatter_no_valid_gems_precast(caster);
        return 0;
    }
    
    return result;    
}

public int
query_shatter_base_shards()
{
    return 2;
}

public int
query_shatter_random_shards()
{
    return 6;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_shatter_spell(caster, targets, resist, result);

    setuid();
    seteuid(getuid());
    // Perform the actual shattering of the gems   
    object * all_gems = get_valid_gems_for_spell(caster);
    if (!sizeof(all_gems))
    {
        hook_describe_shatter_no_valid_gems_postcast(caster);
        return;
    }
    
    object * all_shards = ({ });
    object * unbroken_gems = ({ });
    foreach (object gem : all_gems)
    {
        object shard = clone_object(SPELL_OBJ_DIR + "gem_shard");
        if (!shard->config_shards(gem->query_gem_name()))
        {
            unbroken_gems += ({ gem });
            shard->remove_object();
            continue;
        }
        // default shards is 2-7 shards
        shard->set_heap_size(gem->num_heap() * (query_shatter_base_shards() + 
            random(query_shatter_random_shards())));
        shard->move(environment(caster));
        all_shards += ({ shard });
    }    
    hook_describe_shatter_success(caster, all_gems, all_shards);
    all_gems -= unbroken_gems;
    all_gems->remove_object();
}

// HOOKS TO BE DEFINED

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
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    caster->catch_tell("You stretch out your hand towards the gems "
        + "upon the ground.\n");
    tell_room(environment(caster), QCTNAME(caster) + " stretches out "
        + caster->query_possessive() + " hand towards the gems upon "
        + "the ground.\n", ({ caster }) );
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
    tell_room(environment(caster), "A brilliant burst of light temporarily "
        + "blinds you and you hear a loud shattering sound from " 
        + COMPOSITE_DEAD(all_gems) + ". As the light fades, you see " 
        + COMPOSITE_DEAD(all_shards) + ".\n");
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
        + "can shatter.\n");
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
        + "on the ground and your spell has no effect.\n");
}

