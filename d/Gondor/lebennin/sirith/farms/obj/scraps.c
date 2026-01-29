/*
 * /d/Gondor/lebennin/sirith/farms/obj/scraps.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * special handling of desc so players always see "some" scraps,
 * and cannot count them, swiped from /d/Gondor/mordor/obj/flour.c
 * (thanks, mercade!!)
 *
 */

#pragma strict_types

inherit "/std/heap" heap_file;

#include <stdproperties.h>	/* for HEAP_I_*, etc	*/
#include <macros.h>		/* for CAN_SEE_IN_ROOM	*/
#include <cmdparse.h>		/* for NORMAL_ACCESS	*/
#include <poison_types.h>	/* for POISON_HP	 */
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define SCRAPS_UNIQUE_ID   ("_unique"+SIRITH_SCRAPS)

public void	create_heap();
public varargs	string short();
public void	init();
// public void	appraise_object(int num);
public int	smell_eat_scraps(string arg);
public int	feed_scraps(string arg);
public void	add_alcohol(int soft_amt, int alco_amt);
public void	add_poison(object herb, int str);
public int	crumble_scraps(string arg);


static string	My_short;	/* changes once player adds liquid */
static int	Soft_amt,	/* liquid added			   */
		Alcohol_per,	/* % alcohol			   */
		Poison_str,	/* strength of poison added	   */
		Poison_dam;	/* hp damage done by poison	   */


/*
 * Function name:	create_heap
 * Description	:	set up the scraps
 */
public void
create_heap()
{
    set_name("scraps");
    add_name(SIRITH_SCRAPS);
    set_pname("scraps");
    My_short = "some kitchen scraps";
    set_adj("some");
    add_adj("kitchen");
    set_long(BSN("The scraps include apple cores, potato parings, "+
	"onion skins and other vegetable matter that you cannot "+
	"quite identify. They have begun to decay, and smell nasty."));

    set_heap_size(1);

    /* oh, say a 1-lb lump of scrap, about 5 x 5 x 3 inches */
    add_prop(HEAP_S_UNIQUE_ID,   SCRAPS_UNIQUE_ID);
    add_prop(OBJ_I_WEIGHT, 454);
    add_prop(OBJ_I_VOLUME, 1229);
    add_prop(HEAP_I_UNIT_VALUE,  0);
} /* create_heap */


/*
 * Function name:	short
 * Description	:	mask parent so they always see "some scraps"
 *
 * if use set_short(), "inventory" shows:
 *	You are carrying a some kitchen scraps.
 * and:
 *	You are carrying five some kitchen scrapses.
 * yeuch.
 */
public varargs string
short()
{
    return My_short;
} /* short */


/*
 * Function name:	init
 * Description	:	add player verbs
 *
 * In this function init() the call to ::init() is deliberately omitted for I
 * do not want the "count" command that is defined in /std/heap to be added
 * to the player. Furthermore, there are no important calls in ::init() at all.
 */
public void
init()
{
    add_action(smell_eat_scraps, "smell");
    add_action(smell_eat_scraps, "sniff");
    add_action(smell_eat_scraps, "eat");
    add_action(feed_scraps, "give");
    add_action(feed_scraps, "feed");
    add_action(feed_scraps, "lure");
    add_action(feed_scraps, "show");

    /* bowl breaks if dropped */
    add_action(crumble_scraps, "drop");
    add_action(crumble_scraps, "put");
} /* init */


/*
 * Function name:	appraise_object
 * Description	:	call /std/object's appraise_object()
 * Arguments	:	int num - use this number instead of skill if given.
 */

/*
public void
appraise_object(int num)
{
    ::::appraise_object(num);
}
*/

/*
 * Function name:	smell_eat_scraps
 * Description	:	handle attempts to smell/sniff/eat scraps
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 otherwise
 */
public int
smell_eat_scraps(string arg)
{
    object  what;

    if (strlen(arg) &&
	parse_command(LOW(arg), ENV(TP), "%o", what) &&
        (TO == what))
    {
	if (QVB == "eat")
	{
	    write(BSN("The scraps smell too nasty to put in your mouth."));
	}
	else	/* smell/sniff */
	{
	    write(BSN("You sniff the kitchen scraps. They reek "+
		"of rotten vegetables"+
		( Alcohol_per > 0 ? " and stale alcohol." : "." )));
	}
	return 1;
    }
    return 0;
} /* smell_eat_scraps */


/*
 * Function name:	feed_scraps
 * Description	:	handle attempts to give/feed/show scraps
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 otherwise
 *
 * if pig or chickens, feed them. otherwise, we write a nice
 * msg but do not actually feed the target.
 */
