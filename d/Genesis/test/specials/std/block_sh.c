/*
 * /d/Genesis/specials/std/block_sh.c
 *
 * This is the blocking shadow. It is created whenever someone blocks
 * someone else from exiting the room. The shadow works by using
 * resolve_task to determine whether the person being blocked can
 * actually leave.
 *
 * Created by Novo, adapted to use resolve_task by Petros
 */

inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define TO            this_object()
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()
#define BLOCK_TASK_DIFFICULTY   780
#define BLOCK_LOG ("/d/Genesis/log/BLOCK_LOG")

#define SS_BLOCK 26
#define BLOCK_PROP  "_live_o_enemy_block"
#define BLOCK_PLAYER   0
#define BLOCK_ROOM     1
#define BLOCK_EXIT     2
#define BLOCK_STRENGTH 3

// Global Variables
static int Move_alarmid = 0;
static int Seconds_attempted = 0;
static string How = "";

// Prototypes
public int           escape_from_block();
public int           validate_blocker(object blocker);

private string
composite_living_vbfc(mixed players)
{
    string result;
    
    result = "";
    switch (sizeof(players))
    {
    case 0:
        break;
            
    case 1:
        result = QTNAME(players[0]);
        break;
    
    case 2:
        result = QTNAME(players[0]) + " and " + QTNAME(players[1]);
        break;
    
    default:       
        foreach (object player : players[..-2])
        {
            result += QTNAME(player) + ", ";
        }
        result += "and " + QTNAME(players[-1..][0]);
    }
    
    return result;
}

public void
remove_block_shadow()
{
    remove_shadow();
}


public int
has_block_shadow()
{
    return 1;
}

