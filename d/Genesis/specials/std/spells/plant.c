/*
 * General Herb Planting Spell
 * 
 * This is a generic herb planting spell that can be used to put an
 * herb that doesn't normally grow in a particular location and allow
 * it to grow there for that particular Armageddon cycle.
 *
 * Created by Petros, May 2014
 */
 
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_plant_spell(object caster, mixed * targets, int * resist, int result);
public void hook_describe_plant_success(object caster, object herb);
public void hook_describe_plant_no_valid_herb_precast(object caster);
public void hook_describe_plant_no_valid_herb_postcast(object caster);
public void hook_describe_plant_no_valid_room(object caster);
 
/*
 * Function:    config_plant_spell
 * Description: Config function for plant spells. Redefine this in your
 *              own plant spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_plant_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
}

/*
 * Function:    query_plant_ingredients
 * Description: This function defines what components are required for
 *              this plant spell.
 */
public string *
query_plant_ingredients(object caster)
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

    set_spell_name("plant");
    set_spell_desc("Plant Herb");

    set_spell_mana(30);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_plant_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_plant_spell();
    
    // Call this after the config_plant_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    is_valid_herb_for_spell
 * Description: This returns whether this particular herb is valid to
 *              be planted by this spell. This should be masked so that
 *              herbs are only available for the specific guild's
 *              spells.
 */
public int
is_valid_herb_for_spell(object caster, object obj)
{
    if (!objectp(obj) || !IS_HERB_OBJECT(obj))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    get_valid_herbs_for_spell
 * Description: Gets all the valid spells in the area by filtering against
 *              the maskable function is_valid_herb_for_spell.
 * Returns:     The object list of valid herbs
 */
static nomask object *
get_valid_herbs_for_spell(object caster)
{
    if (!objectp(caster) || !objectp(environment(caster)))
    {
        return ({ });
    }
    return filter(all_inventory(environment(caster)), &is_valid_herb_for_spell(caster,));    
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
    
    if (!sizeof(get_valid_herbs_for_spell(caster)))
    {
        if (!execute)
        {
            hook_describe_plant_no_valid_herb_precast(caster);
        }
        else
        {
            hook_describe_plant_no_valid_herb_postcast(caster);
        }
        return 0;
    }

    // Check to see if the environment can actually grow any herbs already.
    object room = environment(caster);
    if (!objectp(room)
        || !IS_ROOM_OBJECT(room)
        || !sizeof(room->query_herb_files()))
    {
        hook_describe_plant_no_valid_room(caster);
        return 0;
    }
    
    return result;    
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
    resolve_plant_spell(caster, targets, resist, result);

    setuid();
    seteuid(getuid());

    // Perform the actual planting of the herbs   
    object * all_herbs = get_valid_herbs_for_spell(caster);
    // We only take the first herb, since we should only be able to plant one
    // herb at a time.
    object herb = all_herbs[0];
    object room = environment(caster);
    string * herbs_in_room = room->query_herb_files();
    if (!IN_ARRAY(MASTER_OB(herb), herbs_in_room))
    {
        // Note that we don't duplicate entries. But we also don't prevent the
        // user from planting something that already exists. The reason is
        // that if we do, it would pretty much function like "lfind" for the
        // gardeners.
        environment(caster)->add_herb_file(MASTER_OB(herb));
    }
    hook_describe_plant_success(caster, herb);

    // Decrement the herb heap by one. It automatically removes the object
    // if the count goes to 0.
    herb->split_heap(1);
    herb->remove_split_heap();
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_plant_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_plant_spell(object caster, mixed * targets, int * resist, int result)
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
    caster->catch_tell("You stretch out your hand towards the herb "
        + "upon the ground.\n");
    tell_room(environment(caster), QCTNAME(caster) + " stretches out "
        + caster->query_possessive() + " hand towards the herb upon "
        + "the ground.\n", ({ caster }) );
}

/*
 * Function:    hook_describe_plant_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and herbs are planted. It
 *              gives a list of all the herbs prior to planting and all the
 *              shards resulting from the plant.
 */
public void
hook_describe_plant_success(object caster, object herb)
{
    tell_room(environment(caster), "A brilliant burst of light temporarily "
        + "blinds you and you see the herb burrow itself into the ground. As "
        + "the light fades, you sense that the ground's soil has accepted "
        + "your gift.\n");
}

/*
 * Function:    hook_describe_plant_no_valid_herb_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find any herbs. Called from check_valid_action
 */
public void
hook_describe_plant_no_valid_herb_precast(object caster)
{
    caster->catch_tell("You don't find anything on the ground that you "
        + "can plant.\n");
}

/*
 * Function:    hook_describe_plant_no_valid_herb_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid herbs
 *              to plant. This can occur if someone picks up the herbs,
 *              for example.
 */
public void
hook_describe_plant_no_valid_herb_postcast(object caster)
{
    caster->catch_tell("You realize much too late that there are no herbs "
        + "on the ground and your spell has no effect.\n");
}

/*
 * Function:    hook_describe_plant_no_valid_room
 * Description: Mask this function to describe the message that occurs when
 *              the caster tries to plant something in a room that has no
 *              other herbs already defined.
 */
public void
hook_describe_plant_no_valid_room(object caster)
{
    caster->catch_tell("This area doesn't seem to be amenable to planting "
        + "herbs. You may want to try again elsewhere.\n");
}