public int
feed_scraps(string arg)
{
    mixed	*oblist;
    int		parse_ret;
    string	vb = QVB,
		failstr;

    if (!CAN_SEE_IN_ROOM(TP) ||
	!strlen(arg))
    {
        return 0;
    }

    if (vb != "lure") /* feed, give, show */
    {
	parse_ret = parse_command(LOW(arg), ENV(TP),
	    "[some] [kitchen] 'scraps' 'to' %l", oblist);
	failstr = capitalize(vb)+" what to whom?\n";
    }
    else	/* lure */
    {
	parse_ret = parse_command(LOW(arg), ENV(TP),
	    "%l [with] [some] [kitchen] 'scraps'", oblist);
	failstr = "Lure whom with what?\n";
    }

    if (parse_ret)
    {
	oblist = NORMAL_ACCESS(oblist, 0, 0);
	if (!sizeof(oblist))
	{
	    NF0(failstr);
	}

	if (oblist[0] == TP)
	{
	    if (vb == "feed")
	    {
		NFN0("The scraps smell too nasty to put in your mouth.");
	    }
	    /* give,show,lure */
	    NFN0("You already have the scraps.");
	}

	if (oblist[0]->query_attack())
	{
	    /* don't use notify_fail here, because normal "give" will
	     * intercept it
	     */
	    write(oblist[0]->query_The_name(TP)+" is busy fighting.\n");
	    return 1;
	}

	if (oblist[0]->id(PIGNAME))
	{
	    if (oblist[0]->feed_scraps(TO))
	    {
	    	remove_object();
	    }
	    return 1;
	}

	if (oblist[0]->id("chicken"))
	{
	    if (Alcohol_per ||
		Poison_str)
	    {
		write("You approach the "+oblist[0]->short()+
		    " with the scraps. "+
		    capitalize(oblist[0]->query_pronoun())+
		    " seems interested at first, but then backs away.\n");
		return 1;
	    }
	    if (vb == "feed" ||
		vb == "give")
	    {
		write(BSN("You feed the scraps to the "+
		    oblist[0]->short()+"."));
		/* feed is visible */
		SAY(" feeds some scraps to the "+
		    oblist[0]->short()+".");
		remove_object();
		return 1;
	    }
	    /* lure or show */
	    write(BSN("You show the scraps to the "+
		oblist[0]->short()+", who peers at you hungrily."));
	    return 1;
	}

        if (vb == "feed")
	{
	    write(BSN("You try to feed the scraps to "+
		oblist[0]->query_the_name(TP)+", but "+
		oblist[0]->query_pronoun()+" backs away."));
	    oblist[0]->CATCH_MSG(" tries to feed some kitchen scraps to "+
		"you. You quickly back away.", TP);
	    /* XXX tell the rest of the room? */
	    return 1;
	}
        else if (vb == "lure")
	{
	    write(BSN("You wave the scraps in the face of "+
		oblist[0]->query_the_name(TP)+"; "+
		oblist[0]->query_pronoun()+" backs away."));
	    oblist[0]->CATCH_MSG(" waves some kitchen scraps in "+
		"your face. You quickly back away.", TP);
	    /* XXX tell the rest of the room? */
	    return 1;
	}
	/* else default handling of "give" and "show" works fine */
    }
    NF0(failstr);
} /* feed_scraps */


/*
 * Function name:	add_alcohol
 * Description	:	update alcohol contents of scraps
 * Arguments	:	int soft_amt -- quantity of liquid added
 *			int alco_amt -- quantity of alcohol added
 */
public void
add_alcohol(int soft_amt, int alco_amt)
{
    int		newper,
		total;

    if (!soft_amt)
    {
	return;
    }
    if (My_short != "some soggy kitchen scraps")
    {
	My_short = "some soggy kitchen scraps";
	set_long("The scraps include apple cores, potato parings, "+
	    "onion skins and other vegetable matter that you cannot "+
	    "quite identify. They are soggy and have begun to decay; "+
	    "they smell nasty.\n");
    }
    newper = (alco_amt * 100) / soft_amt;
    total = Soft_amt + soft_amt;
    Alcohol_per = (((Alcohol_per * Soft_amt) + (newper * soft_amt))
	/ total);
    Soft_amt = total;
} /* add_alcohol */


/*
 * Function name:	add_poison
 * Description	:	update poison contents of scraps
 * Arguments	:	object herb -- the poison herb
 *			int str -- the strength of the poison
 * poison strength must be >= MIN_POIS_STR and the damage
 * done to hp must be >= MIN_POISON_DAMAGE, or the poison is ignored.
 */
public void
add_poison(object herb, int str)
{
    mixed	*dmg_arr;
    int		i, n;

    if (str < MIN_POIS_STR ||
	!objectp(herb) ||
        !(n = sizeof(dmg_arr = herb->query_poison_damage())))
    {
	return;
    }

    for (i = 0; i < n; i += 2)
    {
	if (dmg_arr[i] == POISON_HP)
	{
	    if (dmg_arr[i+1] < MIN_POIS_DAM)
	    {
		return;
	    }
	    break;	/* for */
	}
    }
    if (i < n)
    {
	Poison_str += str;
	Poison_dam += dmg_arr[i+1];
    }
} /* add_poison */


/*
 * Function name:	crumble_scraps
 * Description	:	crumble scraps if dropped
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we match the arg, 0 if not
 *
 * Need to do this because players are leaving the bowl of scraps sitting in
 * the sty, which makes it just a little too easy for the next person.
 */
public int
crumble_scraps(string arg)
{
    object	ob, env = ENV(TP);
    string	floor;

    if (!arg ||
	 !parse_command(arg, ({ TO }), "%o", ob))
    {
	return 0;
    }

    floor = (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");
    write("You drop some kitchen scraps.\n");
    SAY(" drops some kitchen scraps.");
    tell_room(env, "The scraps crumble to bits when they hit the "+
	 floor+".\n");
    remove_object();
    return 1;
} /* crumble_scraps */
