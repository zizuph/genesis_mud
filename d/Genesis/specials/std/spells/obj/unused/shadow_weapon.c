/*
 * General Shadow Weapon Spell
 * 
 * This is a generic spell to shadow a weapon, which should be used as the
 * basis for all spells shadowing a weapon in the new Genesis Magic system.
 *
 * Created by Navarre, October 2010.
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <language.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/spell";

#include "/d/Genesis/specials/std/spells/centralized_spell.h"

// Prototypes
public void resolve_weapon_shadow_spell(object caster, mixed *targets, int *resist, int result);
public void hook_describe_weapon_shadow_success(object caster, object weapon, object shadow);
public void hook_describe_weapon_shadow_no_valid_weapon_precast(object caster);
public void hook_describe_weapon_shadow_no_valid_weapon_postcast(object caster);
public void hook_describe_non_weapon_target(object caster);
public void hook_describe_weapon_target_not_wielded(object caster, object weapon);
public string query_weapon_shadow();

object weapon_shadow;

/*
 * Function:    config_shadow_weapon_spell
 * Description: Config function for the shadow_weapon spell. Redefine this in your
 *              own shadow weapon spell to override the defaults.
 */
public void
config_shadow_weapon_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
}

/*
 * Function:    query_shadow_weapon_ingredients
 * Description: This function defines what components are required for
 *              this shadow weapon spell.
 */
public string*
query_shadow_weapon_ingredients(object caster)
{
    return ({"red pepper"});
}

private nomask void
config_required_parameters()
{
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("shadow_weapon");
    set_spell_desc("Shadow Weapon");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_object);
    set_spell_ingredients(query_shadow_weapon_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR,  38);
    set_spell_form(SS_FORM_ENCHANTMENT, 39);
        
    // Call the specific configuration that is to be masked.
    config_shadow_weapon_spell();
    
    // Call this after the config_shadow_weapon_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    is_valid_weapon_for_spell
 * Description: This returns whether this particular weapon is valid to
 *              be shadowed. This should be masked to match
 *              what type of weapons are valid to use for shadowing.
 *
 * Arguments: object obj - the object to check for validity.
 * Returns: integer, 0 for invalid, 1 for valid.
 */
public int
is_valid_weapon_for_spell(object weapon)
{
    if (!objectp(weapon) ||
        !(weapon->weapon_type() == "club"))
	
    {
        return 0;
    }
    return 1;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed *targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);

    if (!result)
    {
        return 0; // result is 0;
    }

    if (!IS_WEAPON_OBJECT(targets[0]))
    {
        hook_describe_non_weapon_target(caster);
        return 0;
    }
  
    if (!is_valid_weapon_for_spell(targets[0]))
    {
        hook_describe_weapon_shadow_no_valid_weapon_precast(caster);
        return 0;
    }
    
    if (!targets[0]->query_wielded())
    {
        hook_describe_weapon_target_not_wielded(caster, targets[0]);
    }

    return result;    
}

/*
 * Function for removing the shadow.
 */
void
remove_weapon_shadow(object shadow, object caster, object weapon_spell, object weapon)
{
  shadow->remove_shadow();
  weapon_spell->hook_weapon_shadow_spell_expired(caster, weapon);
}

/*
 * Function meant to be overriden to provide the duration of the weapon
 * effects provided by the shadow.
 */
public float
query_duration_time()
{
  return itof(1500);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets  - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    resolve_weapon_shadow_spell(caster, targets, resist, result);

    setuid();
    seteuid(getuid());

    if (!targets[0] || !is_valid_weapon_for_spell(targets[0]))
    {
        hook_describe_weapon_shadow_no_valid_weapon_postcast(caster);
        return;
    }
    
    weapon_shadow = clone_object(query_weapon_shadow());
    weapon_shadow->shadow_me(targets[0]);
    set_alarm(query_duration_time(), 0.0, &remove_weapon_shadow(weapon_shadow, caster, this_object(), targets[0]));
    hook_describe_weapon_shadow_success(caster, targets[0], weapon_shadow);
}

public void
hook_weapon_shadow_spell_expired(object caster, object weapon)
{
    caster->catch_tell("You feel the effects on your "+weapon->short()+" expire!\n");
}

/*
 * Function name : query_weapon_shadow
 * Description   : Retrieves the path to which shadow to use for
 *                 shadowing the weapon.
 *                 Indended to be overridden to supply specific shadow.
 * 
 * Returns       : The path to the shadow used to shadow the weapon.
 */
public string
query_weapon_shadow()
{
    return STD_SPELL_OBJ_DIR + "weapon_sh";
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_shadow_weapon_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 *
 * Arguments:   object caster   - the caster
 *              mixed *targets  - an array of targets
 *              int *resist     - resistance percentages corresponding to
 *                                each target
 *              int result      - how well the spell was cast
 */
public void
resolve_weapon_shadow_spell(object caster, mixed *targets, int *resist, int result)
{
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *)  The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed *targets, string arg)
{
    caster->catch_msg("You focus your energy on the " + targets[0]->short() + ".\n");

    tell_room(environment(caster), QCTNAME(caster) + " focuses " +
              caster->query_possessive() + " energy on the " +
              targets[0]->short() + ".\n", caster);
}

/*
 * Function:    hook_describe_weapon_shadow_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and the weapon is shadowed.
 */
public void
hook_describe_weapon_shadow_success(object caster, object weapon, object shadow)
{
    tell_room(environment(caster), QCTNAME(caster) + " casts a spell on the " +
              weapon->short() + ".\n", caster);

    caster->catch_msg("You cast your spell on the " + weapon->short() + ".\n");
}

/*
 * Function:    hook_describe_weapon_shadow_valid_gems_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find a valid weapon. Called from check_valid_action
 */
public void
hook_describe_weapon_shadow_no_valid_weapon_precast(object caster)
{
    caster->catch_tell("You don't have a valid weapon to perform the enchantment.\n");
}

/*
 * Function:    hook_describe_weapon_shadow_no_valid_weapon_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid weapon
 *              for the spell.
 */
public void
hook_describe_weapon_shadow_no_valid_weapon_postcast(object caster)
{
    caster->catch_tell("You realize much too late that you don't have a " +
                       "required weapon to perform the enchantment.\n");
}

public void
hook_describe_non_weapon_target(object caster)
{
    caster->catch_tell("You can only target weapons.\n");
}

public void
hook_describe_weapon_target_not_wielded(object caster, object weapon)
{
    caster->catch_tell("Your "+weapon->short()+" must be wielded during enchantment.\n");
}