public int
is_blocking(object player)
{
    mixed block_properties;
    
    block_properties = player->query_prop(BLOCK_PROP);
    if (pointerp(block_properties)
        && block_properties[BLOCK_PLAYER] == shadow_who)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: query_blockers
 * Description  : Returns the array of objects that are blocking
 *                this person.
 * Arguments    : none
 * Returns      : array of objects blocking this person
 */
public mixed 
query_blockers()
{
    object * all_blockers, * all_living;
    
    all_living = FILTER_LIVING_OBJECTS(
                    all_inventory(environment(shadow_who)));
    all_blockers = filter(all_living, is_blocking);

    return all_blockers;
}

/*
 * Function name: query_blockers_for_exit
 * Description  : Returns the array of objects that are blocking
 *                this person at a particular exit
 * Arguments    : how - the exit to check blockers for
 * Returns      : array of objects blocking this person at that exit
 */
public mixed 
query_blockers_for_exit(string how)
{
    object * all_blockers, * blockers;
    mixed block_properties;
    string roomfile;
    
    all_blockers = query_blockers();
    blockers = ({ });
    foreach (object blocker : all_blockers)
    {
        roomfile = MASTER_OB(environment(shadow_who));        
        block_properties = blocker->query_prop(BLOCK_PROP);
        if (block_properties[BLOCK_EXIT] == how
            && block_properties[BLOCK_ROOM] == roomfile
            && validate_blocker(blocker))
        {
            blockers += ({ blocker });
        }
    }
    
    return blockers;
}

/*
 * Function name: validate_blocker
 * Description  : Validation function to check all the various
 *                conditions for the block.
 * Arguments    : blocker - the person to validate
 * Returns      : 0/1 - invalid/valid blocker
 */
public int 
validate_blocker(object blocker)
{
    if (!blocker || !objectp(blocker))
    {
        send_debug_message("block_sh", "Blocker is invalid object.");
        return 0;
    }           

    //Is the blocker trying to move?
    if (blocker->query_trying_to_move())
    {
        send_debug_message("block_sh", "Blocker is trying to move, thus "
                         + "cannot be blocking.");
        return 0;
    }

    //Can't be fighting somebody different and blocking 
    if (blocker->query_attack() != shadow_who 
        && shadow_who->query_attack() != blocker)
    {
        send_debug_message("block_sh", "Blocker not fighting blockee.");        
        return 0;
    }

/*
 
    Commented out per Gorboth's instructions.     
    //Is the blocker blinded?
    if (!CAN_SEE_IN_ROOM(blocker))
    {
        send_debug_message("block_sh", "Blocker can't see in room.");        
        return 0;
    }
        
    //Can the blocker sneak by?
    if (!shadow_who->check_seen(blocker))
    {
        send_debug_message("block_sh", "Blocker can't see blockee.");        
        return 0;
    }

*/

    return 1;
}

public void
print_attempt_move(object blockee, mixed blockers, mixed nonblockers,
                   string exit, string blockers_list)
{
    string blockee_msg, blocker_msg, watcher_msg, block_verb;
    int plural_blockers;
    
    plural_blockers = (sizeof(blockers) > 1);
    blockee_msg = "You try to leave using the " + How + " exit, but ";
    blocker_msg = QCTNAME(blockee) + " tries to leave using the " + How
                + " exit, but ";
    watcher_msg = blocker_msg;
    switch (random(5))
    {
    case 0:
        block_verb = plural_blockers ? "slow" : "slows";
        blockee_msg += blockers_list + " " + block_verb + " you down.\n";
        blocker_msg += "you slow " + blockee->query_objective() 
                     + " down.\n";
        watcher_msg += "is slowed down by " + blockers_list + ".\n";
        break;
    
    case 1:
        block_verb = plural_blockers ? "push" : "pushes";
        blockee_msg += blockers_list + " " + block_verb 
                     + " you backwards and you remain in the room.\n";
        blocker_msg += "you push " + blockee->query_objective() 
                     + " backwards and keep " + blockee->query_objective()
                     + " in the room.\n";
        watcher_msg += "is pushed backwards by " + blockers_list + " and "
                     + "remains in the room.\n";
        break;

    case 2:
        block_verb = plural_blockers ? "pull" : "pulls";    
        blockee_msg += blockers_list + " " + block_verb 
                     + " you back into the fray.\n";
        blocker_msg += "you pull " + blockee->query_objective() 
                     + " back into the fray.\n";
        watcher_msg += "is pulled back into the fray by " + blockers_list 
                     + ".\n";
        break;

    case 3:
        block_verb = plural_blockers ? "cause" : "causes";    
        blockee_msg += blockers_list + " " + block_verb 
                     + " you to stumble which prevents you from "
                     + "leaving the room.\n";
        blocker_msg += "you cause " + blockee->query_objective() 
                     + " to stumble preventing "
                     + blockee->query_objective() + " from leaving the "
                     + "room.\n";
        watcher_msg += "is caused to stumble by " + blockers_list 
                     + " preventing " + blockee->query_objective()
                     + " from leaving the room.\n";
        break;

    case 4:
        block_verb = plural_blockers ? "block" : "blocks";    
        blockee_msg += blockers_list + " " + block_verb 
                     + " the exit so completely that you are having "
                     + "trouble finding a way out.\n";
        blocker_msg += "you block " + blockee->query_objective() 
                     + " from leaving as best as you can.\n";
        watcher_msg += "cannot seem to find a way past " + blockers_list 
                     + ".\n";
        break;
    }
    
    blockee->catch_msg(blockee_msg);
    blockers->catch_msg(blocker_msg);
    nonblockers->catch_msg(watcher_msg);
}

/*
 * Function name: attempt_move
 * Description  : Attempts to move through the blockers. The function
 *                escape_from_block actually does the checking against
 *                every valid blocker.
 * Arguments    : same as move_living, except no how
 * Returns      : same as move_living
 */
public varargs int 
attempt_move(mixed to_dest, int dont_follow, int no_glance)
{
    object blocker;
    object * blockers, * nonblockers;
    string blockers_list, blockee_name;
    int result;

    blockers = query_blockers_for_exit(How);
    nonblockers = FILTER_LIVING_OBJECTS(
                    all_inventory(environment(shadow_who)));
    nonblockers -= blockers;
    nonblockers -= ({ shadow_who });
    blockers_list = composite_living_vbfc(blockers);
    
    if (sizeof(blockers) > 0
        && !escape_from_block())
    {
        ++Seconds_attempted;    
        // escape_from_block returns 0 if it fails. if it succeeded, 
        // it will return the blocker whom it escaped from
        if (strlen(blockers_list))
        {
            print_attempt_move(shadow_who, blockers, nonblockers,
                               How, blockers_list);
        }
        return 7;
    }
    
    if (strlen(blockers_list))
    {
        TO->catch_msg("You work your way past " + blockers_list
                    + " and leave using the " + How + " exit.\n");
        blockers->catch_msg(QCTNAME(TO) + " manages to leave "
                + "using the " + How + " exit.\n");
        nonblockers->catch_msg(QCTNAME(TO) + " works "
                + shadow_who->query_possessive() + " way past "
                + blockers_list + " and leaves using the " + How 
                + " exit.\n");
        
        if (interactive(shadow_who))
        {
            blockee_name = capitalize(shadow_who->query_real_name());
        }
        else
        {
            blockee_name = MASTER_OB(shadow_who);
        }        
        send_debug_message("block_sh", blockee_name + " took " 
                         + (Seconds_attempted + 1)
                         + " attempts to break through the block and "
                         + "move " + How + ".", 
                           BLOCK_LOG);
        // Remove me as the blockee from all my blockers for that exit
        foreach (object blocker : blockers)
        {
            blocker->remove_prop(BLOCK_PROP);
        }
        // If I've broken through the block, then I can remove
        // the shadow.
        set_alarm(0.1, 0.0, &remove_block_shadow());
        
    }

    remove_alarm(Move_alarmid);
    result = shadow_who->move_living(How, to_dest, 
                                     dont_follow, no_glance);    
    How = "";
    Seconds_attempted = 0;
    Move_alarmid = 0;
    
    return result;
}

/*
 * Function name: reduce_blocking_strength
 * Description  : After every attempt, the strength of the blocker
 *                decreases.
 * Arguments    : blocker - the person doing the blocking
 * Returns      : nothing
 */
public void
reduce_blocking_strength(object blocker)
{
    int strength, skill, rate;
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!pointerp(block_properties))
    {
        return;
    }

    strength = block_properties[BLOCK_STRENGTH];
    skill = blocker->query_skill(SS_BLOCK);
    if (skill == 0)
    {
        // Should never really happen, but just in case
        blocker->remove_prop(BLOCK_PROP);
        return;
    }
        
    rate = 10000 / skill;
    strength -= rate;
    if (strength > 0)
    {
        block_properties[BLOCK_STRENGTH] = strength;
        send_debug_message("block_sh", blocker->query_real_name()
                         + " reduces strength to " + strength);
        blocker->add_prop(BLOCK_PROP, block_properties);
    }
    else
    {
        blocker->remove_prop(BLOCK_PROP);
    }
}

