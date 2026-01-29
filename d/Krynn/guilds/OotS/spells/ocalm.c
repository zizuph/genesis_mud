/*
 * pHeal
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "calm";

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
 * Function:    config_calm_spell
 * Description: Config function for calm spells. Redefine this in your
 *              own calm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void 
config_calm_spell()
{
    set_spell_name("ocalm");
    set_spell_desc("Calming touch - provide divine reassurance");

    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 15);
    set_spell_fail("Your prayer is unheard.\n");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_1);

    set_spell_task(TASK_EASY);

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

    // Level 3 (Faithful) spell
    if(OOTS_LEVEL(player) < 3)
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_calm_ingredients
 * Description: This function defines what components are required for
 *              this calm spell.
 */
public string *
query_calm_ingredients(object caster)
{
    return ({ "dandelion" });
}

void
hook_use_ingredients(object *ingrs)
{
    write("The serrated leaf is blown away with the wind as " +
          "your prayer is granted.\n");

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
    return "dandelion";
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
 * Function:    resolve_calm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_calm_spell(object caster, mixed * targets, int * resist, int result)
{
    object target = targets[0];
    int panic = target->query_panic();
    int calm_xp = min(300, (result / 5));

    if(panic == 0)
    {
// DEBUG("ocalm no panic to heal, result " +result+ ".");
    }
    else
    {
// DEBUG("ocalm panic: " +panic+ ", result: " +result+ ", xp: " +calm_xp+ ".");
        OOTS_ADD_EXP(caster, calm_xp); 
    }
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

    
    if(target == caster)
    { 
        caster_message = "You grasp your medallion of faith, calling upon " 
              +oots_god_name(caster)+ " for divine courage.\n";
        watcher_message = QCTNAME(caster) + " grasps "+ HIS(caster)+ " " +
             "medallion of faith, calling upon the " +oots_god_desc(caster)+  
             " " +oots_god_name(caster)+" for divine courage.\n";

        caster->catch_tell(caster_message);
        tell_room(environment(caster), watcher_message, ({ caster }), caster);
    }
    else
    { 
        caster_message = "You grasp your medallion of faith, calling upon " 
              +oots_god_name(caster)+ " to provide divine courage to " +
              target->query_the_name(caster)+ ".\n";
        watcher_message = QCTNAME(caster) + " grasps "+ HIS(caster)+ " " +
             "medallion of faith, calling upon the " +oots_god_desc(caster)+  
             " " +oots_god_name(caster)+" to provide divine courage to " +
             QTNAME(target)+ ".\n";

        target->catch_tell(caster->query_The_name(target) + " grasps "+ 
             HIS(caster)+ " medallion of faith, calling upon the " 
             +oots_god_desc(caster)+ " " +oots_god_name(caster)+
             " to provide you with divine courage.\n");
        caster->catch_tell(caster_message);
        tell_room(environment(caster), watcher_message, ({ caster, target }), caster);
    }
    
    setuid();
    seteuid(getuid());  
}


/*
 * Function name: desc_calm_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                mapping calm_amounts - the amount calmed for each target
 */
public void
desc_calm_cast(object caster, mapping calm_amounts)
{
    object * targets = m_indices(calm_amounts);
    object * other_targets = targets - ({ caster });
    if (!IN_ARRAY(caster, targets))
    {
        caster->catch_tell("You call on the blessings of " +
            oots_god_name(caster) + " and calm " +
            FO_COMPOSITE_ALL_LIVE(other_targets, caster) + ".\n");
    } 
    else
    {
        if (sizeof(targets) == 1)
        {
            // Only casting on self
            caster->catch_tell("The divine blessings of " +
                oots_god_name(caster) + " calm you.\n");
        }
        else
        {
            caster->catch_tell("The divine blessings of " +
                oots_god_name(caster) + " calm " + 
                FO_COMPOSITE_ALL_LIVE(other_targets, caster)+ 
                " and yourself.\n");
        }
    }
    
    if (sizeof(other_targets))
    {
        other_targets->catch_msg("The blessings of " +
                oots_god_name(caster) + " calm you, providing " +
                "divine reassurance.\n");
    }
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
