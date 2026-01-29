/* 
 * Neidar Defend Ability
 *
 * Neidars have the ability to defend other Neidars.
 *
 * Created by Petros, May 2009
 * 
 * Modifications
 *  - fixed runtime when attacking defended target (Petros, September 2009)
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

public void 
config_ability()
{
    ::config_ability();
    set_ability_name("defend");
    set_ability_offensive(0);
    set_ability_hasted(0); // no haste changes affect the timing of ability
    set_ability_prep_time(0);
    set_ability_cooldown_time(10); 
    set_ability_target(target_one_present_living);    
    set_ability_vocal(0);
    set_ability_visual(1);
}

public void 
ability_msg(object actor, mixed * targets, string arg)
{
    // No preparation message
}

public void
set_defend_target(object player, object target)
{
    object defendee;
    object * evades;
    
    if (!objectp(target))
    {
        // If no target specified, defend self
        target = player;
    }
    
    // Remove the defend object from the currently defended person.
    if (objectp(defendee = player->query_prop(NEIDAR_BLOCK_TARGET)))
    {
        evades = defendee->query_evade_effects();
        evades = filter(evades, &->is_neidar_block_evade());
        evades = filter(evades, &operator(==)(player) @ &->query_effect_caster());
        evades->remove_object();
    }

    if (player == target)
    {
        if (!objectp(defendee))
        {
            // Already defending self. Just return.
            return;
        }
        
        // Want to defend myself again. Just unset the prop
        player->remove_prop(NEIDAR_BLOCK_TARGET);
        player->catch_tell("You are once again defending yourself.\n");
        return;
    }
    
    // Defending someone new. Add an evade object to them.
    player->add_prop(NEIDAR_BLOCK_TARGET, target);

    object neidar_block = clone_object(NEIDAR_BLOCK_OBJ);
    neidar_block->set_effect_caster(player);
    neidar_block->move(target, 1);
    neidar_block->start();         
    
    player->catch_msg("You move closer to " + QTNAME(target) + " so that "
        + "you can defend " + HIM(target) + ".\n");

    target->catch_msg(QCTNAME(player) + " moves closer to you in a defensive "+
                     "stance.\n");

    tell_room(environment(player), QCTNAME(player) + " moves closer to "
        + QTNAME(target) + " in a defensive stance.\n",
        ({ player, target }));
    
}

public void 
resolve_ability(object actor, mixed * items, mixed * targets, 
                int * resist, mixed * results)
{
    object target, defendee;
    object * evades;
    
    target = targets[0];
    
    set_defend_target(actor, target);        
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object target, defendee;
    
    if (execute)
    {
        // No checks needed on end of the effect
        return 1;
    }

    if (IS_DOOMSEEKER(player))
    {
    	player->catch_tell("Doomseekers have no interest in being defensive! " +
            "Be aggressive!\n");        
        return 0;
    }

    if (!player->query_attack())
    {
    	player->catch_tell("Maybe you should enter the fray if you hope "
    	    + "to be of use in defending anyone!\n");        
        return 0;
    }

    target = targets[0];
    if (!target->query_attack())
    {
        player->catch_msg(QCTNAME(target) + " is not engaged in battle "
            + "with anyone, so there is no point in defending "
            + target->query_objective() + ".\n");
        return 0;
    }
    
    object* target_enemies = target->query_enemy(-1);
    
    foreach (object target_enemy : target_enemies)
    {
        if (target_enemy == player)
        {
            player->catch_tell("Seems pretty silly to try and protect "
                + "someone who is attacking you. Have a death wish?\n");
            return 0;
        }
    }
    
    defendee = player->query_prop(NEIDAR_BLOCK_TARGET);
    if (defendee == target)
    {
        player->catch_msg("You are already defending " + QTNAME(target)
            + "!\n");
        return 0;
    }
    
    if (player == target && !objectp(defendee))
    {
        player->catch_tell("You are already defending yourself!\n");
        return 0;
    }
    
    // If it passes everything, return success
    return ::check_valid_action(player, targets, arg, execute); 
}

public void
hook_already_active(object ability)
{
    // already battleraging!
    write("You are already preparing to defend someone!\n");
}

public void
hook_special_complete()
{
    write("You feel ready to switch target of who to defend.\n");
}

public void
hook_special_in_cooldown()
{
    // don't allow switching defensive targets too often
	write("Patience! You can't so quickly move around to defend.\n");
}

/*
 * Function:    do_ability
 * Description: This is the first function called from the command
 *              soul. This allows someone to stop defending someone
 *              and get back to defending themselves.
 */
public int 
do_ability(string arg)
{
    object player = this_player();
    object defendee;
    
    if (!arg)
    {
        if (!objectp(defendee = player->query_prop(NEIDAR_BLOCK_TARGET)))
        {
            write("You are currently defending yourself.\n");
            this_player()->remove_prop(NEIDAR_BLOCK_TARGET);
        }
        else
        {
            player->catch_msg("You are currently defending "
                + QTNAME(defendee) + ".\n");
        }
        return 1;
    }
    
    arg = lower_case(arg);
    if (arg == "self" || arg == "myself" || arg == "stop")
    {               
        arg = interactive(this_player()) ? 
            this_player()->query_real_name() : OB_NAME(this_player());
    }
    
    return ::do_ability(arg);
}
