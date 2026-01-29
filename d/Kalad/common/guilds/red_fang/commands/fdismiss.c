/*
 * This code handles the dismiss ability for the the Red
 * Fang racial guild in Kalad.
 *
 * Created October 2017 by Zignur
 *
 */
 
#pragma strict_types

#include "/d/Kalad/defs.h"

inherit "/d/Genesis/specials/timed_ability";
#include "/d/Kalad/common/guilds/red_fang/default.h"
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

public void config_ability()
{
    ::config_ability();
    set_ability_name("fdismiss");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(0);
    set_ability_vocal(1);
    set_ability_visual(0);    
    set_ability_target(target_actor);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    
    actor->catch_msg("You bark a command to your wolf, dismissing it.\n");
    tell_room(environment(actor), QCTNAME(actor) +
    " barks a command to "+ actor->query_possessive() +
    " wolf, dismissing it.\n", actor);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object  mount;
    object * wolves;
    int wolf_health;
    int wolf_fatigue;
    int dismiss_time; 

    dismiss_time = time();
   
    /* Find out if the steed is in the room */
           
    /* Returns a array of all objects in the room with
     * query_owner == to this_player. Should never be more
     * than max one.
     */ 
    wolves = filter(all_inventory(environment(actor)),
    &operator(==)(, actor->query_real_name()) @ &->query_owner());   
    
    /* First hit here will be the mount we want */
    mount = wolves[0];
        
    tell_room(environment(mount), "The " + mount->query_short() + 
    " slips away into the shadows and is gone.\n", mount);

    /* Add health check props to the player */
    wolf_health = mount->query_hp();
    actor->add_prop(WOLF_HEALTH, wolf_health);

    /* Add fatigue check props to the player */
    wolf_fatigue = mount->query_fatigue();
    actor->add_prop(WOLF_FATIGUE, wolf_fatigue);

    actor->add_prop(WOLF_DISMISS_TIME, dismiss_time);
    
    /* Remove the wolf */
    mount->remove_object();
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already dismissing your wolf.\n");
}

public void
hook_special_in_cooldown()
{
    
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
    object mount;
    object * wolves;
    
    /* See if our wolf is in the room */
    /* Returns a array of all objects in the room with
     * query_owner == to this_player. Should never be more
     * than max one.
    */
    wolves = filter(all_inventory(environment(player)),
    &operator(==)(, player->query_real_name()) @ &->query_owner());
    
    if (sizeof(wolves ))
    {
        // Means our wolf is present in the room
        mount = wolves[0];
            
    }
    /* The wolf is not present */
    else
    {
        player->catch_msg("Your wolf is not here.\n");
        return 0;           
    }
    
    /* We cant dismiss while being stunned */
    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot dismiss your wolf while stunned.\n");
        return 0;
    }
    
    /* Have to dismount first */
    if (player->query_prop(LIVE_O_STEED) == mount)
    {
        player->catch_msg("You need to dismount your wolf first.\n");
        return 0;
    }
        
    return 1; 
}
