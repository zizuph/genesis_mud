/*
 * Generic Protection from Dragon Fear Spell
 *
 * Dragonfear is an effect that was established in the Krynn/Ansalon
 * domains. We use a spell to provide protection from dragonfear
 * by changing the prop that allows one to be protected.
 *
 * Use of a Dragon Fear Protection spell must inherit from this
 * spell in order to be approved by the Genesis AoB team.
 * 
 * Created by Petros, July 2016
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/propchange_base";
#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_protect_dragonfear_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input);
public void hook_describe_cast_propchange(object caster, object* targets);

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */
public void
config_protect_dragonfear_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    
    // Set the effect shadow
    set_shadow_filename(STD_SPELL_OBJ_DIR + "protect_dragonfear_sh");
}

/*
 * Function:    query_protect_dragonfear_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments:   The caster of this spell
 */
public string *
query_protect_dragonfear_ingredients(object caster)
{
    return ({ });
}

public nomask void
config_propchange_spell()
{
    ::config_propchange_spell();

    set_spell_name("protect_dragonfear");
    set_spell_desc("protection from dragonfear");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_protect_dragonfear_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE,  20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);

    // Call the specific configuration that is to be masked.
    config_protect_dragonfear_spell();
}

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public nomask void
resolve_propchange_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
    resolve_protect_dragonfear_spell(caster, targets, resist, result, spell_input);
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_illfortunate_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_protect_dragonfear_spell(object caster, mixed * targets, int * resist,
                           int result, mapping spell_input)
{
}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_propchange(object caster, object* targets)
{
    caster->catch_tell("You cast a protect dragonfear spell upon " +
                       COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a protect dragonfear spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " already is under the protect dragonfear spell effects!\n");
}
