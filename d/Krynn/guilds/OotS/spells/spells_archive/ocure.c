/*
 * pcure
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/cleanse";

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
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_cleanse_spell(void)
{
    set_ability_group(GUILD_NAME);
    set_spell_name("ocure");
    set_spell_desc("Cure inflictions - a prayer curing poisons and " +
                   "similar inflictions");

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_fail("Your prayer of curing is unheard.\n");

    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
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

    // Level 4 (Follower) spell
    if(OOTS_LEVEL(player) < 4)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({ "cranberry","elidross" });
}

void
hook_use_ingredients(object *ingrs)
{
    write("The petals fall from the delicate pale blue flower like " +
          "tears, and the red berry darkens and shrivels as your " +
          "prayer is answered.\n");

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
    return "cranberry, elidross";
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not " +
           "align with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    return 1;
}

/*
 * Function:    resolve_cleanse_spell
 * Description: Called at the beginning of resolve_spell in order to perform 
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result)
{

}

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
    object target = targets[0];

        caster_message = "You whisper a prayer, supplicating " +
              oots_god_name(caster)+ 
              " for the ability to cure the afflicted.\n";
        watcher_message = QCTNAME(caster) + " whispers a prayer to the "
              +oots_god_desc(caster)+ " " +oots_god_name(caster)+".\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
        object target = targets[0];
        if (caster == target)
        {
	    caster->catch_tell("You call upon the blessings of " +
                oots_god_name(caster)+
                " to purge you of poisons and inflictions.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " calls upon the blessings of " +oots_god_name(caster)+ 
            ".\n", targets);

        }
        else
        {
            caster->catch_msg("You call upon the blessings of " +
                oots_god_name(caster)+ " to cure "+ QTNAME(target) + 
                " of poisons and afflictions.\n");    
            target->catch_msg(QCTNAME(caster) + " calls upon the " +
                "blessings of " +oots_god_name(caster)+  
                " to cure you of poisons and afflictions.\n");
            tell_room(environment(caster), QCTNAME(caster) + 
                " calls upon the blessings of " +oots_god_name(caster)+ 
                " to cure "+ QTNAME(target) + " of poisons and " +
                "afflictions.\n", ({ caster, target }) );
        }
    
}

public void
hook_no_cleanseable_poisons(object caster, object target)
{
    caster->catch_tell("You find nothing to cure.\n");    
}

public void
hook_no_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You fail to cure any poisons from your body.\n");
   }
   else
   {
       caster->catch_msg("You fail to cure any poisons from "
        + QTPNAME(target) + " body.\n");
   }
}

public void
hook_all_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You successfully cure all poisons from your body.\n");
   }
   else
   {
       caster->catch_tell("You successfully cure all poisons from " +
                          COMPOSITE_LIVE(target)+ ".\n");
       target->catch_msg(QCTNAME(caster) + " cures all of your poisons.\n");
   }

    DEBUG("ocure xp all cleanse: 100.");
    OOTS_ADD_EXP(caster, 100);
}

public void
hook_some_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You manage to cure some of the poisons from " +
                         "your body.\n");
   }
   else
   {
       caster->catch_tell("You manage to cure some poisons from " +
        COMPOSITE_LIVE(target)+  ", but some still remain.\n");
       target->catch_msg(QCTNAME(caster) + " cures some of your poisons, "
        + "but some still remain.\n");
   } 

    DEBUG("ocure xp partial cleanse: 50.");
    OOTS_ADD_EXP(caster, 100);
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
     */
    if(!med[0]->query_worn())
    {
        if (random(10))
            return 0;
    }
        
    return ret;
}