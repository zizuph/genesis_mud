/* 
 * Defence Master Ability
 *
 * Neidar gain a 40% combat aid evade bonus for a limited
 * time (30 seconds).  There is subsequently a 5 minute 
 * cooldown. This ability file simply clones the evade object
 *
 * Created by Petros, May 2009
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
    set_ability_name("dmaster");
    set_ability_offensive(0);
    set_ability_hasted(0); // no haste changes affect the timing of ability
    set_ability_prep_time(30);
    set_ability_cooldown_time(270); // 4.5 minute cooldown
    set_ability_target(target_actor);    
    set_ability_vocal(0);
    set_ability_visual(0);    
    set_ability_no_stun(0); // stun is checked in check_valid_action. need
                            // this here so that when the ability ends, it
                            // can properly remove the object.     
}

public void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_tell("You plant your feet firmly into the ground and "
        + "prepare yourself to endure the onslaught ahead!\n");
    actor->tell_watcher(QCTNAME(actor) + " plants "
        + actor->query_possessive() + " feet into the ground and "
        + "braces for the onslaught.\n");

    // Simply clone the defence master evade object
    setuid();
    seteuid(getuid());
    
    object evade_obj;
    
    evade_obj = clone_object(DEFENCE_MASTER_OBJ);
    evade_obj->set_effect_caster(actor);
    evade_obj->set_effect_target(actor);
    evade_obj->move(actor, 1);
    evade_obj->start();
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    // At the end of the preparation period, we remove the defence
    // master object
    object * effects;
    
    effects = filter(all_inventory(actor), &->is_neidar_defence_master_object());
    effects->remove_object();
    
    actor->catch_tell("You find yourself spent from your efforts to defend "
        + "yourself from the onslaught of attacks.\n");
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
    if (execute)
    {
        // No checks needed on end of the effect
        return 1;
    }
    
    if (!player->query_attack())
    {
        player->catch_tell("You cannot defend yourself when there is "
            + "no one to defend against!\n");
        return 0;
    }

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot defend yourself when you are "
            + "stunned!\n");
        return 0;
    }

    // If it passes everything, return success
    return ::check_valid_action(player, targets, arg, execute); 
}

public void
hook_already_active(object ability)
{
    write("You are already defending yourself as best as you can!\n");
}

public void
hook_special_complete()
{
    write("\nYou feel ready to defend yourself mightily again!\n\n");
}

public void
hook_special_in_cooldown()
{
    write("You are still recovering from the last time you braced "
        + "yourself.\n");
}