/*
 * Function name: escape_from_block
 * Description  : Actually performs the checks against each valid
 *                blocker using resolve_task to see if they break
 *                through the block. The task difficulty for breaking
 *                the block is set in a define above.
 * Arguments    : none
 * Returns      : 0/1 - failure/success
 */
public int
escape_from_block()
{
    int friend_modifier, enemy_modifier;
    object * exit_blockers;
    mixed block_properties;
    
    // Friend Modifier is always 285
    friend_modifier = 285;
    enemy_modifier = 0;
    exit_blockers = query_blockers_for_exit(How);
    if (sizeof(exit_blockers) == 0)
    {
        // There are no valid blockers, so we should escape
        send_debug_message("block_sh", "No valid blockers, escaping.");
        return 1;
    }
    foreach (object blocker : exit_blockers)
    {
        block_properties = blocker->query_prop(BLOCK_PROP);
        if (!pointerp(block_properties))
        {
            // Should never happen.
            continue;
        }
        
        // The conditions are all good. We now add the enemy modifier.
        // Enemy modifiers range from 0-1500. At the end, we divide by 4.
        enemy_modifier += block_properties[BLOCK_STRENGTH];
        reduce_blocking_strength(blocker);
        if (enemy_modifier >= 1000)
        {
            break;
        }
    }    
    
    enemy_modifier = (enemy_modifier * 4) / 10;
    if (shadow_who->resolve_task(BLOCK_TASK_DIFFICULTY, 
                                 ({ SKILL_VALUE, friend_modifier }),
                                 exit_blockers[0],
                                 ({ SKILL_VALUE, enemy_modifier })) > 0)
    {
        // Successfully broke from the block
        send_debug_message("block_sh", shadow_who->query_real_name()
                         + " successfully breaks through block at "
                         + "friend: " + friend_modifier + " "
                         + "enemy: " + enemy_modifier);
        return 1;
    }
    
    send_debug_message("block_sh", shadow_who->query_real_name()
                     + " fails to break through block at "
                         + "friend: " + friend_modifier + " "
                         + "enemy: " + enemy_modifier);

    // Still being blocked
    return 0;
}

