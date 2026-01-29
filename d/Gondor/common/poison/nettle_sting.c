/*
 * This file is:
 * /d/Gondor/common/poison/nettle_sting.c
 *
 * Modified to be nettle poison from the file:
 * /d/Gondor/common/poison/mosquito_sting.c
 *
 * Copyright (C) Stas van der Schaaf - May 16 1994
 *               Mercade @ Genesis
 *
 * This is the poison that enters your body after a mosquito stings you.
 *
 * Revision history:
 * Added argument to ITCH_FEELING for use in tell_damage_player.
 *       Olorin, 28-oct-1995
 * Changed mosquito-specific msg, since mosquito.c is inherited by
 *	other insects.  Gnadnar, 13-jan-99
 * Changed damage to be modest. One should not die of a mosquito bite.
 *	Gnadnar, Gorboth, 19-Feb-99
 * Modified to nettle, Serif, July 18, 2001.
 */

inherit "/std/poison_effect";

#include <wa_types.h>
#include <poison_types.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define STING_FEELING(x) ({ \
    "Intense stinging sensations spread all over your "+x+".",            \
    "The sting of the welts is almost unbearable.",                          \
    "The stinging feeling grows worse.",                                     \
    "The raised red welts on your "+x+" drive you crazy.",                   \
    "Ouch! The red welts continue to sting!",                                \
    "Scratching only seems to spread the welts on your "+x+".",              \
    "Scratching your "+x+" only makes the red welts worse!",                 \
    "The stinging sensation seems to be spreading!" })

#define	PNAME		"_gondor_herb_nettle_poison"
#define	PTIME		 621	/* how long it lasts               */
#define	PINTERVAL	  27	/* interval between damage         */
#define	PSTRENGTH	  15	/* how strong the poison           */
#define	MAX_PTIME	3600	/* max duration of rash, no matter */
				/* how many nettles they pick       */

/* Global variables */
private static string	body_part;
private static int	first_time = 1;

/* Protoypes */
public void	create_poison_effect();
public void	set_body_part(string part);
public string	query_body_part();
public void	start_poison(object poisoner);
public void	first_msg();
public void	add_poison();
public void	tell_damage_player(int phit, string feeling);
public void	special_damage(int damage);
public void	timeout();
public string	query_poison_recover();
public void	init_poison_recover(string arg);
public string	stat_object();


/*
 * Function name:	create_poison_effect
 * Description	:	set up the poison
 */
public void
create_poison_effect()
{
    set_time(PTIME);
    set_interval(PINTERVAL);
    set_damage( ({
        POISON_HP, 1,
	POISON_USER_DEF, 5 }) );
    set_strength(PSTRENGTH);
    set_silent(2);
    set_poison_type("nettle");
    set_name(PNAME);
} /* create_poison_effect */


public void	set_body_part(string part)	{ body_part = part; }
public string	query_body_part()		{ return body_part; }
public string	query_poison_recover()		{ return body_part; }
public void	init_poison_recover(string arg)	{ body_part = arg; }


/*
 * Function name:	start_poison
 * Description	:	mask parent to start poison only if there is not
 *                	already a poison for our body_part.  if there's
 *			already a poison for body_part, then just call
 *			its add_poison().
 * Arguments    :	object poisoner - the living responsible for it.
 */
public void
start_poison(object poisoner)
{
    object	*others,
		env = ENV();
    int		s;

    if (!living(env))
    {
	remove_object();
	return;
    }

    others = filter(all_inventory(env), &->id(PNAME)) - ({ TO });
    s = sizeof(others);
    while (s-- > 0)
    {
	if (others[s]->query_body_part() == body_part)
	{
	    others[s]->add_poison();
	    remove_object();
	    return;
	}
    }
    ::start_poison(poisoner);
    if (first_time)
    {
	set_alarm(2.0, 0.0, first_msg);
	first_time = 0;
    }
    return;
} /* start_poison */


/* 
 * Function name:	first_msg
 * Description	:	give player an initial itch msg
 */
public void
first_msg()
{
    object	env = ENV();
    if (living(env))
    {
	tell_object(env, "Your "+body_part+" begins to sting intensely.\n");
    }
} /* first_msg */


/*
 * Function name:	add_poison
 * Description	:	extend rash and increase strength
 *			when another nettle afflicts the same
 *			body part. called from start_poison().
 */
public void
add_poison()
{
    mixed	*arr;
    float	time_left = 0.0;
    int		oldtime = query_time(),
		bumptime = (PTIME / 3);

    if (oldtime >= MAX_PTIME)
    {
	/* already at max duration */
	return;
    }

    /* extend the total time by a third, and change the
     * timeout alarm
     */
    set_time(oldtime + bumptime);
    if (a_time &&
	sizeof(arr = get_alarm(a_time)))
    {
        time_left = arr[2];
	remove_alarm(a_time);
    }
    time_left += itof(bumptime);
    a_time = set_alarm(time_left, 0.0, timeout);

    /* bump the strength by a third */
    set_strength(query_strength() + (PSTRENGTH / 3));
} /* add_poison */


