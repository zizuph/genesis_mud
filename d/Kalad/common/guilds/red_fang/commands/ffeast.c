/*
 * This code handles the feast ability for the the Red
 * Fang racial guild in Kalad. It will let the wolf
 * feed on a corpse removing it just like a ingot from
 * Calia. Much of the code is stolen from the calian ingot.
 *
 * Created October 2017 by Zignur
 *
 *  20210803 Meton Fixed typo, visciously to viciously
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
    set_ability_name("ffeast");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(0);
    set_ability_cooldown_time(1);
    set_ability_vocal(1);
    set_ability_visual(0);    
    set_ability_target(target_actor);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    
    actor->catch_msg("You command your wolf to feast on a corpse.\n");
    tell_room(environment(actor), QCTNAME(actor) +
    " commands "+ actor->query_possessive() +
    " wolf to feast on a corpse.\n", actor);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object  mount,
            theorgan,
            corpse;
    object * wolves;
    mixed *leftovers;
    string racename;
    string str;
    int i;
    
    /* Find out if the wolf is in the room */
           
    /* Returns a array of all objects in the room with
     * query_owner == to this_player. Should never be more
     * than max one.
     */  
    wolves = filter(all_inventory(environment(actor)),
    &operator(==)(, actor->query_real_name()) @ &->query_owner());   
    
    /* First hit here will be the mount we want */
    mount = wolves[0];
    
    /* Do the feasting! Most of the code is stolen from the ingot */
    str = "corpse";
    corpse = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(corpse) || !IS_CORPSE_OBJECT(corpse))
    {
        /* This should never happen since we already did the check, but might
           as well do it again since we need to get the corpse object */
        actor->catch_msg("There is no corpse for your wolf to feast on.\n");
        return 0;
    }
    else 
    {
        leftovers = corpse->query_leftover();
        racename = corpse->query_race();

        setuid();
        seteuid(getuid());
        for (i=0; i < sizeof(leftovers);i++)
        {
            if (leftovers[i][2] == 0
            || (leftovers[i][3] != "" && leftovers[i][3] != 0))
            {
                // Don't clone the object if there are
                // none left available, or if there is VBFC
                continue;
            }
            theorgan = clone_object(leftovers[i][0]);
            if (IS_LEFTOVER_OBJECT(theorgan))
            {
               // Wizards can place non-leftovers as parts of the
               // corpse. In this case, these objects should not
               // have these leftover/heap specific functions
               // called.
            if (!stringp(leftovers[i][1]) || !intp(leftovers[i][2]))
            {
                continue;
            }
            // Sometimes leftover objects are just not set up correctly
            // we check the types to make sure that we don't throw
            // runtimes.
            theorgan->leftover_init(leftovers[i][1], racename);
            theorgan->set_heap_size(leftovers[i][2]);
            }
            theorgan->move(environment(TP));        
    }
    
     tell_room(environment(mount), "The " + mount->query_short() + " " +
        "savagely feasts upon the " +corpse->short_func() + "," +
        " viciously tearing limbs and body apart with teeth" +
        " and claws.\n", 0, mount);
       
    /* Remove the corpse */
    corpse->remove_object();
   }
}


public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("Your wolf is already feasting!\n");
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
    object mount, 
           corpse;
 
    object * wolves;
    string str;
    int i;
   
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
    
     /* See if we have a corpse in the room */
    str = "corpse";
    corpse = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(corpse) || !IS_CORPSE_OBJECT(corpse))
    {
        player->catch_msg("There is no corpse for your wolf to feast on!\n");
        return 0;
    }
         
    /* We cant command while being stunned */
    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot command your wolf while stunned.\n");
        return 0;
    }
    
    return 1; 
}




