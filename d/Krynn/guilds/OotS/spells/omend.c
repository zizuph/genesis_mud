/*
 * omend
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "regeneration";

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
 * Function:    config_regeneration_spell
 * Description: Config function for regeneration spells. Redefine this in your
 *              own regeneration spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_regeneration_spell()
{
    set_spell_name("omend");
    set_spell_desc("Blessed mending - a blessing of regeneration " +
                   "and mending");

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE,  30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);

    set_spell_combat_aid(15.0); // Max caid for this spell is 15
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // Can only cast obless on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(OOTS_SPELL_OBJS + "omend_obj");

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

    // Only castable by followers of Mishakal
    if(oots_god_name(player) != "Mishakal")
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_regeneration_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */
public string *
query_regeneration_ingredients(object caster)
{
    return ({ "_oots_holy_water", "fiddlehead" });
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
    return "fiddlehead, holy water";
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // If the player has defensive spells on, we reduce the
    // total combat aid provided by this spell.

    float caid_mod, align_mod;
    int caster_align = TP->query_alignment();

    if(caster_align < 1000)
    {
        align_mod = itof(caster_align) / 1000.0;
    }
    else
    {
        align_mod = 1.0;
    }

    caid_mod = 100.0 * align_mod;    

// DEBUG("Caid_mod: " +ftoi(caid_mod)+ " align_mod: " +ftoi(align_mod * 10.0));
    
    return caid_mod;
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

/*
    if("/d/Krynn/guilds/OotS/spells/oprotect"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy " +
            "protection, and are unable to maintain two prayers " +
            "at the same time!\n");
        return 0;
    }

    if("/d/Krynn/guilds/OotS/spells/obless"->has_spell_object(TP))
    {
        caster->catch_tell("You are currently maintaining a holy " +
            "protection, and are unable to maintain two prayers " +
            "at the same time!\n");
        return 0;
    }

    if(caster->query_feared_ec_shadow())
    {
        caster->catch_tell("You are currently focused on turning undead, and " +
            "are unable to maintain two prayers at the same time!\n");
        return 0;
    }
*/

    int c_aid = ftoi(query_spell_combat_aid());
    // DEBUG("Mend combat aid: " + c_aid);

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already blessed with a blessing of mending, and " +
    	    "the prayer has no effect.\n");
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
    write("You are missing an ingredient to invoke the blessing of mending!\n");
}


void
hook_use_ingredients(object *ingrs)
{
    write("Your prayers are granted as you swallow an unfurling green frond " +
          "and cleanse yourself with a phial of holy water.\n");

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
              oots_god_name(caster)+ " for a blessing of mending.\n";
        watcher_message = QCTNAME(caster) + " whispers a prayer to the "
              +oots_god_desc(caster)+ " " +oots_god_name(caster)+".\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
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