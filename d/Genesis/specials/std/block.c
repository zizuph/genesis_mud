/*
 * /d/Genesis/specials/std/block.c
 *
 * This is the block ability. It blocks by placing a block shadow
 * on the person being blocked. The block shadow will do all the
 * necessary checking.
 *
 * Created by Novo, adapted to use resolve_task by Petros
 *
 * Modifications:
 *   - Allowed stopping of block when it is dark, Petros, April 2009
 *   - Changed prep_time to 3 seconds in the query_ability_prep_time
 *     function and set it to nomask. - Carnak, June 2021
 */
 
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "defs.h"
#include "block_defs.h"

inherit TIMED_ABILITY_LIB;
inherit BLOCK_LIB;

#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

public mixed * target_block(object actor, string str);

/*
 * Function name:   disable_pvp_abilities
 * Description:     Created to enable the override of pvp abilities.
 * Arguments:       (object) actor
 * Returns:         (status) 1 - Abilities disabled
 *                           0 - Abilities enabled
 */
public nomask status
disable_pvp_abilities(object actor)
{
    return PVP_ABILITY_DISABLED;
} /* disable_pvp_abilities */

public void config_ability()
{
    ::config_ability();
    set_ability_prep_time(5);
    set_ability_cooldown_time(0);
    set_ability_name("block");
    set_ability_offensive(0); // no longer offensive, blocks exit
    set_ability_stationary(1);
    set_ability_visual(0);
    set_ability_target(target_block);
    set_ability_target_verify(0);
    set_ability_hasted(0);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->reveal_me(1);

    if (query_block_exit(actor) == targets[0]
        && query_block_room(actor) == MASTER_OB(environment(actor)))
    {
        actor->catch_tell("You focus on positioning yourself again "
            + "to effectively block the " + targets[0] + " exit.\n");
    }
    else
    {    
        // If not reblocking the same exit, we remove all blocking
        actor->remove_blocker_shadow();
        actor->catch_tell("You focus on ways to position yourself "
            + "to effectively block the " + targets[0] + " exit.\n");
    }
    tell_room(environment(actor), QCTNAME(actor) + " begins to position "
        + actor->query_objective() + "self to prevent you from "
        + "escaping this room.\n", ({ actor }) );
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    object block_shadow, blocker_shadow, room;
    object * other_livings, * unblockable;
    string exit, roomfile;
    
    if (!targets || !sizeof(targets) 
        ||!stringp(targets[0]))
    {
        return;
    }
    
    actor->reveal_me(1);
    exit = targets[0];
    room = environment(actor);
    roomfile = MASTER_OB(room);
    other_livings = FILTER_LIVING_OBJECTS(all_inventory(room));
    other_livings -= ({ actor });
    
    setuid();
    seteuid(getuid());
    
    if (!actor->has_blocker_shadow())
    {
        blocker_shadow = clone_object(BLOCKER_SH);
        if (!blocker_shadow->shadow_me(actor)) 
        {
            blocker_shadow->remove_shadow();
            return;
        }
    }
    
    if (query_block_room(actor) != roomfile)
    {
        // Room has changed
        set_block_room(actor, roomfile);
        // Reset strengths
        reset_block_strength(actor);
    }
    set_block_exit(actor, exit);    
    unblockable = ({ });
    foreach (object blockee : other_livings)
    {
        if (!blockee->has_block_shadow())
        {
            block_shadow = clone_object(BLOCK_SH);
            if (catch(block_shadow->shadow_me(blockee)))
            {
                unblockable += ({ blockee });
                send_debug_message("block", MASTER_OB(blockee) + " cannot be "
                    + "shadowed.", BLOCK_LOG);
                block_shadow->remove_shadow();
                continue;
            }
        }

        // One can define certain conditions that may allow a "friend" to be
        // free from the blocking effects. This is generally used only by
        // npcs. Simply implement the function "query_ignore_block" to
        // return something non-zero.
        if (actor->query_ignore_block(blockee))
        {
            continue;
        }
        set_block_is_blocking(actor, blockee);
    }
    
    object * blockees = filter(FILTER_LIVING_OBJECTS(all_inventory(environment(actor))), 
        &query_block_is_blocking(actor,));
    if (sizeof(unblockable))
    {
        actor->catch_tell("You move yourself into position "
            + "to block the " + exit + " exit, but you sense that you "
            + "cannot fully block the exit here.\n");
    }
    else if (!sizeof(blockees))
    {
        actor->catch_tell("You move yourself into position "
            + "to block the " + exit + " exit, but find no one to block.\n");
        actor->remove_blocker_shadow();
        return;
    }
    else      
    {
        actor->catch_tell("You successfully move yourself into position "
            + "to block " + COMPOSITE_LIVE(blockees) + " from leaving through "
            + "the " + exit + " exit.\n");
    }        
    send_debug_message("block", capitalize(actor->query_real_name())
         + " blocks the " + exit + " exit in the room "
         + roomfile, BLOCK_LOG);
    tell_room(environment(actor), QCTNAME(actor) + " is now "
        + "in position to block the " + exit + " exit.\n", ({ actor }));
}