/*
 * Function name: move_living
 * Description  : Mask this function to block movement and trigger alarms
 *                if the person is blocked.
 * Arguments    : same as base move_living
 * Returns      : same as base move_living
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int result;
    object * blockers;
    mixed block_properties;
    
    if (get_alarm(Move_alarmid))
    {
        if (how == How)
        {
            // If we already have an alarm to attempt to leave, don't
            // do anything.
            send_debug_message("block_sh", shadow_who->query_real_name()
                             + " tries to move, but already has a "
                             + "movement alarm to break block.");
            shadow_who->catch_msg("You are already trying to break free "
                                + "towards the " + how + " exit.\n");     
            return 7;
        }
        else if (sizeof(query_blockers_for_exit(how)) != 0)        
        {
            blockers = query_blockers_for_exit(How);

            How = how;
            send_debug_message("block_sh", shadow_who->query_real_name()
                             + " tries move in a different direction.");
            shadow_who->catch_msg("You change your efforts and attempt to "
                                + "leave via the " + how + " exit.\n");

            // Trying a new direction forces a reset in the block in the
            // old direction.
            foreach (object blocker : blockers)
            {
                block_properties = blocker->query_prop(BLOCK_PROP);
                if (pointerp(block_properties))
                {
                    block_properties[BLOCK_STRENGTH] = 1500;
                    blocker->add_prop(BLOCK_PROP, block_properties);
                }
            }
            return 7;            
        }
        
        // If there are no blockers, we just allow the attempt_move to
        // proceed.
        send_debug_message("block_sh", shadow_who->query_real_name()
                         + " made " + (Seconds_attempted + 1)
                         + " attempts to break through the " + How
                         + " exit, but now moves unblocked through the "
                         + how + " exit.",
                           BLOCK_LOG);
        remove_alarm(Move_alarmid);
        Move_alarmid = 0;
    }

    blockers = query_blockers_for_exit(How);

    How = how; // store the how for checking on next move_living call.
    
    result = attempt_move(to_dest, dont_follow, no_glance);
    if (result != 0) // 0 is success
    {
        if (!get_alarm(Move_alarmid))
        {
            Move_alarmid = 
                set_alarm(1.0, 1.0, 
                          &attempt_move(to_dest, dont_follow, 
                                        no_glance));
        }
    }
    else
    {
        // If we moved out of the room, we want to reset the strengths
        // of all the blockers in case we move back in.
        foreach (object blocker : blockers)
        {
            block_properties = blocker->query_prop(BLOCK_PROP);
            if (pointerp(block_properties))
            {
                block_properties[BLOCK_STRENGTH] = 1500;
                blocker->add_prop(BLOCK_PROP, block_properties);
            }
        }
    }
    
    return result;    
}


/*
 * Function name: add_blocker
 * Description  : This method is used to add a new blocker to the
 *                shadow. Each blocker is inserted into Blockers
 *                mapping with the starting block strength
 * Arguments    : blocker - the player doing the blocking
 *                exit    - the exit that they're blocking
 * Returns      : nothing
 */
