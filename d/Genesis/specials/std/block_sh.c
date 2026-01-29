/*
 * /d/Genesis/specials/std/block_sh.c
 *
 * This is the blocking shadow. It is created whenever someone blocks
 * someone else from exiting the room. The shadow works by using
 * resolve_task to determine whether the person being blocked can
 * actually leave.
 *
 * - Originally created by Novo, adapted to use resolve_task by Petros
 * - Rewritten to allow blocking by exit only and extend the duration
 *   in November 2008.
 * - Call set_this_player for logging to get correct logging of blockers
 *   (Petros, February 2009)
 * - Added logging for people who die while being blocked.
 *   (Petros, February 2009)
 * - Added fix for going to the correct room when changing directions
 *   (Petros, March 2010)
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include <composite.h>

inherit SHADOW_OBJECT;

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "block_defs.h"

// should not ever need to change this define
#define BLOCK_TASK_DIFFICULTY   780

// Global Variables
static int Move_alarmid = 0;
static int Seconds_attempted = 0;
static mixed * Move_arguments = ({ "", "", 0, 0 });
static string Move_command = ""; // not currently used

// Defines
#define         HOW_ARGUMENT            0
#define         DESTINATION_ARGUMENT    1
#define         DONT_FOLLOW_ARGUMENT    2
#define         NO_GLANCE_ARGUMENT      3

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

    // Is blocker invis? If so, invalid blocker
    if (blocker->query_prop(OBJ_I_INVIS))
    {
        send_debug_message("block_sh", "Blocker became invis, thus cannot "
            + "block successfully.");
        return 0;
    }
    
    if (blocker->query_ignore_block(shadow_who))
    {
        return 0;
    }
    
    if (IN_ARRAY(blocker, shadow_who->query_team()))
    {
        // If you're a leader, you shouldn't be blocked by your own
        // team.
        return 0;
    }
    
    return 1;
}


public int
is_valid_blocker(object blocker, string how, string room)
{
    mixed block_properties;
    
    if (blocker == shadow_who)
    {
        // It'd be pretty silly to block oneself
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    if (BLOCK_ABILITY->query_block_exit(blocker) != how
        || BLOCK_ABILITY->query_block_room(blocker) != room
        || !BLOCK_ABILITY->query_block_is_blocking(blocker, shadow_who))
    {
        return 0;
    }
    
    return validate_blocker(blocker);
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
    string room;
    
    room = MASTER_OB(environment(shadow_who));
    all_blockers = FILTER_LIVING_OBJECTS(all_inventory(environment(shadow_who)));
    return filter(all_blockers, &is_valid_blocker(, how, room));
}

public void
print_attempt_move(object blockee, mixed blockers, mixed nonblockers,
                   string exit, string blockers_list)
{
    string blockee_msg, blocker_msg, watcher_msg, block_verb;
    int plural_blockers;
    
    string How = Move_arguments[HOW_ARGUMENT];
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
        block_verb = plural_blockers ? "step" : "steps";    
        blockee_msg += blockers_list + " " + block_verb 
                     + " into your path preventing your exit.\n";
        blocker_msg += "you step into " + blockee->query_possessive() 
                     + " path and prevent " + blockee->query_objective()
                     + " from exiting.\n";
        watcher_msg += "is prevented from exiting by " + blockers_list 
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
attempt_move()
{
    string How = Move_arguments[HOW_ARGUMENT];
    mixed to_dest = Move_arguments[DESTINATION_ARGUMENT];
    int dont_follow = Move_arguments[DONT_FOLLOW_ARGUMENT];
    int no_glance = Move_arguments[NO_GLANCE_ARGUMENT];
    
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
    
    // stop the repeating alarm
    remove_alarm(Move_alarmid);
    Move_alarmid = 0;

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
        
        string * blockers_list = map(blockers, &->query_real_name());
        send_debug_message("block_sh", blockee_name + " took " 
                         + (Seconds_attempted + 1)
                         + " attempts to break through the block by "
                         + implode(blockers_list, " and ") + " and "
                         + "move " + How + " from "
                         + MASTER_OB(environment(shadow_who)) + ".", 
                           BLOCK_LOG);
        // If we moved out of the room, we want to reset the strengths
        // of all the blockers in case we move back in.
        foreach (object blocker : blockers)
        {
            BLOCK_ABILITY->notify_blockee_leaves_room(blocker, shadow_who);
        }        
    }

    result = shadow_who->move_living(How, to_dest, 
                                     dont_follow, no_glance);    
    Move_arguments = ({ "", "", 0, 0 }); // reset the move arguments
    Seconds_attempted = 0;
    
    return result;
}

public int
query_rate_by_skill(int skill)
{
    int rate;
    float factor;
    
    rate = 10000 / skill;
    factor = BLOCK_TIME_PER_10_SKILL / exp(1.0 - (itof(skill) / 100.0));
    rate = ftoi(itof(rate) / factor);
    
    return rate;    
}

/*
 * Function name: reduce_blocking_strength
 * Description  : After every attempt, the strength of the blocker
 *                decreases.
 * Arguments    : blocker - the person doing the blocking
 * Returns      : nothing
 */
