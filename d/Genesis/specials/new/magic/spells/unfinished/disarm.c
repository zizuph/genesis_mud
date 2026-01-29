/*
 * Base disarm spell
 *
 * In order to use an ability like this, you must inherit from this
 * function in order to adhere to the Genesis Balance standards.
 *
 * Created by Arman, October 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>

#include "defs.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

#define RECENTLY_SPELL_DISARMED   ("_recently_spell_disarmed")
#define HIS(x) ((x)->query_possessive())
#define HIM(x) ((x)->query_objective())

#define DEBUG(x)	     find_player("arman")->catch_msg("[Disarm] " + x + "\n")

// Prototypes
public void     resolve_disarm_spell(object caster, mixed * targets, int * resist, int result);
public string*  query_disarm_ingredients(object caster);
public void     resolve_spell_resisted(object caster, object target, int resist, int result);
public void     hook_describe_disarm(object caster, mixed * targets, int result);
public void     hook_no_weapons_wielded(object caster, object target);
public void     hook_disarm_cooldown(object caster, object target);

/*
 * Function:    config_disarm_spell
 * Description: Config function for disarm spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public varargs void
config_disarm_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);  
    
    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_combat_aid(50);

    // set_spell_object(STD_SPELL_OBJ_DIR + "disarm_obj");
    set_spell_object(SPELL_OBJ_DIR + "unfinished/disarm_obj");
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_offensive(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("disarm");
    set_spell_desc("spell of disarming");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_spell_ingredients(query_disarm_ingredients);

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.

    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);

    config_disarm_spell();

    // Call this after the config_disarm_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    set_disarm_duration
 * Description: Sets the percentage of time the silence is modified by
 *              depending on caid. In reality, it will actually set
 *              the combat aid after taking into account the effect
 *              percentage to combat aid calculation.
 * Arguments:   time, the percentage to make the target miss with.
 */

public void
set_disarm_duration(int percentage)
{
    // Effect => Combat Aid Formula
    // (100 * effect_percentage) / (100 - effect_percentage)
    // 50% of time disarmed equates to 100% combat aid.
    set_spell_combat_aid((100.0 * itof(percentage)) / (100.0 - itof(percentage)));
}

/*
 * Function:    query_disarm_duration
 * Description: Translates the combat aid back to the duration
 *              calculation.
 */

public int
query_disarm_duration()
{
    // Combat Aid => Effect formula
    // (100 * combat_aid) / (100 + combat_aid)
    // 50% combat aid disarm would equate to 33 seconds disarmed.
    // 100% combat aid equates to 50 seconds disarmed.
    float aid = query_spell_combat_aid();
    return ftoi((100.0 * aid) / (100.0 + aid));
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public nomask void
resolve_spell(object caster, mixed* targets, int* resist, int result)
{
    int duration = query_disarm_duration();

    resolve_disarm_spell(caster, targets, resist, result);
    
    hook_describe_disarm(caster, targets, result);
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        // Check resistance to see if the spell is resisted
        if (objectp(target) && resistance && resistance > random(100))
        {
            resolve_spell_resisted(caster, target, resistance, result);
            continue;
        }
    
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, target, resistance, result, duration);
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
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
    target->catch_msg("You resisted " + QTNAME(caster)+"'s spell.\n");
}

/*
 * Function:    query_disarm_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */

public string *
query_disarm_ingredients(object caster)
{
    return ({ });
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

    return 1;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
        
        if (!sizeof(target->query_weapon(-1)))
        {
        	hook_no_weapons_wielded(caster, target);
        	return 0;
        } 

        if (target->query_prop(RECENTLY_SPELL_DISARMED) > time())
        {
            hook_disarm_cooldown(caster, target);
            return 0;
        }      	 
    }
    
    return 1;
}

// HOOKS TO BE DEFINED
/*
 * Function:    resolve_disarm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_disarm_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_describe_disarm(object caster, mixed * targets, int result)
{
    caster->catch_msg("You extend your hands towards "+ COMPOSITE_LIVE(targets) +
		      " and feel mystical energy shoot out from your hands.\n");
    targets->catch_msg(QCTNAME(caster) + " extends " + HIS(caster) +
			  " hands, and mystical energy shoots out towards you.\n");
    tell_room(environment(caster), QCTNAME(caster) + " extends " + HIS(caster) + 
	      " hands towards " + COMPOSITE_LIVE(targets) +
	      ", causing a flash of energy to ignite between them.\n",
	      ({ caster }) + targets, caster);

}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been disarmed!\n"); 
    }
}

public void
hook_no_weapons_wielded(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has no weapons wielded!\n");
    }
}

/*
 * Function:    hook_disarm_cooldown
 * Description: Function that gets called to tell the caster that the cooldown
 *              is in effect.
 */
public void
hook_disarm_cooldown(object caster, object target)
{
    int wait_time = target->query_prop(RECENTLY_SPELL_DISARMED) - time();
    string seconds;

    if(wait_time > 60)
      seconds = "over a minute";
    else if(wait_time > 1)
      seconds = wait_time+ " seconds";
    else
      seconds = wait_time+ " second";

    caster->catch_msg(QCTNAME(target) + " was recently magically disarmed. You " +
            "will need to wait " +seconds+ " before you can magically " +
            "disarm " +target->query_objective()+ " again.\n");
}

/*
 * Function:    hook_no_disarm_message
 * Description: When it is not possible to disarm, for whatever reason,
 *              this message is given.
 * Arguments:   caster - person casting the spell
 *              target - the person being disarmed
 */
public void
hook_no_disarm_message(object caster, object target)
{
    caster->catch_tell("Your cannot seem to locate your target.\n");    
}
