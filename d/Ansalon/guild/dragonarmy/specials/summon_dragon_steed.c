/*
 * /d/Ansalon/guild/dragonarmy/specials/summon_dragon_steed
 *
 * This is the steed summoning ability for Dragonarmy. It uses their
 * horn to blow a loud sound, summoning their steed.
 *
 * Created by Petros, February 2009
 *
 * Mana penalty for summoning a dragonsteed reduced from 200 to 65
 * mindful of the new magic system mana reallocation.
 * Arman, August 2017 
 *
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
    set_ability_name("summon steed");
    set_ability_stationary(1);
    set_ability_offensive(0);
    set_ability_hasted(0);
    // Takes 30 seconds to summon a dragon steed
    set_ability_prep_time(30);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);    
    set_ability_vocal(1);
    set_ability_visual(0);
    set_ability_no_stun(0);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{

}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object dragon;
    
    setuid();
    seteuid(getuid());
    
    dragon = DRAGONS_MANAGER->create_dragonsteed(actor);
    if (!dragon)
    {
        actor->catch_tell("The dragon flies away, unable to land where "
            + "you are.\n");
        return;
    }
    
    tell_room(E(actor), "With a final beat of its leathery wings, "+
      LANG_ADDART(dragon->short())+ " lands here.\n");
    dragon->move_living("M", E(actor));    
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
	write("Dragon is already on its way. Patience!\n");
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
    object dragon, horn, oldtp;
    string msg;
    
    if(!IS_MEMBER(player) || player->query_dragonarmy_promotions() < 2)
    {
    	player->catch_tell("You have no idea how to summon a "
    	    + "dragonsteed!\n");
    	return 0;
    }

    if (!execute)
    {
        // Checking for horn only at beginning of ability.
        if (!objectp(horn = present("_dragonarmy_horn", player)))
        {
            player->catch_tell("You don't have anything that you can summon "
                + "your dragonsteed with!\n");
            return 0;
        }
    }

    if (!player->query_relaxed_from_combat())
    {
        player->catch_tell("You need to relax a little before you can "
            + "summon your dragonsteed.\n");
        return 0;
    }
    
    dragon = query_summoned_dragonsteed(player);
    if(objectp(dragon))
    {
        if (present(dragon, E(player)))
        {
            player->catch_tell("Your dragon is already here!\n");
            return 0;
        }
        else if (dragon == E(player)->query_dragon())
        {
            player->catch_tell("You are sitting on your dragon!\n");
            return 0;            
        }
    }

    if(!CAN_SEE_IN_ROOM(player))
    {
        player->catch_tell("You can't see here. Maybe this place is not "
            + "suitable for dragon landing?\n");
        return 0;
    }

    if(E(player)->query_prop(ROOM_I_INSIDE))
    {
        player->catch_tell("Being inside, you doubt the dragon will be able "
            + "to reach you.\n");
        return 0;
    }

    if (E(player)->query_prop(ROOM_IN_WATER) 
        || E(player)->query_prop(ROOM_UNDER_WATER))
    {
        player->catch_tell("Unfortunately, a dragon is unable to land on "
            + "water.\n");
        return 0;
    }
    
    if (E(player)->query_prop(ROOM_IN_AIR))
    {
        player->catch_tell("Since you are in air dragon would not be able "
            + "land next to you.\n");
        return 0;
    }

    if (msg = E(player)->query_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND))
    {
        if (stringp(msg))
        {
            player->catch_tell(msg);
        }
        else
        {
            player->catch_tell("This spot is not suitable for dragon "
                + "landing.\n");
        }
        return 0;
    }

    if (!execute)
    {
        object * observers;
        observers = FILTER_LIVE(all_inventory(E(player))) - ({ player });
        observers = FILTER_CAN_SEE(observers, player);
        observers = filter(observers, &not() @ &->query_wiz_level());
        observers -= player->query_team_others();
        foreach (object observer : observers)
        {
            if (!IS_MEMBER(observer) && interactive(observer))
            {
                player->catch_tell("There are strangers watching here. You "
                    + "would rather not summon now.\n");
                return 0;
            }
        }

        oldtp = this_player();
        set_this_player(player);
        horn->blow("_dragonarmy_horn");
        set_this_player(oldtp);
    
        // Only reduce mana at the start of the summon
        if(player->query_mana() < 65)
        {
        	write("Your headache affects your sounding of " +
        	  "the horn. You doubt a dragon will answer your call.\n");
        	player->add_mana(-player->query_mana());
        	return 0;
        }
    
        player->add_mana(-65);

        if(E(player)->query_prop(ROOM_I_NO_DRAGON) != 0)
        {
            player->catch_tell("You blow the horn, but feel that your call "
                + "remains unheard.\n");
            return 0;
        }
        
        if (objectp(dragon))
        {
            dragon->check_back();
            if((dragon->query_back())->query_flying())
            {
                player->catch_tell("Your dragon seems to be busy. Try again "
                    + "later.\n");
                return 0;
            }
            
            // Instead of telling the room, we tell each living in the back
            // that isn't a relay object.
            object * passengers = FILTER_LIVING_OBJECTS(all_inventory(dragon->query_back()));
            foreach (object passenger : passengers)
            {
                if (IN_ARRAY("/d/Ansalon/guild/dragonarmy/dragons/relay.c",
                             inherit_list(passenger)))
                {
                    continue;
                }
                passenger->catch_tell("The dragon turns to you and snarls, "
                    + "making it very clear that you should dismount.\n"
                    + "You swiftly dismount.\n");
            }
            (dragon->query_back())->dismount_all();
            dragon->leave_area();
        }
    
        if (player->query_skill(SS_ANI_HANDL) < (40 + random(30)))
        {
            player->catch_tell("You have a sinking feeling nothing is going "
                + "to answer your call.\n");
            return 0;
        }
    }
            
    return ::check_valid_action(player, targets, arg, execute);
}


private void
summon_dragon_stage_two(object player)
{
    if (!objectp(player))
    {
        return;
    }
    
    if (!validate_ability_stationary(player, environment(player)))
    {
        stop_ability(player);
        player->catch_tell("The dragon you summoned will not come because "
            + "you have moved on.\n");
        return;
    }
    
    player->catch_tell("A cruel shriek from the skies alerts you to the " 
        + "dragon you summoned bearing down towards you with great "
        + "speed.\n");
    tell_room(E(player), "A cruel shriek from the skies alerts you to the "
        + "winged-form of a dragon bearing down upon you with great "
        + "speed!\n", player);

    return;
}

private void
summon_dragon_stage_one(object player, float prep_time)
{
    if (!objectp(player))
    {
        return;
    }
    
    if (!validate_ability_stationary(player, environment(player)))
    {
        stop_ability(player);
        player->catch_tell("The dragon you summoned will not come because "
            + "you have moved on.\n");
        return;
    }
    
    player->catch_tell("In the distance, like a dark star on the horizon, " 
        + "a winged-shaped creature makes its way towards you.\n");
    tell_room(E(player), "In the distance, like a dark star on the "
        + "horizon, a winged-shaped creature makes its way towards "
        + "you.\n", player);

    set_alarm(prep_time / 4.0, 0.0, 
              &summon_dragon_stage_two(player));    
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
    // We have two messages before the actual ability executes.
    // First message is about halfway in, and the second message
    // is about 75% of the way in.    
    set_alarm(prep_time / 2.0, 0.0, 
              &summon_dragon_stage_one(actor, prep_time));
}

public void
hook_changed_env()
{
    write("The dragon you summoned will not come because you have moved "
        + "on.\n");    
}

public void
hook_stopped_ability(object ability, object player)
{
    // Don't give any messages.    
}
