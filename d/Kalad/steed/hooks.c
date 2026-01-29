/*
 * hooks.c
 *
 * This file contains all the various _hook_ functions calls
 * pertaining to the steeds code.
 */

/*
 * Function name: st_hook_fail_combat
 * Description:   Gives messages when we fail to mount with combat cond.
 * Arguments:     object: living tried to mount
 * Returns:       void
 */
public void
st_hook_fail_combat(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "Combat conditions prevent you from mounting " +
      "the " + this_object()->short_old() + ".\n");
}

/*
 * Function name: st_hook_check_combat
 * Description:   Does this steed support mounted combat?
 *                If not, is the living or the steed in combat?
 * Arguments:     object: Person trying to mount
 * Returns:       int:  1 - Mounting okay, 0 - Cannot mount.
 */
public int
st_hook_check_combat(object who)
{
    if (!who)
    {
	return 0;
    }

    if (this_object()->query_steed_allow_combat())
    {
	return 1;
    }

    if (this_object()->query_attack())
    {
	return 0;
    }

    if (who->query_attack())
    {
	return 0;
    }

    return 1;
}

/*
 * Function name: st_hook_fail_mount
 * Description:   Gives a failure message when you fail to mount.
 * Arguments:     object: living who failed
 * Returns:       void
 */
public void
st_hook_fail_mount(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You are not skilled enough to mount " +
      "the " + this_object()->short_old() + ".\n");
}

/*
 * Function name: st_hook_fail_dismount
 * Description:   Gives a message when you cannot dismount a steed.
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_fail_dismount(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You fail to dismount the " + 
      this_object()->short_old() + ".\n");
}

/*
 * Function name: st_hook_try_mount
 * Description:   Is the living skilled enough to mount the steed?
 * Arguments:     object: living trying to mount
 * Returns:       int: 1 - Can mount, 0 - Can't mount.
 */
public int
st_hook_try_mount(object who)
{
    if (!who)
    {
	return 0;
    }

    if (who->query_skill(this_object()->query_steed_skill()) < 20)
    {
	return 0;
    }

    return 1;
}

/*
 * Function name: st_hook_try_dismount
 * Description:   Is the living skilled enough to dismount the steed?
 * Arguments:     object: living trying to dismount
 * Returns:       int: 1 - Can dismount, 0 - Can't dismount.
 */
public int
st_hook_try_dismount(object who)
{
    /* Always succeed by default */
    return 1;
}

/*
 * Function name: st_hook_did_mount
 * Description:   Called to provide extra functionality after mounting.
 *                Also gives the success message.
 * Arguments:     object: living that mounted
 * Returns:       void
 */
public void
st_hook_did_mount(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You mount the " + this_object()->short_old() + ".\n");
    say( ({ who->query_Met_name() + " mounts the " +
	this_object()->short_old() + ".\n", capitalize(
	  who->query_nonmet_name()) + " mounts the " +
	this_object()->short_old() + ".\n", "Someone mounts the " +
	this_object()->short_old() + ".\n{" }) );
}

/*
 * Function name: st_hook_did_dismount
 * Description:   Called to provide extra functionality after dismounting.
 *                Also gives the success message.
 * Arguments:     object: living that dismounted
 * Returns:       void
 */
public void
st_hook_did_dismount(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You dismount the " + 
      this_object()->short_old() + ".\n");
    say( ({ who->query_Met_name() + " dismounts the " +
	this_object()->short_old() + ".\n", capitalize(
	  who->query_nonmet_name()) + " dismounts the " +
	this_object()->short_old() + ".\n", "Someone dismounts the " +
	this_object()->short_old() + ".\n{" }) );
}

/*
 * Function name: st_hook_not_driver
 * Description:   Message saying object isn't driving the horse.
 * Arguments:     object: the player trying to drive the steed
 * Returns:       void
 */
public varargs void
st_hook_not_driver(object who, string where = "there")
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You may not go " + where + " as you are not " +
      "driving the " + this_object()->short_old() + ".\n");
}

/*
 * Function name: st_hook_steed_tired
 * Description:   Give a message when the steed is too tired to move.
 * Arguments:     object: the living to give the message to
 *                string: (optional) direction to go.
 * Returns:       void
 */
public varargs void
st_hook_steed_tired(object who, string where = "there")
{
    if (!who)
    {
	return;
    }

    tell_object(who, "Your " + this_object()->short_old() + 
      " is too tired to go " +
      where + ".\n");
}

