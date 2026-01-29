/*
 * Turn Undead Spell for the OotS - Arman 2017
 *
 * Shamelessly borrowed from the Elemental Cleric Guild of Calia
 * using their caster/target shadows for consistency
 *
 * Originally created by Jaacar, March 2017
 */


#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/unfinished/turn_target";

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include <macros.h>
#include <tasks.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

#include "../oots_god_descs.h"

/*
 * Function name:   validate_turn_target_effect
 * Description:     Determines if the fear is situationally successful.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         (status) 1: Successful
 *                           0: Failed
 */
public status
validate_turn_target_effect(object spell_object)
{
    object  caster = spell_object->query_spell_effect_caster(),
            target = spell_object->query_spell_effect_target();
    
    int success = caster->resolve_task(
    TASK_ROUTINE,   ({  SKILL_WEIGHT, 40, TS_INT, SKILL_WEIGHT, 40, TS_WIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_LIFE,
                        SS_SPELLCRAFT, SKILL_END }),
    target,         ({  SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 60, TS_DIS,
                        SKILL_WEIGHT, 20, SKILL_AVG, SS_ELEMENT_DEATH,
                        target->query_prop(LIVE_I_UNDEAD), SKILL_END}));
    
    if (success < 0)
        return 0;
    
    return 1;
} /* validate_turn_target_effect */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object  target = spell_object->query_spell_effect_target(),
            caster = spell_object->query_spell_effect_caster();
    
    if (objectp(caster) && objectp(target))
    {
        target->catch_tell("Your fear of " + caster->query_the_name(target)
        + " subsides.\n");
        
        caster->catch_tell("You sense that the righteous intervention " +
          "against " + target->query_the_name(caster) + " is now gone.\n");
    }
} /* hook_spell_effect_ended */

public object *
target_one_present_undead_or_enemy(object actor, string str)
{
    object *enemies, enemy = actor->query_attack();

    if (!strlen(str))
    {
        if (!enemy || 
            /* This shouldn't happen, but we'll check just in case */
            !present(enemy, environment(actor)))
        {
            actor->catch_tell("You aren't fighting anyone!\n");
            return ({});
        }
        return ({ enemy });
    }

    enemies = PARSE_THIS(str, "[at] / [on] [the] %l");
    
    if (!sizeof(enemies))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (!sizeof(enemies = filter(enemies, &->query_prop(LIVE_I_UNDEAD))))
    {
        actor->catch_tell("You are only able to turn undead.\n");
        return ({});
    }
    
    if (sizeof(enemies) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
    
    return enemies;
}

/*
 * Function:    config_turn_target_spell
 * Description: Config function for turn_target spells. Redefine this in your
 *              own turn_target spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_turn_target_spell()
{
    set_spell_name("oturn");
    set_spell_desc("Turn undead - cause the unliving to flee your presence");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
        
    set_locate_limit(3);
    set_turn_target_visual(0);
    
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);
    
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(query_turn_target_ingredients);
    set_spell_fail("Your prayer of intervention is unheard.\n");
    set_spell_target(target_one_present_undead_or_enemy);
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    /*
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    // Level 5 (Fervent Follower) spell
    if(OOTS_LEVEL(player) < 5)
    {
        return 0;
    }*/

    return 1;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
/*
    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not align " +
           "with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    if("/d/Krynn/guilds/OotS/spells/obless"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy protection, " +
            "and are unable to maintain two prayers at the same time!\n");
        return 0;
    }

    if("/d/Krynn/guilds/OotS/spells/oprotect"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy protection, " +
            "and are unable to maintain two prayers at the same time!\n");
        return 0;
    }
  */    
    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been turned!\n");
    }
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your prayer.\n");
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
    caster->catch_tell("You raise your medallion of faith and call upon "
    + oots_god_name(caster) + " for righteous aid against the unliving!\n");
    
    tell_room(environment(caster), QCTNAME(caster) + " raises " + HIS(caster)
    + " medallion of faith and calls upon the " + oots_god_desc(caster) + " "
    + oots_god_name(caster) + " for aid against the unliving!\n", ({ caster }),
    caster);
}

/*
 * Function:    query_turn_target_ingredients
 * Description: This function defines what components are required for
 *              this turn_target spell.
 */
public string *
query_turn_target_ingredients(object caster)
{
    return ({ "_oots_holy_water" });
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
    return "holy water";
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
    write("You are missing a phial of holy water to turn undead!\n");
}

void
hook_use_ingredients(object *ingrs)
{
    write("A phial of holy water turns to vapor as your prayer is answered.\n");
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("oots_guild_object"))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(caster,));

    int ret = ::query_casting_success(caster);

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     *
    if(!med[0]->query_worn())
    {
        if (random(10))
            return 0;
    }*/
        
    return ret;
}

/*
 * Function name:   resolve_turn_target_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_turn_target_spell(object caster, object *targets, int *resist, int result,
                     mapping paths)
{
    caster->catch_msg("Blazing light explodes from your medallion of faith, "
    + "forcing " + COMPOSITE_LIVE(targets) + " away from you through the "
    + "radiant intervention of " + oots_god_name(caster) + ".\n");
    
    targets->catch_msg("Blazing light explodes from " +QTPNAME(caster)
    + " medallion of faith, forcing you backwards as the radiant intervention "
    + "of a holy " + oots_god_desc(caster) + " works against your undead "
    + "form.\n");
    
    tell_room(environment(caster), "Blazing light explodes from "
    + QTPNAME(caster) + " medallion of faith, forcing "
    + COMPOSITE_LIVE(targets) + " away through the radiant intervention of a "
    + oots_god_desc(caster)+"!\n", ({ caster }) + targets, caster);
} /* resolve_locate_spell */