public mixed *
target_block(object actor, string str)
{
    if (!strlen(str))
    {
        if (query_block_room(actor) == MASTER_OB(environment(actor))
            && strlen(query_block_exit(actor)))
        {
            actor->catch_tell("You are currently blocking the "
                + query_block_exit(actor) + " exit.\n");
        }
        else
        {
            actor->catch_tell("Block which exit?\n");
        }
        return ({ });
    }

    // Get all the normal exits
    string * names = ({ "stop" });
    
    mixed exits = environment(actor)->query_exit();

    for (int i = 1; i < sizeof(exits); i += 3)
    {
        // exits array is list of location, exit, function
        // so we need to get the 2nd item of each triplet
        names += ({ exits[i] });
    }

    string * localcmds = get_localcmd(actor);
    if (IN_ARRAY("climb", localcmds))
    {
        names += ({ "climb" });
    }
    if (IN_ARRAY("enter", localcmds))
    {
        names += ({ "enter" });
    }
    if (IN_ARRAY("swim", localcmds))
    {
        names += ({ "swim" });
    }

    // Now check for door exits
    object * objects = FILTER_DOOR_OBJECTS(all_inventory(environment(actor)));
    foreach (object obj : objects)
    {
        string * pass_commands = obj->query_pass_command();
        if (pointerp(obj))
        {
            names += pass_commands;
        }
    }

    if (!sizeof(names) || !IN_ARRAY(str, names))
    {
        actor->catch_msg("You find no " + str + " exit to block.\n");
        return ({ });
    }

    return ({ str });
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed * targets, string arg, int execute)
{
    string exit, room;
    
    if (actor->query_prop(PLAYER_I_CANNOT_BLOCK))
    {
        mixed message = actor->query_prop(PLAYER_I_CANNOT_BLOCK);
        if (strlen(message))
        {
            actor->catch_msg(message);
        }
        else
        {
            actor->catch_tell("Try as you might, you cannot seem to "
                              + "position yourself to block an exit at "
                              + "the moment.\n");
        }
        return 0;
    }

    if (environment(actor)->query_prop(ROOM_M_NO_ATTACK))
    {
        actor->catch_tell("Try as you might, you cannot seem to "
            + "position yourself to block an exit in this room.\n");
        return 0;
    }
    
    if (actor->query_skill(SS_BLOCK) == 0)
    {
        send_debug_message("block", actor->query_real_name() + " "
                         + "has no blocking skill");
        // The blocker has no skill, therefore no blocking allowed.
        actor->catch_tell("You have no idea how to block.\n");
        return 0;
    }    
    
    // Cannot block when invisible. reveal_me is called for OBJ_I_HIDE
    if (actor->query_prop(OBJ_I_INVIS))
    {
        send_debug_message("block", actor->query_real_name() + " "
            + "is invisible and cannot block.");
        actor->catch_tell("You find it difficult to block when you are "
            + "invisible.\n");
        return 0;
    }
    
    if (!targets || !sizeof(targets) || !stringp(targets[0]))
    {
        actor->catch_tell("Block which exit?\n");
        return 0;
    }
    
    exit = targets[0];
    room = MASTER_OB(environment(actor));
    if (exit == "stop")
    {
        if (query_block_room(actor) == room)
        {
            actor->catch_tell("You move away from the "
                + query_block_exit(actor) + " exit, no longer "
                + "focused on preventing others from leaving.\n");
            tell_room(environment(actor),
                QCTNAME(actor) + " moves away from the "
              + query_block_exit(actor) + " exit, no longer "
              + "focused on preventing others from leaving.\n",
              ({ actor }));
            actor->remove_blocker_shadow();
        }
        else
        {
            actor->catch_tell("You are not blocking any exits "
                + "in this room!\n");
        }
        return 0;
    }
    
    // Added April 2009
    // The ability used to be visual, meaning you couldn't block
    // or stop blocking when you couldn't see. However, one should be
    // able to stop blocking even when blind/cannot see. Set ability
    // to non-visual, and adding check here.
    if (!CAN_SEE_IN_ROOM(actor))
    {
        actor->catch_tell("You cannot see!\n");
        return 0;
    }
    
    object * others;
    others = FILTER_LIVING_OBJECTS(all_inventory(environment(actor)));
    others -= ({ actor });
    
    /*
    
    // Removed this check January 2008 because it allows someone to
    // check whether there are invisible people in the room.
    if (!sizeof(others))
    {
        actor->catch_tell("You don't see anyone here that you can try "
            + "to prevent from leaving.\n");
        return 0;
    }
    
    */
    
    if (query_block_exit(actor) == exit
        && query_block_room(actor) == room)
    {
        // We check to see if there's anyone new that we need to block.
        int bFoundBlockee = 0;
        foreach (object blockee : others)
        {
            if (!query_block_is_blocking(actor, blockee))
            {
                bFoundBlockee = 1;
                break;
            }
        }
        
        if (!bFoundBlockee)
        {                
            actor->catch_tell("You are already blocking that exit!\n");
            return 0;
        }
    }
 
    // Because of how block works, it's not possible to block exits
    // that can possibly move away. This would make it completely
    // unrealistic if the ship moves away and then someone breaks
    // through the block and is suddenly on the ship.
    if (exit == "board")
    {
        actor->catch_tell("You cannot block someone from boarding a "
            + "ship.\n");
        return 0;
    }
    
    if (exit == "disembark")
    {
        actor->catch_tell("You cannot block someone from leaving a "
            + "ship.\n");
        return 0;
    }
       
    return 1;
}

public void 
hook_special_complete()
{
}

/*
 * Function name: hook_changed_env
 * Description:   Return the string that will be printed to the player when
 *                he or she has moved rooms while preparing the ability.
 * Returns:       The message to print.
 */
public void
hook_changed_env()
{
    write("You realize that you cannot move and block at the same "
        + "time.\n");
}

public nomask int
query_ability_prep_time()
{
    /************************************************************************
     * By AoP decree, all preventative PvP abilities now have a 3 second 
     * prep time
     *
     * 2021-06-01: Carnak
     ************************************************************************
    
    object player;
    int skill, prep_time;
    
    player = this_player();
    if (!objectp(player))
    {
        return ::query_ability_prep_time();
    }
    
    skill = player->query_skill(SS_BLOCK);
    
    // We decide prep time by skill level
    prep_time = 3;
    
    switch (skill)
    {
    case 0..40:
        prep_time = 3;
        break;
    case 41..80:
        prep_time = 2;
        break;
    case 81..100:
    default:
        prep_time = 1;
        break;
    }
    send_debug_message("block", "Based on skill, prep time is now " + prep_time);
    return prep_time;
     
     ************************************************************************
     *                          End of AoP Decree!                          *
     ************************************************************************/
    return 3;
}

