/*
 * - beauty_salve.c
 * - beauty_shadow.c
 *
 * This item is a beauty salve for players to apply unto their skin
 * to heal in an attempt to make themselves more appealing to the eye.
 *
 * Repeated applications will improve your looks, however, applying
 * too much will destroy your looks.
 *
 * The shadow will decay over time and remove the bonus to a player's
 * beauty and will eventually fade away completely, leaving them as they were.
 *
 * Coded by Lucius@Genesis.
 */
#pragma no_inherit
#pragma strict_types

inherit "/std/shadow";

/* How often do we check decay? */
#define DECAY	3600.0
/* How many decay checks to do before removal. */
#define COUNT	3
/* How much is our beauty boosted? */
#define BOOST	-(10 + random(10))
/* How many applications before our looks are destroyed. */
#define APPLY	(2 + random(3))


private int alarm, apply, beauty, count, ugly;


/* Masked to halt any running alarms. */
public void
remove_shadow()
{
    if (alarm)
	remove_alarm(alarm);
    ::remove_shadow();
}

/* Return a pointer to this shadow. */
public object
beauty_salve_shadow()	{ return this_object(); }

/* Allows us to remove this specific shadow externally. */
public void
remove_beauty_salve()	{ remove_shadow(); }

/* This handles decay of our looks. */
private void
decay_beauty()
{
    int diff;

    /* Have we finished decaying yet? */
    if (++count > COUNT)
    {
	if (ugly)
	{
	    tell_object(shadow_who, "You sense that your destroyed looks "+
		"have returned to normal.\n");
	}
	else
	{
	    tell_object(shadow_who, "The beauty salve wears off completely "+
		"and your looks return to normal.\n");
	}

	remove_shadow();
	return;
    }

    /*
     * Adjust the beauty offest.
     * This formula means it wears off faster further into decay.
     */
    diff  = beauty / COUNT;
    diff *= count;
    beauty -= diff;

    if (ugly)
    {
	tell_object(shadow_who, "Your destroyed looks are slowly returning "+
	    "to something more normal.\n");
    }
    else
    {
	tell_object(shadow_who, "You sense the beauty salve beginning to "+
	    "wear off and lose some of its effect.\n");
    }
}

/*
 * Applies the beauty salve to us.
 * If test > 0, then it means another application has been added.
 */
public void
apply_salve(int test)
{
    /* Is this a re-application? */
    if (test)
    {
	/* Did they apply too much salve? */
	if (++apply > APPLY)
	{
	    ugly   = 1;
	    beauty = -BOOST;

	    tell_object(shadow_who, "You have applied too much "+
		"beauty salve and it has destroyed your looks!\n");
	}
	else
	{
	    beauty += BOOST;
	}
    }
    else
    {
	/* Boost and start decay. */
	apply  = 1;
	beauty = BOOST;
	alarm  = set_alarm(DECAY, DECAY, decay_beauty);
    }

    count = 0;
}

/* This is the actual (modified) appearance. */
public int
query_appearance_offset()	{ return beauty; }