/*
 * Function name: st_hook_invalid_dest
 * Description:   Give a message saying the steed won't move someplace.
 * Arguments:     object: driver,
 *                string: where to.
 * Returns:       void
 */
public varargs void
st_hook_invalid_dest(object who, string where = "there")
{
    if (!who)
    {
	return;
    }

    tell_object(who, "Your " + this_object()->short_old() + 
      " refuses to go " +
      where + ".\n");
}

/*
 * Function name: st_hook_try_lead
 * Description:   Try to lead a steed
 * Arguments:     object: the living
 * Returns:       int:  0 - No, 1 - Yes
 */
public int
st_hook_try_lead(object who)
{
    /* Disabled by default */
    return 0;
}

/*
 * Function name: st_hook_fail_lead
 * Description:   Give a failure message since we cannot lead
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_fail_lead(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You are not allowed to lead the " +
      this_object()->short_old() + ".\n");
}

/*
 * Function name: st_hook_add_follow_fail
 * Description:   Give an error if the steed cannot follow
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_add_follow_fail(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "The " + this_object()->short_old() + 
      " is unable to follow, perhaps you have too many " +
      "following already?\n");
}

/*
 * Function name: st_hook_did_lead
 * Description:   Success message for being able to lead a steed
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_did_lead(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You start leading the " + 
      this_object()->short_old() + ".\n");
    say( ({ who->query_Met_name() + " starts leading the " +
	this_object()->short_old() + ".\n", capitalize(
	  who->query_nonmet_name()) + " starts leading the " +
	this_object()->short_old() + ".\n", "Someone starts leading " +
	"the " + this_object()->short_old() + ".\n{" }) );
}

/*
 * Function name: st_hook_try_unlead
 * Description:   Try to stop leading a steed
 * Arguments:     object: the living
 * Returns:       int:  1 - True, 0 - False
 */
public int
st_hook_try_unlead(object who)
{
    /* Always succeed by default */
    return 1;
}

/*
 * Function name: st_hook_fail_unlead
 * Description:   Give a message if can't leave steed behind
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_fail_unlead(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You are unable to leave the " +
      this_object()->short_old() + " behind.\n");
}

/*
 * Function name: st_hook_rem_follow_fail
 * Description:   Give messsage just in case we can't remove the steed
 *                as a follower.
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_rem_follow_fail(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "For some reason you may not leave the steed " +
      "behind, this may be due to a bug.\n");
}

/*
 * Function name: st_hook_did_unlead
 * Description:   Give a message when you stop leading a steed
 * Arguments:     object: the living
 * Returns:       void
 */
public void
st_hook_did_unlead(object who)
{
    if (!who)
    {
	return;
    }

    tell_object(who, "You stop leading the " + 
      this_object()->short_old() + ".\n");
    say( ({ who->query_Met_name() + " stops leading the " +
	this_object()->short_old() + ".\n", capitalize(
	  who->query_nonmet_name()) + " stops leading the " +
	this_object()->short_old() + ".\n", "Someone stops leading " +
	"the " + this_object()->short_old() + ".\n{" }) );
}

/*
 * Function name: st_hook_fail_move
 * Description:   Hook for when a steed fails steed_check_dest()
 * Returns:       void
 */
public void
st_hook_fail_move()     { return; }

/*
 * Function name: st_hook_steed_moved
 * Description:   Hook for when a steed has moved not by driver
 * Returns:       void
 */
public void
st_hook_steed_moved()   { return; }

/*
 * Function name: st_hook_try_attack_mount
 * Description  : Hook to see if you can attack steeds that
 *                we are currently riding.
 * Arguments    : object - the rider trying to attack
 * Returns      : int 1 - attack away, 0 - not allowed (default)
 */
public int
st_hook_try_attack_mount(object who)
{
    return 0;
}

/*
 * Function name: st_hook_fail_attack_mount
 * Description  : Print a message to the attacker on why we
 *                cannot attack mounted steeds.
 * Arguments    : object - the rider failing to attack.
 * Returns      : void
 */
public void
st_hook_fail_attack_mount(object who)
{
    if (!objectp(who))
    {
	return;
    }

    tell_object(who, "You cannot attack " + 
      this_object()->short_old() + " while you are riding it!\n");
}
