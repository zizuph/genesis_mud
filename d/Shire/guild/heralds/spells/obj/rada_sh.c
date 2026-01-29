/*
 * Rada shadow - locate herbs
 * Arman Kharas, May 2018
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "/d/Shire/common/defs.h"
#include "../../herald.h"

inherit "/d/Genesis/specials/new/magic/spells/objs/locate_sh.c";

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (!m_sizeof(paths[spell_object]))
    {
        target->catch_tell("The air around you is briefly filled with " +
            "the scent of spring flowers in bloom, before dissipating.\n");
        tell_room(environment(target), "The air is briefly filled with " +
            "the scent of spring flowers in bloom, before dissipating.\n", 
           ({ target }));
        return;
    }
    
    if (objectp(target))
    {
        target->catch_tell("The air around explodes with the scent of " +
            "spring flowers in bloom, while around you motes of " +
            "light like tiny sparkling fireflies form, before lightly " +
            "dropping to the ground to form a glimmering path before " +
            "you.\n");
        tell_room(environment(target), "The air explodes with " +
            "the scent of spring flowers in bloom!\nMotes of " +
            "light like tiny sparkling fireflies form around " +
            QTNAME(target)+ ", before lightly dropping to the ground.\n", 
           ({ target }));
    }
} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The glimmering path fades, leaving no " +
            "traces behind.\n");
    }
} /* hook_spell_effect_ended */

/*
 * Function name:   hook_spell_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object  caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel you won't be able to maintain " +
            "your channeling of Vana for much longer.\n");
    }
} /* hook_spell_effect_warn_fading */

/* 
 * Function name:   hook_spell_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       (object) spell_object - The effect object
 * Returns:         Nothing
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you cease channelling " +
            "Vana.\n");
    }
} /* hook_spell_effect_not_maintained */

/*
 * Function name:   hook_return_to_path
 * Description:     A hook for when you return to the path after having left it.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_return_to_path(object to, object from)
{
    shadow_who->catch_msg("You return to the glimmering path.\n");
} /* hook_return_to_path */

/*
 * Function name:   hook_follow_path
 * Description:     A hook for when you follow the path.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_follow_path(object to, object from)
{
    shadow_who->catch_msg("You follow to the glowing path.\n");
} /* hook_follow_path */

/*
 * Function name:   hook_end_of_path
 * Description:     A hook for when you reach the end of the path.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_end_of_path(object to, object from)
{
    shadow_who->catch_msg("You have reached the end of the glimmering " +
        "path.\n");
} /* hook_end_of_path */

/*
 * Function name:   hook_strayed_from_path
 * Description:     A hook for when you strayed from the path but have a chance
 *                  of returning to it.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_strayed_from_path(object to, object from)
{
    shadow_who->catch_msg("You have strayed from the glimmering path.\n");
} /* hook_strayed_from_path */

/*
 * Function name:   hook_abandoned_path
 * Description:     A hook for when you abandon the path, removing all traces.
 * Arguments:       1. (object) to      - The environment we are entering.
 *                  2. (object) from    - The environment we are leaving.
 * Returns:         Nothing
 */
public void
hook_abandoned_path(object to, object from)
{
    shadow_who->catch_msg("You abandon the glimmering path entirely.\n");
} /* hook_abandoned_path */

/*
 * Function name:   hook_path_description
 * Description:     A hook for displaying the path when glancing or looking.
 * Arguments:       1. (string *) exits - The array string list of exits.
 *                  2. (int) brief      - Brief of full description.
 * Returns:         Nothing
 */
public void
hook_path_description(string *exits, int brief)
{
    shadow_who->catch_msg("The glimmering path of light motes leads " + 
        COMPOSITE_WORDS(exits) + ".\n");
} /* hook_path_description */
