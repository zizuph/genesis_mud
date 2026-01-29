/*
 *	/d/Gondor/ithilien/nforest/pool.c
 *
 *	Coded by Olorin, 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *
 *	3-Dec-1997, Gnadnar:	Changed to hook up with guild/ithilien/pool 
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>	/* for OBJ_I_CONTAIN_WATER	*/
#include <ss_types.h>		/* for SS_SWIM			*/
#include <macros.h>		/* for QCTNAME			*/
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define	RANGER_ITHILIEN_VISITOR	"ranger_ithilien_visitor"
#define POOL           (RANGERS_ITH_DIR + "pool")
#define	MIN_SWIM_SKILL		20

public void	create_area_room();
public void	init();
public string	exa_pool();
public int	enter_pool(string arg);


/*
 * Function name:	create_area_room
 * Description	:	set up the room
 */
public void
create_area_room()
{
    FIX_EUID;	/* since we may try to load the guild pool */
    set_areatype(7);
    set_areadesc("ledge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");

    set_extraline(
        "From the top of the large rock to the east, a torrent plunges "+
	"south into an oval basin. The falling water forms a beautiful "+
	"veil as it pours into the foaming bowl, spraying everything with "+
	"a fine shower of water droplets. From the pool, the water runs "+
	"through a small cleft in the west.");

    add_item( ({"veil", "waterfall", "waters", "water", "fall", }), BSN(
        "The waterfall plunges from a flat even edge at the top of "+
        "the rock, shaping the fall into a thin veil of water. "+
	"The water pours into a pool below you."));
    add_item( ({"oval basin", "basin", "bowl", "pool"}), exa_pool);
    add_item( ({ "stream" }), BSN(
	"Leaving the pool, the waters flow into a calmer stream to the west."));
    add_item( ({ "cleft", }), BSN(
        "The waters find their way out of the pool through a narrow " +
        "cleft to the west."));
    add_item( ({ "rocky ledge", "ledge" }), BSN(
	"The rocky ledge angles west through the cleft, high "+
	"above the pool."));

    add_item( ({ "cliff", "wall", "rock", "rock wall", }), BSN(
        "From here you can see the northwestern side of the large rock. " +
        "Over a flat even edge at the top of the rock a waterfall " +
        "plunges down into the oval basin. The northern cliff of the " +
        "waterfall is steep and featureless, so that it is impossible " +
        "to climb it."));

    add_exit(ITH_DIR + "nforest/sstream8", "northeast", 0, 3);
    add_exit(ITH_DIR + "nforest/sstream9", "west",      0, 3);

    add_cmd_item( ({ "from pool", "from basin",
	"water from pool", "water from basin" }),
	"drink",
	BSN("The pool is too far below you, and the waters too "+
	    "turbulent, for you to drink safely."));
} /* create_area_room */


/*
 * Function name:	init
 * Description	:	add verbs for pool
 */
public void
init()
{
    ::init();
    add_action(enter_pool, "swim");
    add_action(enter_pool, "dive");
    add_action(enter_pool, "enter");
} /* init */



/*
 * Function name:	exa_pool
 * Description	:	VBFC for guild pool
 * Returns	:	string -- desc of pool + swimmers
 */
public string
exa_pool()
{
    string	swimming = "";
    object	pool;

    POOL->short();
    if (objectp(pool = find_object(POOL)))
    {
	swimming = pool->query_swimmers();
    }

    return(BSN(
        "The oval basin below you is filled with foaming waters " +
        "that plunge into the pool from the top of the rock. "+
	"The waters swirl around in the bowl, until they find their way "+
	"out again " +
        "through a narrow cleft, and flow away, fuming and chattering, " +
        "into calmer and more level reaches to the west. "+
	swimming));
} /* exa_pool */


/*
 * Function name:	enter_pool
 * Description	:	handle attempts to enter pool
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
enter_pool(string arg)
{
    string	dest;
    object	tp;

    if (!strlen(arg))
    {
	NF0(capitalize(query_verb())+" where?\n");
    }

    if (!sscanf(arg, "in %s", dest) &&
	!sscanf(arg, "into %s", dest))
    {
	dest = arg;
    }

    if (dest != "pool" &&
	dest != "bowl" &&
	dest != "basin" &&
        dest != "oval basin")
    {
	NF0(capitalize(query_verb())+" where?\n");
    }

    tp = TP;

    if (tp->query_skill(SS_SWIM) < MIN_SWIM_SKILL)
    {
	NFN0("You advance to the edge of the pool, but "+
	    "change your mind when you see the foaming "+
	    "waters at close range.");
    }

    if (tp->query_guild_name_occ() != "Rangers of the Westlands" &&
        !tp->query_prop(RANGER_ITHILIEN_VISITOR))
    {
	write(BSN("You dive into the foaming waters of the "+dest+"."));
	SAYBB(" dives into the pool and is swept downstream "+
	    "by the foaming waters.\n");
	write(BSN("You are swept downstream by the turbulent waters."));
	tell_room(POOL, 
	    QCNAME(TP)+" dives into the pool from high on the northwest "+
	    "wall. "+capitalize(TP->query_pronoun())+" is immediately "+
	    "swept away through the cleft by the foaming waters.\n");
    	write(BSN("The waters grow calmer and you climb out of the stream."));
	tp->move_living("M", (ITH_DIR+"nforest/sstream9"));
	if (TP != tp)
	{
	    set_this_player(tp);
	}
	tell_room(ENV(tp),
	    QCNAME(tp)+" climbs out of the stream.\n", tp);
	return 1;
    }

    write(BSN("You dive into the foaming waters of the "+dest+"."));
    SAYBB(" dives into the pool.");
    /* people in this room might not notice a well-hidden player
     * leaving, but people in the pool definitely will notice when
     * s/he arrives
     */
    tell_room(POOL,
	QCNAME(tp)+" dives into the pool from high on the northwest wall.\n",
	tp);

    tp->move_living("M", POOL);
    if (TP != tp)
    {
	set_this_player(tp);
    }

    return 1;
} /* enter_pool */
