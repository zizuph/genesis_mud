/*
 * Redefinable hooks for steeds.
 *
 * Lucius, Fysix, Sep 2002
 */

#include <macros.h>

/* Function name: mount_hook
 * Description:   Give a message when a living mounts the steed.
 *                Called by do_mount when not in silent mode.
 * Arguments:     object the livings who mounts
 */
public void
mount_hook(object o)
{
    o->catch_tell("You mount the " + this_object()->steed_short(o) + ".\n");
    tell_room(environment(this_object()), QCTNAME(o) + " mounts the " +
        this_object()->steed_short() + ".\n", o);
}

/* Function name: dismount_hook
 * Description:   Give a message when a living dismounts the steed.
 *                Called by sh_do_dismount when not in silent mode.
 * Arguments:     object the living who dismounts
 * Returns:       
 */
public void
dismount_hook(object o)
{
    o->catch_tell("You dismount the " + this_object()->steed_short(o) + ".\n");
    tell_room(environment(this_object()), QCTNAME(o) +
        " dismounts the " + this_object()->steed_short() + ".\n", o);
}

/* Function name: is_not_driver_hook
 * Description:   Give a message when one of the riders tries
 *                to move, but he is not the driver of this steed.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 */
public void
is_not_driver_hook(object o)
{
    o->catch_tell("You cannot go there since you " +
        "are not driving " + this_object()->query_the_name(o) + ".\n");
}

/* Function name: invalid_dest_hook
 * Description:   Give a message when the steed cannot go somewhere
 *                because check_destination indicated it.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 *                optional: string where_to, e.g. "board the ship",
 *                   "go north".
 */
public varargs void
invalid_dest_hook(object o, string where_to)
{
    o->catch_tell("Your " + this_object()->steed_short(o) +
        " refuses to " + (strlen(where_to) ? where_to : "go there") +
        ".\n");
}

/* Function name: steed_is_tired_hook
 * Description:   Give a message when the steed is too tired to move.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 */
public void
steed_is_tired_hook(object o)
{
    o->catch_tell("Your " + this_object()->steed_short(o) +
        " is too tired to go there.\n");
}

/* Function name: lead_hook
 * Description:   Give a message when a player starts leading this steed.
 * Arguments:     object living
 */
public void
lead_hook(object o)
{
    o->catch_tell("You start leading the " + this_object()->short() + ".\n");
    tell_room(environment(), QCTNAME(o) + " starts leading the " +
        this_object()->short() + ".\n", o);
}

/* Function name: unlead_hook
 * Description:   Give a message when a player stops leading this steed.
 * Arguments:     object living
 */
public void
unlead_hook(object o)
{
    o->catch_tell("You stop leading the " + this_object()->short() + ".\n");
    tell_room(environment(), QCTNAME(o) + " stops leading the " +
        this_object()->short() + ".\n", o);
}

/*
 * Function name: fail_mount_hook
 * Description:   Gives a failure message when you fail to mount.
 * Arguments:     object: living who failed
 * Returns:       void
 */
public void
fail_mount_hook(object who)
{
    if (!who)
    {
	    return;
    }

    tell_object(who, "You are not skilled enough to mount " +
      "the " + this_object()->steed_short() + ".\n");
}

/*
 * Function name: fail_mount_in_combat_hook
 * Description:   Gives messages when we fail to mount with combat cond.
 * Arguments:     object: living tried to mount
 * Returns:       void
 */
public void
fail_mount_in_combat_hook(object who)
{
    if (!who)
    {
	    return;
    }

    tell_object(who, "Combat conditions prevent you from mounting " +
      "the " + this_object()->steed_short() + ".\n");
}

