/*
 * Detect Magic Spell for the Elementalist Guilds of Calia
 * 
 * This allows one to detect magic on a person or an individual object. It is
 * based on the Genesis Magic System's detect magic spell.
 *
 * Created by Petros, February 2013
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/detect_magic";

/*
 * Function:    config_detect_magic_spell
 * Description: Config function for detect_magic spells. Redefine this in your
 *              own detect_magic spells to override the defaults.
 */
public void
config_detect_magic_spell()
{
    set_ability_group("Elemental Worshippers of Calia");
    set_spell_name("detramfip");
    set_spell_desc("Detect magic on an object or person");

    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_detect_magic_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_detect_magic_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_detect_magic_not_allowed
 * Description: Override to customize the message for when the current
 *              environment does not allow one to detect magic here.
 */
public void
hook_detect_magic_not_allowed(object caster, string target)
{
    caster->catch_tell("You find your ability to sense magic to be muted "
        + "here.\n");
}

/*
 * Function:    hook_detect_magic_cast
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_magic_cast(object caster)
{
    caster->catch_msg("You start detecting magic.\n");
}

/*
 * Function:    hook_detect_magic_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_magic_resisted(object caster, object target, int resistance)
{
    caster->catch_msg(QCTNAME(target) + " resists your attempt to detect "
        + "magic.\n");
}

/*
 * Function:    hook_detect_magic_living_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a living being.
 */
public void
hook_detect_magic_living_results(object caster, object target, object * effects)
{
    if (sizeof(effects))
    {
        caster->catch_msg("You detect magical effects on " + QTNAME(target) 
            + ".\n");
    }
    else
    {
        caster->catch_msg("You don't detect any magic on " + QTNAME(target) 
            + ".\n");
    }
}

/*
 * Function:    hook_detect_magic_nonliving_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a nonliving object.
 */
public void
hook_detect_magic_nonliving_results(object caster, object target, mapping magical_properties)
{
    if (m_sizeof(magical_properties))
    {
        caster->catch_msg("You detect magical properties on " + target->short() 
            + ".\n");
    }
    else
    {
        caster->catch_msg("You don't detect any magic on " + target->short() 
            + ".\n");
    }
}

/*
 * Function:    query_detect_magic_ingredients
 * Description: This function defines what components are required for
 *              this detect_magic spell.
 */
public string *
query_detect_magic_ingredients(object caster)
{
    // By default, use the herb for awareness
    return ({ "kuko" });
}

public int
query_spell_can_be_learned(object player)
{
    // For now, remove this spell altogether.
    return 0;
    
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    return 1;
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
    return "kuko";
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
