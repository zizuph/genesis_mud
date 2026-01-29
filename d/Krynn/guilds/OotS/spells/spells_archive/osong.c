/*
 * osong
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/featherweight";

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
 * Function:    config_featherweight_spell
 * Description: Config function for featherweight spells. Redefine this in your
 *              own featherweight spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_featherweight_spell()
{
    set_spell_name("osong");
    set_spell_desc("Song of Freedom - a blessing reducing burden " +
                   "for the wanderer");

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE,  30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);

    set_spell_fail("You fail in your efforts to invoke the blessing.\n");

    // Can only cast osong on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(OOTS_SPELL_OBJS + "osong_obj");

    // Set the weight factor - 50% more weight capacity
    set_weight_factor(150);

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

    // Only castable by followers of Branchala
    if(oots_god_name(player) != "Branchala")
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
{
    return ({ "_oots_holy_water", "hawthorn" });
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
    return "hawthorn, holy water";
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

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already blessed with a Song of Freedom, and " +
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
    write("You are missing an ingredient to invoke the Song of Freedom!\n");
}

void
hook_use_ingredients(object *ingrs)
{
    write("Your prayers are granted as you solemnly swallow the red " +
          "berry and cleanse yourself with a phial of holy water.\n");

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

        caster_message = "You sing joyfully to " +oots_god_name(caster)+ 
              ", calling on blessing of freedom from burden!\n";
        watcher_message = QCTNAME(caster) + " sings joyfully to the "
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