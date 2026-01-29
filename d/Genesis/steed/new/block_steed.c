/*
    /d/Genesis/steed/block_steed.c
    
    Module to be inherited by rooms to block steeds.
    This is especially useful to block "up" and "down" exits
    for steeds. Also steeds carrying more than one rider
    might not be welcome in some guilds or quest related places.

    Notes:
    For not allowing steeds to enter an entire room, use the
    property ROOM_I_NO_ALLOW_STEED.
    To discern between different types of steeds (like wolves and
    horses) you will have to create your own blocking functions.

    Examples of exits which block steeds:

        // This will block all steeds from going east
        add_exit("/d/Kalad/some_room", "east", block_steed);
        
        // This will block steeds carrying more than 1 rider
        add_exit("/d/Kalad/some_room", "north", &block_steed(1));
    
        // This will block all steeds from going up the stairs
        add_exit("/d/Kalad/some_room", "up",
            &block_steed(-1, hook_steed_blocked_by_stair);

        // This does the same
        add_exit("/d/Kalad/some_room", "up", stair_block_steed);

    Fysix@Genesis, Feb 1998
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <stdproperties.h>

/* Function name: hook_steed_blocked
 * Description:   Give some message when the steed is blocked
 *                Mask this function if you want to have your own messages.
 * Arguments:     object steed,
 *                object tp, the one who gave the command
 *                string direction
 */
public void
hook_steed_blocked(object steed, object tp, string direction)
{
    steed->query_riders()->catch_tell("Your " + steed->steed_short() +
        " is stopped as " + steed->query_pronoun() +
        " tries to " + direction + ".\n");
    tell_room(this_object(),
        QCTNAME(steed) + " is stopped as " +
        steed->query_pronoun() + " tries to go " + direction + ".\n",
        steed->query_riders());
}

/* Function name: hook_steed_blocked_by_stair
 * Description:   Give message the steed can't go up or down the stairs
 *                You can use this message function in stead of the
 *                default hook_steed_blocked message.
 * Arguments:     object steed,
 *                object tp, the one who gave the command
 *                string direction
 */
public void
hook_steed_blocked_by_stair(object steed, object tp, string direction)
{
    steed->query_riders()->catch_tell("Your " + steed->steed_short() +
        " is stopped as " + steed->query_pronoun() +
        " tries to go " + direction + " the stairs.\n");
    tell_room(this_object(),
        QCTNAME(steed) + " is stopped as " +
        steed->query_pronoun() + " tries to go " + direction +
        " the stairs.\n",
        steed->query_riders());
}

/* Function name: find_steed
 * Description:   See if the living is a steed or is riding on one.
 * Arguments:     object living
 * Returns:       the found steed object, 0 otherwise
 */
public object
find_steed(object living)
{
    object steed;
    
    if (living->is_steed())
        return living;
    
    if (steed = living->query_prop(LIVE_O_STEED))
        return steed;
    
    return 0;
}

/* Function name: block_steed
 * Description:   Blocks steeds when they have too many riders.
 * Arguments:     int: number of riders that are allowed on the steed,
 *                     is -1 by default.
 *                function: message function that should give the
 *                     fail message.
 *                     Is hook_steed_blocked by default.
 * Returns:       int 1: block
 *                    0: let steed pass
 */
public varargs int
block_steed(int allowed_no_of_riders = -1,
    function message_fun = hook_steed_blocked)
{
    object steed = find_steed(this_player());

    if (steed)
    {
        // Check number of riders the steed has
        if (steed->query_has_riders() > allowed_no_of_riders)
        {
            message_fun(steed, this_player(), query_verb());
            return 1;
        }
    }
    
    return 0;
}

// Steed will be blocked by stairs
public varargs int
stair_block_steed(int allowed_no_of_riders = -1,
    function message_fun = hook_steed_blocked_by_stair)
{
    return block_steed(allowed_no_of_riders, message_fun);
}
