/*
 * /d/Gondor/river/anduin/anduin_onwater.c
 *
 * Base onwater room for the anduin:
 * 	associate a distance (in miles) with each in-water exit
 *	experiment with ways to prevent swimming entire river
 */

#pragma strict_types

inherit "/d/Gondor/std/water/onwater";
inherit "/d/Gondor/river/anduin/anduin_tod";

#include "/d/Gondor/std/water/onwater.h"
#include "/d/Gondor/defs.h"
#include "anduin.h"



/* prototypes */
public void	create_anduin_onwater();
nomask void	create_onwater();
public void	set_distance(string dir, int dist);
public string	query_distance(string dir);
public int	swim_float_fatigue(int skill, string dir, int type, object pl);


static mapping	Distances = ([ ]);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up your room here
 */
public void
create_anduin_onwater()
{
} /* create_anduin_onwater */


/*
 * Function name:	create_onwater
 * Description	:	set up the base onwater room
 */
nomask void
create_onwater()
{
    create_anduin_onwater();
    set_anduin_tod_descs();
} /* create_onwater */


public void	set_distance(string dir, int dist)	{ Distances[dir] = dist; }
public string	query_distance(string dir)		{ return Distances[dir]; }


/*
 * Function name:	swim_float_fatigue
 * Description	:	mask parent to make fatigue also depend on distance
 * Arguments	:	int skill -- player's swimming (or boating) skill
 *			string dir -- the direction to swim
 *			int type -- WATER_MOVE_SWIM, WATER_MOVE_FLOAT or 
 *				    WATER_MOVE_WADE
 *			object pl -- the player
 * Returns	:	positive integer -- the fatigue to be incurred;
 *			    caller must check against player's current fatigue
 *			    and decide whether to invoke add_fatigue(),
 *			    or to fail the swim attempt.
 *			or -1 -- cannot swim in that dir
 */
public int
swim_float_fatigue(int skill, string dir, int type, object pl)
{
    int		fatigue,
		dist;

    fatigue = ::swim_float_fatigue(skill, dir, type, pl);
    if ((dist = Distances[dir]) > 1)
    {
	if (type != WATER_MOVE_ROW)
	{
	    /* are in the water -- bump the fatigue lots
	     * to account for distance
	     */
	    fatigue = SWIM_FATIGUE_FOR_DISTANCE(fatigue, dist);
	    DBG(pl, "Fatigue bumped to "+fatigue+" for distance "+dist+".\n");
	}
	else
	{
	    /* rowing -- bump the fatigue some to account for distance */
	    fatigue = ROW_FATIGUE_FOR_DISTANCE(fatigue, dist);
	    DBG(pl, "Fatigue bumped to "+fatigue+" for distance "+dist+".\n");
	}
    }
    return fatigue;
} /* swim_float_fatigue */
