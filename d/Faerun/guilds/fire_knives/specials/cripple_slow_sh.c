/*
 * Standard Slow Shadow
 *
 * This is the slow shadow. When someone possesses the slow effect
 * it will limit their movement to once per second (or perhaps some
 * other interval). It is similar to a block, except that it does
 * not require an actual blocker. It is always in place.
 * 
 * Created by Petros, March 2010
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include <composite.h>

inherit SHADOW_OBJECT;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mixed *  Move_arguments = ({ "", "", 0, 0 });
public int      Move_alarmid = 0;
public object   Message_object = 0;
public float    Slow_interval = 2.0;

// Prototypes
public void     hook_slow_start_moving(object player, string direction);
public void     hook_slow_change_direction(object player, string direction);
public void     hook_slow_already_moving(object player, string direction);
public void     hook_slow_move_succeeded(object player, string direction);

// Defines
#define         HOW_ARGUMENT            0
#define         DESTINATION_ARGUMENT    1
#define         DONT_FOLLOW_ARGUMENT    2
#define         NO_GLANCE_ARGUMENT      3

/*
 * Function:    remove_slow_shadow
 * Description: Defined function to remove the shadow directly.
 *              Necessary since remove_shadow cannot be called
 *              safely when there are multiple shadows.
 */
public void
remove_slow_shadow()
{
    remove_shadow();
}

/*
 * Function:    has_slow_shadow
 * Description: Simply checks to see if the person has this
 *              shadow.
 */
public int
has_slow_shadow()
{
    return 1;
}

/*
 * Function:    set_message_object
 * Description: By default, messages for the slow are defined in the shadow.
 *              However, one has the option of specifying an outside object
 *              that will handle the messages. This similar to the armour
 *              and weapon overrides like set_wf.
 *              NOTE: If you use this, you *must* define all the hook
 *              functions, otherwise things will not display properly.
 */
public void
set_message_object(object obj)
{
    Message_object = obj;
}

/*
 * Function:    set_slow_interval
 * Description: Sets how long it takes between slow movements.
 */
public void
set_slow_interval(float interval)
{
    Slow_interval = interval;
}

/*
 * Function:    query_slow_interval
 * Description: Returns how long it takes between slow movements.
 */
public float
query_slow_interval()
{
    return Slow_interval;
}

/*
 * Function name: slow_move
 * Description  : Performs the slow movement. Called from alarm created
 *                in move_living.
 */
public varargs int 
slow_move()
{
    int result;
    
    hook_slow_move_succeeded(shadow_who, Move_arguments[HOW_ARGUMENT]);
    result = shadow_who->move_living(Move_arguments[HOW_ARGUMENT], 
                                     Move_arguments[DESTINATION_ARGUMENT],
                                     Move_arguments[DONT_FOLLOW_ARGUMENT],
                                     Move_arguments[NO_GLANCE_ARGUMENT]);
    Move_arguments = ({ "", "", 0, 0 });
    Move_alarmid = 0;
    
    return result;
}

/*
 * Function name: move_living
 * Description  : Mask this function to slow a person's movement and 
 *                only allow movement via the alarmed functions.
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    setuid();
    seteuid(getuid());    
    if (get_alarm(Move_alarmid))
    {
        if (how == Move_arguments[HOW_ARGUMENT])
        {            
            // Person is trying to move in the same direction that they are
            // already moving.
            hook_slow_already_moving(shadow_who, how);            
            return 7;
        }
        else
        {
            // Person is changing directions
            Move_arguments[HOW_ARGUMENT] = how;
            Move_arguments[DESTINATION_ARGUMENT] = to_dest;
            Move_arguments[DONT_FOLLOW_ARGUMENT] = dont_follow;
            Move_arguments[NO_GLANCE_ARGUMENT] = no_glance;
            hook_slow_change_direction(shadow_who, how);
            return 7; 
        }        
    }
        
    // Person is starting to move in a certain direction
    Move_arguments[HOW_ARGUMENT] = how;
    Move_arguments[DESTINATION_ARGUMENT] = to_dest;
    Move_arguments[DONT_FOLLOW_ARGUMENT] = dont_follow;
    Move_arguments[NO_GLANCE_ARGUMENT] = no_glance;
    Move_alarmid = set_alarm(query_slow_interval(), 0.0, &slow_move());
    hook_slow_start_moving(shadow_who, how);
    return 7;
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

// HOOKS
/*
 * Function:    hook_slow_start_moving
 * Description: Hook that gets called when the person starts to move with
 *              the slow effect.
 */
public void
hook_slow_start_moving(object player, string direction)
{
    if (objectp(Message_object))
    {
        Message_object->hook_slow_start_moving(player, direction);
        return;
    }
    player->catch_tell("You start to move towards the " + direction
        + " exit, but are slowed by weakness and disorientation.\n");
    tell_room(environment(player), QCTNAME(player) + " starts to move "
        + "towards the " + direction + " exit, but is slowed by "
        + "weakness and disorientation.\n", ({ player }) );
}

/*
 * Function:    hook_slow_change_direction
 * Description: Hook that gets called when the person changes direction while
 *              already trying to move.
 */
public void
hook_slow_change_direction(object player, string direction)
{
    if (objectp(Message_object))
    {
        Message_object->hook_slow_change_direction(player, direction);
        return;
    }
    player->catch_tell("You change your mind and start to move towards the " 
        + direction + " exit, but are still slowed by weakness and disorientation.\n");
    tell_room(environment(player), QCTNAME(player) + " changes direction "
        + "and begins to move towards the " + direction + " exit, but "
        + "contisues to be slowed by "
        + "weakness and disorientation.\n", ({ player }) );
}

/*
 * Function:    hook_slow_already_moving
 * Description: Hook that gets called when the person continues to try to break 
 *              free in the same direction that they already were trying.
 */
public void
hook_slow_already_moving(object player, string direction)
{
    if (objectp(Message_object))
    {
        Message_object->hook_slow_already_moving(player, direction);
        return;
    }
    player->catch_tell("You are already moving towards the " + direction
        + " exit, but are still slowed by weakness and disorientation.\n");
}

/*
 * Function:    hook_slow_move_succeeded
 * Description: Hook that gets called when the person completes the move
 *              that they wanted to and are allowed to move to the next
 *              room.
 */
public void
hook_slow_move_succeeded(object player, string direction)
{
    if (objectp(Message_object))
    {
        Message_object->hook_slow_move_succeeded(player, direction);
        return;
    }
    player->catch_tell("You successfully make your way to the " + direction
        + " exit.\n");
    tell_room(environment(player), QCTNAME(player) + " successfully makes "
        + player->query_possessive() + " way to the " + direction
        + " exit.\n", ({ player }) );
}