/*
 * Function name:	tell_damage_player
 * Description	:	Mask the parent so that we never do msgs here.
 *                	All the itching msgs are written in special_damage().
 * Arguments	:	phit - the damage level
 *                	str  - the string to tell the player.
 */
public void
tell_damage_player(int phit, string feeling)
{
}


/*
 * Function name:	special_damage
 * Description	:	give the player an itching message each interval
 * Arguments	:	damage - the damage value.
 *
 * Since the rash is so weak, the probability of normal damage is fairly low,
 * so relying on tell_damage_player() for itching msgs is no good.
 * However, special_damage() will be called each interval, so do msgs here.
 */
public void
special_damage(int damage)
{
    tell_object(poisonee, ONE_OF_LIST(STING_FEELING(body_part)) + "\n");
} /* special_damage */


/*
 * Function name:	timeout
 * Description	:	mask parent so only remove self if there is
 *			no nettle in contact with player's skin.
 *
 * if player obstinately continues to hold nettle vines in bare hands,
 * or to wear wreaths on bare skin, obstinately continue poison.
 */
public void
timeout()
{
    object	pl = ENV(TO),
		armour, 
		*arr;
    int		loc,
		rhand_clad,
		lhand_clad,
		s;

    if (!living(pl))
    {
	::timeout();
	return;
    }

    switch (body_part)
    {
    case "scalp":	loc = A_HEAD; break;
    case "neck":	loc = A_NECK; break;
    case "left hand":	loc = A_L_HAND; break;
    case "right hand":	loc = A_R_HAND; break;
    default:		
	tell_object(pl, "You don't notice that stinging sensation on your " +
			body_part + " any longer.\n");
	::timeout();
	return;
    }

    if (objectp(armour = pl->query_armour(loc)) &&
	armour->id("herbcord") &&
	armour->query_itches())
    {
	/* wearing an itchy wreath on body_part -- keep rash going */
	remove_alarm(a_dam);
	start_poison(pl);
	return;
    }

    /* not wearing an itchy wreath on our body_part. are they
     * carrying any nettle?
     */
    arr = all_inventory(pl);
    if (!sizeof(filter(arr,
		       &operator(==)("nettle") @ &->query_herb_name())) &&
        !sizeof(filter(filter(filter(arr,
				     &->id("herbcord")),
			      &->query_itches()),
			not @ &->query_worn())))
    {
	/* no nettle in hands */
	tell_object(pl, "You don't notice that stinging sensation on your " +
			body_part + " any longer.\n");
	::timeout();
	return;
    }

    /* carrying nettle -- are hands protected? */
    rhand_clad = (objectp(armour = pl->query_armour(A_R_HAND)) &&
		       !armour->id("herbcord")); 
    lhand_clad = (objectp(armour = pl->query_armour(A_L_HAND)) &&
		       !armour->id("herbcord")); 
    if (rhand_clad && lhand_clad)
    {
	/* yep, all covered */
	tell_object(pl, "You don't notice that stinging sensation on your " +
			 body_part + " any longer.\n");
	::timeout();
	return;
    }

    /* carrying nettle and hands are not protected.
     * if we are a hands rash, continue itching them 
     */
    if (loc == A_L_HAND || loc == A_R_HAND)
    {
	remove_alarm(a_dam);
	start_poison(pl);
	return;
    }

    /* we are not a hands rash -- is there a hands rash already
     * in place?
     */
    arr = filter(all_inventory(pl), &->id(PNAME)) - ({ TO });
    while (s-- > 0)
    {
	if (arr[s]->query_body_part() == "left hand" ||
	    arr[s]->query_body_part() == "right hand")
	{
	    /* already have a hand rash -- nothing for us to do */
	    tell_object(pl, "You don't notice that stinging sensation on your " +
			     body_part + " any longer.\n");
	    ::timeout();
	    return;
	}
    }

    /* carrying nettle, hands not protected, no hands rash.
     * convert ourselves to hands and continue.
     */
    if (!rhand_clad)
    {
	body_part = "right hand";
    }
    else
    {
	body_part = "left hand";
    }
    remove_alarm(a_dam);
    start_poison(pl);
    set_alarm(2.0, 0.0, first_msg);
    return;
} /* timeout */


/*
 * Function name:	stat_object
 * Description	:	mask parent to add body_part
 * Returns	:	A string describing the object.
 */
public string
stat_object()
{
    return ::stat_object() +
           "Body_part : " + body_part + "\n";
} /* stat_object */
