/*
 * /d/Ansalon/guild/dragonarmy/specials/summon_strike
 *
 * This is the dragon summoning ability for Dragonarmy that allows
 * them to summon a dragon to perform dragon attacks and have
 * dragonfear in the room.
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/timed_ability";
inherit "/d/Ansalon/guild/dragonarmy/specials/dragonarmy_utility";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define ROOM_I_NO_DRAGON "_room_i_no_dragon"


public void 
config_ability()
{
    ::config_ability();
    set_ability_name("summon dragonfear");
    set_ability_stationary(1);
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(85); // see query_ability_cooldown_time
    set_ability_target(target_actor);    
    set_ability_vocal(1);
    set_ability_visual(0);
    // Can be executed stunned, but cannot be started stunned
    set_ability_no_stun(0);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
}

public int
query_ability_cooldown_time()
{
    int soldier_lvl;
    
    soldier_lvl = this_player()->query_dragonarmy_rank_stat();
    return (::query_ability_cooldown_time() + soldier_lvl);
}



static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object dragon;
    int soldier_lvl;
    
    setuid();
    seteuid(getuid());
    
    dragon = DRAGONS_MANAGER->create_strike_dragon(actor);
    if (!dragon)
    {
        actor->catch_tell("You sense that the dragons leave mysteriously "
            + "for another place, and are unable to come.\n");
        return;
    }
    
    soldier_lvl = actor->query_dragonarmy_rank_stat();
    dragon->set_dragonfear_time(65 + soldier_lvl + random(40));
    dragon->follow_summoner();

    if(interactive(actor)) /* we log only use by players */
    {
    	log_file("dragonarmy_dragonfear", extract(ctime(time()),4,15) +
    	    ": " + actor->query_name() + " - " + file_name(E(actor)) +
    	    " - dragon avg. stat = " + dragon->query_average_stat() + "\n");
    }
}

public void
hook_special_complete()
{
  if ( IN_ARRAY(this_player(), users()) )
  {
    write("You feel you are once again able to summon "
        + "dragons to your aid.\n");    
  }
}

public void
hook_already_active(object ability)
{
    write("The dragons are on their way! Be patient!\n");
}

public void
hook_special_in_cooldown()
{
    write("You have yet to catch your breath from your last summoning.\n");
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
    object dragon, horn, oldtp;
    string msg;
    
    if(!IS_MEMBER(player))
    {
    	player->catch_tell("You have no idea how to summon a "
    	    + "dragon!\n");
    	return 0;
    }

    setuid();
    seteuid(getuid());
    if(!DRAGONS_MANAGER->dragonfear_dragon_age(player))
    {
        player->catch_tell("Dragons do not answer calls from someone so "
            + "low in the army.\n");
        return 0;
    }

    object enemy = player->query_attack();
    if (!execute)
    {
/*
        if (!objectp(enemy))
        {
            player->catch_tell("You don't think the dragons you are about to "
                + "call would be particularly impressed to find you summoned "
                + "them without even entering combat!\n");
            return 0;
        }
*/

/*     No problems with DA fighting amongst themselves! Evil turns on itself!
    
        if (enemy->query_dragonarmy_occ_member())
        {
        	player->catch_tell("No, you do not want your dragon to witness "
        	    + "your skirmishes with other dragonarmy soldiers.\n");
        	return 0;
        }

*/
    
        // Checking for horn only at beginning of ability.
        if (!objectp(horn = present("_dragonarmy_horn", player)))
        {
            player->catch_tell("You don't have anything that you can summon "
                + "a dragon with!\n");
            return 0;
        }

        if(player->query_prop(LIVE_I_ATTACK_DELAY) 
           || player->query_prop(LIVE_I_STUNNED))
        {
            /* Note that this is only called at the beginning of the 
            special. If the summoner is stunned at a later
            point of this sequence, that doesn't stop the 
            dragon from coming to his assistance. */
            player->catch_tell("You are too stunned to summon a "
                + "dragon.\n");
            return 0;
        }        
    }
    
    dragon = query_summoned_strike_dragon(player);
    if(objectp(dragon))
    {
        if (present(dragon, E(player)))
        {
            player->catch_tell("Your dragon is already here!\n");
            return 0;
        }
    }

    if(E(player)->query_prop(ROOM_I_INSIDE))
    {
        if (execute)
        {
        	player->catch_tell("The sensation you know as dragonfear "
        	    + "dissapears. Dragons probably departed your "
        	    + "neighbourhood.\n");
        }
        else
        {
        	player->catch_tell("You are not outdoors! The dragons would not "
        	    + "be able to reach you.\n");
        }
        return 0;
    }

    object dragonsteed;
    if (objectp(dragonsteed = query_summoned_dragonsteed(player))
        && dragonsteed->query_back() == environment(player))
    {
        // If on the back of a dragon, you can't summon a strike dragon
        player->catch_tell("You are already sitting on the back of your "
            + "dragonsteed. The dragons would not be able to reach you!\n");
        return 0;
    }
    
    if (!execute)
    {
        if (player->query_fatigue() < 30)
        {
            player->catch_tell("You are too exhausted to be able to summon "
                + "a dragon.\n");
            return 0;
        }
        
        if(player->query_mana() < 30)
        {
            player->catch_tell("You are not able to concentrate enough to "
                + "summon dragon.\n");
            return 0;
        }
    
        oldtp = this_player();
        set_this_player(player);
        horn->blow("_dragonarmy_horn");
        set_this_player(oldtp);
    
        player->add_mana(-30);

        int handle_check = player->query_dragonarmy_rank_stat();

        // Allowing soldiers to be able to summon dragons now
        // handle_check *= player->query_dragonarmy_promotions() - 1;
        handle_check *= player->query_dragonarmy_promotions();
        handle_check /= 2;
        if ((player->query_skill(SS_ANI_HANDL) < (40 + random(30)))
            || !random(handle_check))
        {
            player->catch_tell("You have a sinking feeling nothing is going "
                + "to answer your call.\n");
            return 0;
        }
    }
            
    return ::check_valid_action(player, targets, arg, execute);
}

private void
summon_dragon_stage_one(object player)
{
    if (!objectp(player))
    {
        return;
    }
    
    player->catch_tell("An eerie sensation that you recognise as " 
        + "dragonfear forewarns you of the approach of a dragon.\n");
    if(!E(player)->query_prop(ROOM_I_INSIDE))
    {
        tell_room(E(player), "The hairs on your neck suddenly rise, followed " 
            + "by an eerie sensation that makes you reflexively " 
            + "look up into the skies with concern.\n", player);
    }
}

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    set_alarm(prep_time / 2.0, 0.0, 
              &summon_dragon_stage_one(actor));
}

public void
hook_stopped_ability(object ability, object player)
{
    // Don't give any messages.    
}
