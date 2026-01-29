/*
 * Shatter Spell for Elemental Worshippers of Calia
 * 
 * Created by Petros, December 2010
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
    set_spell_name("spazopetra");
    set_spell_desc("Shatter component gems");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_SIMPLE);
    set_spell_time_factor(1.5); // no components
    set_spell_fail("You sense your prayers are not heard.\n");
  
    // Setting lower skill requirements since it's the most basic spell
    set_spell_element(SS_ELEMENT_EARTH, 5);
    set_spell_form(SS_FORM_ABJURATION, 5);    
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
        caster->catch_tell("You are not a servant of the Elementals!\n");
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

    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
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
        caster_message = "You concentrate upon a prayer to Lady Gu as "
            + "you weave a hand across " + COMPOSITE_DEAD(valid_gems) 
            + " laid before you.\n";
        watcher_message = QCTNAME(caster) + " concentrates and weaves "
            + caster->query_possessive() + " hand back and forth above the "
            + "gems on the ground.\n";
        break;
    
    case 1:
    default:
        caster_message = "You murmur the ancient mantras and invoke the "
            + "prayer of spazopetra to Lady Gu over " + COMPOSITE_DEAD(valid_gems)
            + " upon the ground.\n";
        watcher_message = QCTNAME(caster) + " has a faraway look in "
            + caster->query_possessive() + " eyes as "
            + caster->query_pronoun() + " begins an ancient chant.\n";
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
    
    // Each branch of the guild will have different lists here.
    if (IS_CLERIC(caster))
    {
        switch (obj->query_gem_name())
        {
        case "quartz": // used by pyrofosti
        case "topaz_yellow": // used by choma
        case "chalcedony": // used by elefrinisi
        case "ruby": // used by schirmo
        case "diamond": // used by unteristi
        case "diamond_black": // used by unteristi
        case "pearl": // aleipso
        case "pearl_black": // aleipso
        case "turquoise": // used by dynami
        case "jade": // used by evimero
        case "opal": // used by floga
        case "opal_fire": // used by floga
            return 1;
        }
    }
    else if (IS_WORSHIPPER(caster))
    {
        switch (obj->query_gem_name())
        {
        case "quartz": // used by pyrofosti
        case "topaz_yellow": // used by choma
        case "chalcedony": // used by elefrinisi
        case "ruby": // used by schirmo
        case "diamond": // used by unteristi
        case "diamond_black": // used by unteristi
        case "pearl": // aleipso
        case "pearl_black": // aleipso
        case "turquoise": // used by dynami
        case "jade": // used by evimero
        case "opal": // used by floga
        case "opal_fire": // used by floga
            return 1;
        }
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
    caster->catch_tell("As you complete the prayer, you hear a series of cracking "
        + "noises from " + COMPOSITE_DEAD(all_gems) + " before you. After a "
        + "moment, you see they have shattered into " + COMPOSITE_DEAD(all_shards)
        + ".\n");
    tell_room(environment(caster), "You hear a series of small cracking noises "
        + "from the gems on the ground. They appear to have shattered into "
        + "shards.\n", ({ caster }) );
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
        + "can use " + query_spell_name() + " upon.\n");
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
        + "on the ground and your invocation of " + query_spell_name()
        + " has no effect.\n");
}


/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "none";
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "prayers" is used.
 */
public void
list_spells()
{
    string ingredients_description = query_spell_ingredients_description();
    if (!strlen(ingredients_description))
    {
        ingredients_description = "none";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}