public void
reduce_blocking_strength(object blocker, int number_of_blockers = 1)
{
    int strength, skill, rate;
    mixed block_properties;

    setuid();
    seteuid(getuid());
    strength = BLOCK_ABILITY->query_block_strength(blocker);
    skill = blocker->query_skill(SS_BLOCK);
    if (skill == 0)
    {
        // Should never happen, but just in case
        blocker->remove_prop(BLOCK_PROP);
        return;
    }
    /*
     * Changed in accordance to the new calculations, lowered the stacking effect
     * 2021-06-01 - Carnak
    int divisor = max(1, ftoi(log(itof(number_of_blockers) * 2.0) * 1.5));
    rate = query_rate_by_skill(skill) / divisor;
    */
    int divisor = max(1, ftoi(10.0 * (1.0 + (log(itof(number_of_blockers) * 2.0) * 0.3))));;
    rate = query_rate_by_skill(skill) * divisor / 10;
    strength -= rate;
    if (strength < 0)
    {
        strength = 0;
    }
    BLOCK_ABILITY->set_block_strength(blocker, strength);
    send_debug_message("block_sh", blocker->query_real_name()
                     + " reduces strength to " + strength);    
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
    
    string How = Move_arguments[HOW_ARGUMENT];
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

    setuid();
    seteuid(getuid());
    int number_of_blockers = sizeof(exit_blockers);
    foreach (object blocker : exit_blockers)
    {
        // The conditions are all good. We now add the enemy modifier.
        // Enemy modifiers range from 0-1500. At the end, we divide by 4.
        enemy_modifier += BLOCK_ABILITY->query_block_strength(blocker);
        reduce_blocking_strength(blocker, number_of_blockers);
        // Each blocker should be revealed
        blocker->reveal_me(1);
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

    setuid();
    seteuid(getuid());    
    // Get the stored "How" argument
    string How = Move_arguments[HOW_ARGUMENT];
    blockers = query_blockers_for_exit(How);
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

            // Since we changed directions, reset the move arguments
            Move_arguments[HOW_ARGUMENT] = how;
            Move_arguments[DESTINATION_ARGUMENT] = to_dest;
            Move_arguments[DONT_FOLLOW_ARGUMENT] = dont_follow;
            Move_arguments[NO_GLANCE_ARGUMENT] = no_glance;
            
            send_debug_message("block_sh", shadow_who->query_real_name()
                             + " tries move in a different direction.");
            shadow_who->catch_msg("You change your efforts and attempt to "
                                + "leave via the " + how + " exit.\n");

            // Trying a new direction forces a reset in the block in the
            // old direction.
            foreach (object blocker : blockers)
            {
                BLOCK_ABILITY->notify_blockee_change_direction(blocker, shadow_who);
            }
            return 7;            
        }
        
        // If there are no blockers, we just allow the attempt_move to
        // proceed.
        string * blockers_list = map(blockers, &->query_real_name());        
        send_debug_message("block_sh", shadow_who->query_real_name()
                         + " made " + (Seconds_attempted + 1)
                         + " attempts to break through the " + How
                         + " exit blocked by " + implode(blockers_list, " and ")
                         + " in room " + MASTER_OB(environment(shadow_who))
                         + ", but now moves unblocked through the "
                         + how + " exit.",
                           BLOCK_LOG);
        remove_alarm(Move_alarmid);
        Move_alarmid = 0;
    }

    // Store the move_living arguments for checking on the next move_living call
    Move_arguments[HOW_ARGUMENT] = how;
    Move_arguments[DESTINATION_ARGUMENT] = to_dest;
    Move_arguments[DONT_FOLLOW_ARGUMENT] = dont_follow;
    Move_arguments[NO_GLANCE_ARGUMENT] = no_glance;
    // Store the actual command that was given
    string vb = query_verb();
    if (!strlen(vb))
    {
        if (sizeof(explode(how, " ")) == 1)
        {
            Move_command = how;
        }
        else
        {
            Move_command = "";
        }
    }
    else if (Move_command = shadow_who->query_dircmd())
    {
        Move_command = vb + " " + Move_command;
    }
    else
    {
        Move_command = vb;
    }
    // Perform the actual attempt to move
    result = attempt_move();
    if (result != 0) // 0 is success
    {
        if (!get_alarm(Move_alarmid))
        {
            Move_alarmid = set_alarm(1.0, 1.0, &attempt_move());
        }
    }

    return result;    
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
    int decrement, attempt;
    float percentage, block_percentage;
    
    if (skill < 10)
    {
        write("Skill is too low to calculate.\n");
        return;
    }
    
    decrement = query_rate_by_skill(skill) * 4 / 10;
    
    block_percentage = 100.0;
    player = this_player();
    attempt = 1;
    for (int i = 400 - decrement; i >= 0; i -= decrement, ++attempt)
    {        
        percentage = test_resolve_task(player, 285, i);
        block_percentage = (100.0 - percentage) * block_percentage / 100.0;
        write("Attempt: " + attempt + "\tEnemy: " + i + "\tEscape Percentage: " 
            + ftoa(100.0 - block_percentage) + "\n");
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
 * Function name: query_trying_to_move_direction
 * Description  : This returns the last direction that the blockee
 *                tried to move. It's useful for determining whether
 *                there are any more blockees attempting to break
 *                through a particular exit or not.
 * Arguments    : none
 * Returns      : name of the exit
 */
public string
query_trying_to_move_direction()
{
    if (query_trying_to_move())
    {
        return Move_arguments[HOW_ARGUMENT];
    }
    
    return "";
}

/*
 * Function name:   adjust_combat_on_move
 * Description:     Function is called whenever move_living happens.
 *                  we shadow it here so we can track when the blockee
 *                  successfully leaves the room. That way, we can
 *                  go ahead and remove the shadow.
 * Arguments:       True if leaving else arriving
 */
public void
adjust_combat_on_move(int leave)
{
    if (leave)
    {
        set_alarm(0.0, 0.0, remove_block_shadow);
        send_debug_message("block_sh", "Moving out of room, removing "
            + "block shadow.");
    }
    shadow_who->adjust_combat_on_move(leave);
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void 
do_die(object killer)
{
    object * blockers;
    
    string How = Move_arguments[HOW_ARGUMENT];
    blockers = query_blockers_for_exit(How);
    if (sizeof(blockers))
    {        
        string * blockers_list = map(blockers, &->query_real_name());
        send_debug_message("block_sh", capitalize(shadow_who->query_name()) 
                         + " DIED while being blocked by "    
                         + implode(blockers_list, " and ") + ".\n", 
                           BLOCK_LOG);
    }
    
    shadow_who->do_die(killer);
}

