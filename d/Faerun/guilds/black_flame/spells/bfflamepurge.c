/*
 * Flamepurge
 * By Nerull, 2022
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "cleanse";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"


/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_cleanse_spell(void)
{
    //set_ability_group(GUILD_NAME);
	
    set_spell_name("flamepurge");
    set_spell_desc(" - Purge internal toxins with fire water");

    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);

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

	if (player->query_guild_level_lay() >= GIFT_1)
    {
         return 1;
    }
    
	return 0;
}


/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({ "_flamepurge_charge" });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

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

    caster_message = "You invoke the power of Kossuth!\n";
    
    watcher_message = QCTNAME(caster)
    +" invokes the power of Kossuth!\n";

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
	        caster->catch_tell("You call upon the power of Kossuth " +
                " to purge you of poisons and inflictions.\n");
				
	        tell_room(environment(caster), QCTNAME(caster) +
	        " calls upon the purging power of Kossuth " + 
            ".\n", targets);

        }
        else
        {
            caster->catch_msg("You call upon the power of Kossuth " +
                " to purge "+ QTNAME(target) + 
                " of poisons and afflictions.\n");    
				
            target->catch_msg(QCTNAME(caster) + " calls upon the " +
                "power of Kossuth " +  
                " to purge you of poisons and afflictions.\n");
				
            tell_room(environment(caster), QCTNAME(caster) + 
                " calls upon the power of Kossuth " + 
                " to purge "+ QTNAME(target) + " of poisons and " +
                "afflictions.\n", ({ caster, target }) );
        }
    
}

public void
hook_no_cleanseable_poisons(object caster, object target)
{
    caster->catch_tell("You find nothing to purge.\n");    
}


public void
hook_no_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You fail to purge any poisons from your body.\n");
   }
   else
   {
       caster->catch_msg("You fail to purge any poisons from "
        + QTPNAME(target) + " body.\n");
   }
}


public void
hook_all_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You successfully purge all poisons from your body.\n");
   }
   else
   {
       caster->catch_tell("You successfully purge all poisons from " +
                          COMPOSITE_LIVE(target)+ ".\n");
						  
       target->catch_msg(QCTNAME(caster) + " purges all of your poisons.\n");
   }
}


public void
hook_some_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You manage to purge some of the poisons from " +
                         "your body.\n");
   }
   else
   {
       caster->catch_tell("You manage to purge some poisons from " +
        COMPOSITE_LIVE(target)+  ", but some still remain.\n");
		
       target->catch_msg(QCTNAME(caster) + " purges some of your poisons, "
        + "but some still remain.\n");
   } 
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
//public int
//query_ability_item_modifier(object caster, mixed *items)
//{
 //   return 100;
//} /* query_ability_item_modifier */  

int trolla()
{
	return 1;
}