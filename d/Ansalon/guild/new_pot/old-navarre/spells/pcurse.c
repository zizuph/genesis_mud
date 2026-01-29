/*
 * This spell is a generic version of the curse of the illfortunate.
 * It cause the target to have a harder time hitting his targets.
 *
 * Created by Navarre May 2013.
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <ss_types.h>
#include "../defs.h"

inherit "/d/Genesis/specials/std/spells/illfortunate";

/*
 * Function:    config_illfortunate_spell
 * Description: Config function for illfortunate spell. Redefine this in your
 *              own illfortunate spells to override the defaults.
 */
public void
config_illfortunate_spell()
{
    set_spell_name("pcurse");
    set_spell_desc("Place Curse of Illfortunate");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    
    set_spell_object(POT_SPELL_OBJS + "pcurse_obj");
    set_percentage_miss(100);
    set_spell_element(SS_ELEMENT_DEATH,  20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
}

/*
 * Function: query_illfortunate_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments: The caster of this spell
 */
public string*
query_illfortunate_ingredients(object caster)
{
    return ({});
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_illfortunate_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_illfortunate_spell(object caster, mixed* targets, int* resist,
                           int result)
{

}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_illfortunate(object caster, object* targets)
{
    caster->catch_tell("You cast a curse spell upon " +
                       COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a curse spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already cursed!\n");
}


/*
 * Function:    hook_curse_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_illfortunate_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " are " +
                      "not affected by your spell.\n");
    targets->catch_msg("You shrug off an attempt by " + QTNAME(caster) +
                       "to curse you.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in " +
                         "trying to curse " + COMPOSITE_LIVE(targets) + ".\n",
                         ({ caster }) + targets);
}
