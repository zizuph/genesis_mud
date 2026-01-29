/*
 * - seat_shadow.c
 *
 * This shadow gets added to seated players to track if they leave
 * the room without standing first.  Does a callback to their chair
 */
#pragma strict_types

inherit "/std/shadow";

private static object seating = 0;

/*
 * Function name: query_seating_shadow
 * Description	: Returns an object pointer to this shadow.
 * Returns	: object - This shadow object.
 */
public nomask object
query_seating_shadow(void)	{ return this_object(); }

/*
 * Function name: remove_seating_shadow
 * Description	: Removes this seating shadow from a person.
 * Returns	: Void
 */
public nomask void
remove_seating_shadow(void)	{ remove_shadow(); }

/*
 * Function name: set_seating_ob
 * Description	: Sets the object this person is seated upon.
 * Arguments	: object ob - The seating arrangement managing us.
 * Returns	: Void
 */
public nomask void
set_seating_ob(object ob)	{ seating = ob; }

/*
 * Function name: query_seating_ob
 * Description	: Returns the object this person is seated upon.
 * Returns	: object - A pointer to the seating arrangement managing us.
 */
public nomask object
query_seating_ob(void)		{ return seating; }

/*
 * Masked function to capture us moving without first standing up.
 * See: sman /std/living move_living
 */
public varargs int
move_living(string how, mixed dest, int follow, int glance)
{
    int res = seating->do_stand("up");

    if (res == 2)
    {
	/* We were blocked by deny_stand() in the seating object. */
	return 7;
    }

    set_alarm(0.0, 0.0, &remove_seating_shadow());
    return shadow_who->move_living(how, dest, follow, glance);
}

/*
 * Masked function to capture quit / destruct events.
 * See: sman /std/living remove_object
 */
public int
remove_object(void)
{
    seating->do_not_deny();
    seating->do_stand("up");
    set_alarm(0.0, 0.0, &remove_seating_shadow());
    return shadow_who->remove_object();
}

/*
 * Masked function to capture linkdeath events.
 * See: sman /std/player_sec linkdeath_hook
 */
public void
linkdeath_hook(int link)
{
    if (!link)
	return shadow_who->linkdeath_hook(link);

    seating->do_not_deny();
    seating->do_stand("up");
    set_alarm(0.0, 0.0, &remove_seating_shadow());
    shadow_who->linkdeath_hook(link);
}
