/*
 * Ice Shards Attack Spell for the Academy of Elemental Arts
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("hydrokine");
    set_spell_desc("Hurl icicles at your enemy");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_EASY);    

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_ABJURATION, 20);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    // One herb, and one leftover. No gem requirements
    return ({ "frosty raspberry", "_leftover_tooth" });
}

public int
query_spell_can_be_learned(object player)
{
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
    return ACADEMIC_MANAGER->acquired_water_spell(player);
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
    
    if (ACADEMIC_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules. Please see <help academic "
            + "rules>.\n");
        return 0;
    }
    
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
    string caster_message, watcher_message;
    switch (random(2))
    {
    case 0:
        caster_message = "You hold out your palm with the fingers pointed "
            + "away from you and focus on gathering the power of the "
            + "moisture in the air.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palm and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You summon your inner reserves of power and "
            + "focus your mind on utilizing the element of water.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    ACADEMIC_MANAGER->add_practice_level(caster, 2);
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Icicles fly towards you with great speed, but at "
            + "the last moment you are able to move aside and dodge them, "
            + "escaping unscathed.\n";
        watcher_message = "Icicles fly towards " + QTNAME(target) + " with "
            + "great speed, but at the last moment " + target->query_pronoun()
            + " is able to move aside and dodge them, escaping unscathed.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Swirling icicles strike you on the "
                + hitloc_desc + " and barely hurts you.\n";
            watcher_message = "Swirling icicles strike " + QTNAME(target)
                + " on the " + hitloc_desc + " and barely hurts "
                + target->query_objective() + ".\n";
            break;
            
        case 1..2:
            target_message = "Sharp icicles dig deeply into your " + hitloc_desc
                + " and cause you to bleed.\n";
            watcher_message = "Sharp icicles dig deeply into " + QTPNAME(target)
                + " " + hitloc_desc + " and cause " + target->query_objective()
                + " to bleed.\n";
            break;
            
        case 3..5:
            target_message = "You turn your body to try and dodge the many ice "
                + "shards hurtling towards you, but are unable to keep them from "
                + "skewering your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) + " turns " 
                + target->query_possessive() + " body to try and dodge the many "
                + "ice shards hurtling towards " + target->query_objective()
                + ", but " + target->query_pronoun() + " is unable to keep them "
                + "from skewering " + target->query_possessive() + " "
                + hitloc_desc + ".\n";
            break;
            
        case 6..9:
            target_message = "White icicles strike you and break upon "
                + "contact into extremely sharp shards, slashing you on your "
                + hitloc_desc + " and causing many wounds.\n";
            watcher_message = "White icicles strike " + QTNAME(target) + " and "
                + "break upon contact into extremely sharp shards, slashing "
                + target->query_objective() + " on " + target->query_possessive()
                + " " + hitloc_desc + " and causing many wounds.\n";
            break;
            
        case 10..15:
            target_message = "Flying past you at tremendous speeds, the icicles "
                + "seem to miss you, but at the last moment they come hurtling "
                + "back and pierce your " + hitloc_desc + " deeply.\n";
            watcher_message = "Flying past " + target->query_objective() + " at "
                + "tremendous speeds, the icicles seem to miss " 
                + target->query_objective() + ", but at the last moment they come "
                + "hurtling back and pierce " + target->query_possessive()
                + " " + hitloc_desc + " deeply.\n";
            break;
            
        case 16..25:
            target_message = "Sharp icicles strike your " + hitloc_desc + " and "
                + "dig into your skin before exploding inside of you, causing "
                + "piercing pain.\n";
            watcher_message = "Sharp icicles strike " + QTNAME(target) + " on the "
                + hitloc_desc + " and dig into " + target->query_possessive()
                + " skin before exploding inside of " + target->query_objective()
                + ", causing piercing pain.\n";
            break;
            
        case 26..40:
            target_message = "Jagged sharp icicles crash into you from "
                + "all sides, striking you in quick succession on your "
                + hitloc_desc + ", forcing you to your knees.\n";
            watcher_message = "Jagged sharp icicles seem to crash into "
                + QTNAME(target) + " from all sides, striking "
                + target->query_objective() + " in quick succession on "
                + target->query_possessive() + " " + hitloc_desc + ", forcing "
                + target->query_objective() + " to " 
                + target->query_possessive() + " knees.\n";
            break;
                    
        case 41..65:
            target_message = "The searing cold of the icicles freezes your "
                + hitloc_desc + " before hammering into you, shattering "
                + "your skin and causing great pain.\n";
            watcher_message = "The searing cold of the icicles freezes "
                + QTPNAME(target) + " " + hitloc_desc + " before hammering "
                + "into " + target->query_objective() + ", shattering "
                + target->query_possessive() + " skin and causing great "
                + "pain.\n";
            break;
            
        default:
            target_message = "Exploding into sight, hundreds of icicles "
                + "pummel you on your " + hitloc_desc + ", bursting apart both "
                + "inside and outside of your body, causing extreme "
                + "internal bleeding and damage.\n";
            watcher_message = "Exploding into sight, hundreds of icicles "
                + "pummel " + QTNAME(target) + " on " + target->query_possessive()
                + " " + hitloc_desc + ", bursting apart both inside and outside "
                + "of " + target->query_possessive() + " body, causing extreme "
                + "internal bleeding and damage.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
    
    target = targets[0];
    
    switch (random(2))
    {
    case 0:
        caster_message = "Ice begins to form at your fingertips and "
            + "gradually grows into large icicles. You direct them towards "
            + QTNAME(target) + ".\n";
        target_message = "Icicles form at " + QPNAME(caster) + " fingertips "
            + "as " + caster->query_pronoun() + " pushes out "
            + caster->query_possessive() + " palm towards you.\n";
        watcher_message = "Icicles form at " + QTPNAME(caster) + " fingertips "
            + "as " + caster->query_pronoun() + " pushes out "
            + caster->query_possessive() + " palm towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "White and blue energies swirl around your "
            + "outstretched palm and form into brilliantly white sharp "
            + "icicles. You push them towards " + QTNAME(target) + ".\n";
        target_message = "White and blue energies swirl around the "
            + "outstretched palm of " + QTNAME(caster) + " as "
            + caster->query_pronoun() + " pushes out the sharp forming "
            + "icicles towards you.\n";
        watcher_message = "White and blue energies swirl around the "
            + "outstretched palm of " + QTNAME(caster) + " as "
            + caster->query_pronoun() + " pushes out the sharp forming "
            + "icicles towards " + QTNAME(target) + ".\n";        
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need both a frosty raspberry herb and a tooth to generate "
        + "the manifestation of hydrokine.\n");
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        "tooth, frosty raspberry"));
}
