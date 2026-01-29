/*
 * /d/Shire/rivendell/room/river/in_ford.c
 *
 * evils will have a very bad time here.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/onwater";

#include <composite.h>
#include <macros.h>
#include "local.h"

/* set NO_GONDOR_DEFS so onwater won't try to include ~gondor/defs.h */
#define	NO_GONDOR_DEFS	
#include "/d/Gondor/std/water/onwater.h"

#define	MIN_ALIGN	100

public void	create_onwater();
public void	enter_inv(object ob, object from);
public int	check_alignment();
public int	block_exit();
public void	float_downstream(object pl);


/*
 * Function name:	create_onwater
 * Description	:	set up the ford
 */
public void
create_onwater()
{
    set_short("In the ford of the Bruinen");
    set_long(BSN("The Bruinen flows from north to southwest. "+
	"Its cold, swift waters are just shallow enough "+
	"to ford here."));

    set_depth(MAX_WADE_DEPTH);
    set_currentstr(MODERATE_CURRENT);
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_watertype("ford");
    set_waterrefs( ({ "water", "waters", "ford", "river",
	"bruinen", "river bruinen", "bruinen river", "loudwater",
	"river loudwater", "loudwater river",  }) );

#ifdef NOTYET
    add_exit(FOREST_DIR + "track01", "east", check_alignment, 3);
    add_exit(ER_DIR     + "erb38",   "west", check_alignment, 3);
#else /* NOTYET */
    add_exit("tmp1", "west", check_alignment, 3);
    add_exit("tmp2", "east", check_alignment, 3);
#endif /* NOTYET */

    /* river00 does not exist. we add the exit so that the
     * messages will look right, though.
     */
    add_exit("river00", "north", block_exit);
    add_exit("river01", "southwest", block_exit);

} /* create_onwater */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to hasten alarms for washing
 *			evils downstream
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    if (!living(ob) ||
	ob->query_alignment() >= MIN_ALIGN)
    {
	::enter_inv(ob, from);
	return;
    }

    /* we want to wash them downstream *fast* */
    ::::enter_inv(ob, from);
    ob->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_SWIM);
    ob->add_prop(OBJ_I_WATER_ALARM, 
	set_alarm(0.5, 0.0, &float_downstream(ob)));
} /* enter_inv */



/*
 * Function name:	check_alignment
 * Description	:	prevent evils from taking shore exits
 * Returns	:	0 if exit allowed, 1 if not
 */
public int
check_alignment()
{
    if (TP->query_alignment() >= MIN_ALIGN)
    {
	return 0;	/* exit allowed */
    }
    /* XXX what msg? */
    write(BSN("The cold waters crash over you, forcing you "+
	"back from the shore."));
    return 1;
} /* check_alignment */


/*
 * Function name:	block_exit
 * Description	:	block up- and downstream exits, so they
 *			can't swim away. we will move evils downstream
 *			by hand.
 * Returns	:	1 -- exit never allowed
 */
public int
block_exit()
{
    write(BSN("The waters are swift and icy cold, and appear dangerous. "+
	"You decide not to risk it."));
    return 1;	/* exit not allowed */
} /* block_exit */


/*
 * Function name:	float_downstream
 * Description	:	wash evils downstream, just do msgs for
 *			everyone else :-)
 * Arguments	:	object ob -- the entering person
 */
public void
float_downstream(object ob)
{

    if (!objectp(ob) ||
	ENV(ob) != TO)
    {
	return;
    }

    ob->remove_prop(OBJ_I_WATER_ALARM);
    if (ob->query_alignment() >= MIN_ALIGN)
    {
	/* the default enter-water set up an alarm, but
	 * we don't want to wash them downstream 
	 */
	return;
    }
    
    /* XXX better msgs? */
    write(BSN("The river rises up, violently churning, and drags you "+
	"off your feet. You are pulled under and swept away."));
    say("The river suddenly rises up violently against "+
	QTNAME(ob)+". "+CAP(PRONOUN(ob))+" disappears beneath "+
	"the water and is swept downstream.\n");
    ob->move_living("M", "/d/Shire/rivendell/room/river/river01");
    tell_room(ENV(ob),
	QNAME(ob)+" is swept in by the foaming current.\n",
	ob);

} /* float_downstream */