public void 
add_blocker(object blocker, string exit)
{
    mixed block_properties;
    string roomfile;
    
    if (!objectp(blocker))
    {
        // Can't add non-objects
        return;
    }
        
    if (blocker->query_skill(SS_BLOCK) == 0)
    {
        send_debug_message("block_sh", blocker->query_real_name() + " "
                         + "has no blocking skill, so cannot be added "
                         + "to the block list.");
        // The blocker has no skill, therefore no blocking allowed.
        return;
    }    
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    roomfile = MASTER_OB(environment(shadow_who));
    if (!pointerp(block_properties))
    {
        block_properties = ({ shadow_who, roomfile, exit, 1500 });
    }
    else if (block_properties[BLOCK_ROOM] != roomfile)
    {
        // No block properties set yet for this room. We will set the
        // block room and the strength.
        block_properties[BLOCK_ROOM] = roomfile;
        // Everybody starts out at 1500 for their resolve_task strength
        block_properties[BLOCK_STRENGTH] = 1500;
    }
    block_properties[BLOCK_PLAYER] = shadow_who;
    block_properties[BLOCK_EXIT] = exit;        
    blocker->add_prop(BLOCK_PROP, block_properties);            
}

/*
 * Function name: test_resolve_task
 * Description  : Test the result of the resolve_task over 1000 attempts.
 * Arguments    : player - player trying to break free
 *                friend_modifier - the factors in favor
 *                enemy_modifier - the factors against
 * Returns      : percentage of success
 */
public float
test_resolve_task(object player, int friend_modifier, int enemy_modifier)
{
    int counter;
    
    counter = 0;
    for (int i = 0; i < 1000; ++i)
    {
        if (player->resolve_task(BLOCK_TASK_DIFFICULTY, 
                                 ({ SKILL_VALUE, friend_modifier }),
                                 player,
                                 ({ SKILL_VALUE, enemy_modifier })) > 0)
        {
            ++counter;
        }
    }
    
    return itof(counter) / 10.0;
}

/*
 * Function name: print_resolve_task_test
 * Description  : Depending on the skill level given, it gives back the
 *                percentages per try to break free.
 * Arguments    : skill - skill from 0 to 100
 * Returns      : nothing
 */
public void
print_resolve_task_test(int skill)
{
    object player;
    int block_percentage, percentage, decrement, attempt;
    
    if (skill < 10)
    {
        write("Skill is too low to calculate.\n");
        return;
    }
    
    if (skill > 100)
    {
        write("Cannot block with greater than 100 skill.\n");
        return;
    }
    
    decrement = 4000 / skill;
      
    block_percentage = 100;
    player = this_player();
    attempt = 1;
    for (int i = 400; i >= 0; i -= decrement, ++attempt)
    {        
        percentage = ftoi(test_resolve_task(player, 285, i));
        block_percentage = (100 - percentage) * block_percentage / 100;
        write("Attempt: " + attempt + "\tEnemy: " + i + "\tEscape Percentage: " 
            + (100 - block_percentage) + "\n");
    }
}

/*
 * Function name: query_trying_to_move
 * Description  : If the blocker is blocked, and is trying to move, then
 *                they cannot be blocking. This checks to make sure that
 *                they don't do so.
 * Arguments    : none
 * Returns      : 0/1 - not trying to move/is trying to move
 */
public int
query_trying_to_move()
{
    if (get_alarm(Move_alarmid))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: notify_enemy_leaves
 * Description  : This routine is called when an enemy leaves the room, that
 *                is, when someone leaves us. It is not called when we walk
 *                away from someone who is subsequently hunting us.
 * Arguments    : object enemy - the enemy who left us.
 */
public void
notify_enemy_leaves(object enemy)
{
    enemy->remove_prop(BLOCK_PROP);
}
