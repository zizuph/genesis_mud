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

#include "/d/Genesis/specials/local.h"

inherit "/d/Genesis/specials/new/magic/spells/unfinished/turn_undead";

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

#include <macros.h>
#include <tasks.h>

#include "../oots_god_descs.h"

/*
 * Function:    config_turn_undead_spell
 * Description: Config function for turn_undead spells. Redefine this in your
 *              own turn_undead spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_turn_undead_spell()
{
    set_spell_name("oturn");
    set_spell_desc("Turn undead - cause the unliving to flee your presence");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
        
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);
    
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(query_turn_undead_ingredients);

    set_spell_fail("Your prayer of intervention is unheard.\n");

    set_spell_object(OOTS_SPELL_OBJS + "oturn_obj");        
} 

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
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

    // Level 5 (Fervent Follower) spell
    if(OOTS_LEVEL(player) < 5)
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
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not align " +
           "with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    if("/d/Krynn/guilds/OotS/spells/obless"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy protection, and are unable " +
            "to maintain two prayers at the same time!\n");
        return 0;
    }

    if("/d/Krynn/guilds/OotS/spells/oprotect"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy protection, and are unable " +
            "to maintain two prayers at the same time!\n");
        return 0;
    }
      
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
    string caster_message, watcher_message;

        caster_message = "You raise your medallion of faith and call upon " 
              +oots_god_name(caster)+ " for righteous aid against the unliving!\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ " medallion of "+
              "faith and calls upon the " +oots_god_desc(caster)+ " " 
              +oots_god_name(caster)+" for aid against the unliving!\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());

}

public void
hook_describe_turn_undead(object caster, mixed * targets, int result)
{
    caster->catch_msg("Blazing light explodes from your medallion of faith, " +
		      "forcing " +COMPOSITE_LIVE(targets) +
		      " away from you through the radiant intervention of "
                      +oots_god_name(caster)+".\n");
    targets->catch_msg("Blazing light explodes from " +QTPNAME(caster) + 
                       " medallion of faith, forcing you backwards as the " +
                       "radiant intervention of a holy " +oots_god_desc(caster)+
                       " works against your undead form.\n");
    tell_room(environment(caster), "Blazing light explodes from " +QTPNAME(caster) +  
	      " medallion of faith, forcing " + COMPOSITE_LIVE(targets) +
	      " away through the radiant intervention of a "+oots_god_desc(caster)+"!\n",
	      ({ caster }) + targets, caster); 
}

/*
 * Function:    query_turn_undead_ingredients
 * Description: This function defines what components are required for
 *              this turn_undead spell.
 */
public string *
query_turn_undead_ingredients(object caster)
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
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed *
check_required_items(object actor, mixed * targets,string arg, int pretest)
{
    return filter(actor->query_clothing(-1), &is_valid_medallion(actor,));
}

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    mixed *items = check_required_items(this_player(), ({}), "", 0);
    return max(1, query_ability_power(this_player(), ({}), items));
}

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object caster, mixed *items)
{
    items = filter(items, &is_valid_medallion(caster,));
    
    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if(!sizeof(items))
    {
        if (random(10))
            return 0;
    }
    
    return 100;
} /* query_ability_item_modifier */