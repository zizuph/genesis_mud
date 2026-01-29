/*
 * pdetect
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/spells/alignment";

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
config_alignment_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("odetect");
    set_spell_desc("Detect evil - detect the presence of evil on a target");

    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_ABJURATION, 15);
    set_spell_fail("Your prayer is unheard.\n");

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
query_alignment_ingredients(object caster)
{
    return ({  });
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
    return "no prayer components";
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
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_alignment_spell(object caster, mixed * targets, int * resist, int result)
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

        caster_message = "You grasp your medallion of faith, calling upon " 
              +oots_god_name(caster) + " for divine knowledge.\n";
        watcher_message = QCTNAME(caster) + " grasps "+ HIS(caster) + 
             " medallion of faith, calling upon the " +
             oots_god_desc(caster) + " " +oots_god_name(caster) +
             " for divine knowledge.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{
    if (target_alignment > 0) 
    {
        caster->catch_msg("You do not sense the presence of evil around " + 
                          QTNAME(target) + ".\n");
    }
    else
    {
        switch(target_alignment)
        {
           case -1200..-1001:
             caster->catch_msg("You sense a profound blackness around " + 
                              QTNAME(target) + ", indicating " +
                              HE(target)+ " walks a vile path of regular " +
                              "atrocities, and is damned in the eyes of " +
                              oots_god_name(caster)+ ".\n");
             break;
           case -1000..-601:
             caster->catch_msg("You sense a great darkness around " + 
                               QTNAME(target) + ", indicating " +
                               HE(target)+ " walks an evil and " +
                               "depraved path.\n");
             break;
           case -600..-201:
             caster->catch_msg("You sense a darkness around " + 
                               QTNAME(target) + ", indicating " +
                               HE(target)+ " walks an immoral path.\n");
             break;
           case -200..-1:
             caster->catch_msg("You sense a slight darkness around " + 
                               QTNAME(target) + ", indicating " +
                               HE(target)+ " has started down an " +
                               "immoral path.\n");
             break;
           case 0:
             caster->catch_msg("You sense that " + QTNAME(target) + 
                               " is neither good nor evil, a blank " +
                               "slate that is neither enlightened " +
                               "nor damned.\n");
             break;
         }
    }

    target->catch_msg(QCTNAME(caster) + " examines you with a knowing gaze.\n");
    tell_room(environment(caster), QCTNAME(caster)+ " examines " +
          QTNAME(target) + " with a knowing gaze.\n", 
          ({ caster, target }), caster);
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