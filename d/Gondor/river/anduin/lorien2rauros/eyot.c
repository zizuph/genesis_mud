/*
 * /d/Gondor/river/anduin/lorien2rauros/eyot.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * the day 6 campsite: "a small eyot close to the western bank"
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room" shore;
inherit "/d/Gondor/river/anduin/anduin_tod" tod;
inherit "/d/Gondor/gnadnar/wiz_chairs" chairs;

/* inherit "/d/Gondor/open/room_chairs/room_chairs" chairs; */

#include <composite.h>		/* for COMPOSITE_LIVE, DEAD */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include <ss_types.h>		/* for SS_AWARENESS */
#include <stdproperties.h>	/* for OBJ_S_WIZINFO, etc */
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define	MIN_AWARE	20
#define	RANDOM_AWARE	10
#define	BUSHES		(LORIEN_TO_RAUROS_DIR+"eyot_bushes")

#define	RIVER_EAST	(LORIEN_TO_RAUROS_DIR+"river13e")
#define	RIVER_WEST	(LORIEN_TO_RAUROS_DIR+"river13w")

#define	LOG_NAME	"moss-grown log"

#ifdef XYZZY
#define	RACE(tp) \
    ((tp)->query_real_name()[0..6] == "gnadnar" ? \
	"gnome" : (tp)->query_race())
#else
#define	RACE(tp)	((tp)->query_race())
#endif


/* prototypes */
public void	create_shore_room();
public void	init();
public int	enter_bushes(string arg);
public string	do_search(object tp, string arg);
public string	exa_river();
public string	exa_log();
public void	msgs_before_move(object tp, string verb, string watertype);
public void	leave_inv(object ob, object dest);


static object	RiverE,		/* the river room to the east */
		RiverW;		/* the river room to the west */	

/*
 * Function name:	create_shore_room
 * Description	:	set up the eyot
 */
public void
create_shore_room()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("the day 6 campsite: a small eyot close to the western bank, "+
	    "255 miles downstream from the silverlode."));
    set_short("small eyot");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("Low, tangled bushes blanket the eyot, "+
	"crowding around a large log. "+
	"On either side, the Great River flows south.");
    set_tod_landname("the Downs");
    set_tod_landtype("eyot");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("east",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    add_chair(LOG_NAME, "[down] [on] [the] [large] [moss-grown] 'log'", 6);
    add_item( ({ "large log", "moss-grown log", "log", }), exa_log);
    add_cmd_item( ({ "large log", "moss-grown log", "log" }),
	({ "push", "move", "roll", "shove", "get", "take" }),
	"You cannot budge the log.\n" );

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_exit("river13e", "east", 0, 2, 1);
    add_exit("river13w", "west", 0, 2, 1);
    set_no_exit_msg( ({ "northeast", "northwest", "southwest",
	"south", "southeast" }),
	BSN("You try to make your way into the bushes, but they "+
	    "are too tangled and their thorns too sharp."));

    add_item( ({ "island", "small eyot", "eyot" }), long);
    add_item( ({ "thorn bushes", "low bushes", "tangled bushes",
	"bush", "bushes" }),
	BSN("The bushes grow low to the ground, tangled together "+
	    "in a thorny weave."));
    add_item( ({ "weave", "thorn", "thorns" }),
	BSN("The long, sharp thorns interlace in a dense weave."));
    add_item( ({ "ground", "gravel" }),
	BSN("The ground is hard, and scattered with gravel."));
    add_item( ({ "eastern shore", "eastern bank", "western shore",
	"western bank", "east shore", "east bank", "west shore",
	"west bank", "shore", "shores", "river bank", "river banks",
	"bank", "banks", "plains", "downs", "land" }),
	BSN("Rolling, treeless plains rise on either side of the river."));
    add_item( ({ "sides", "side", "east channel", "west channel",
	"eastern channel", "western channel", "great river", "waters",
	"water", "river anduin", "anduin river", "anduin", "river" }),
	exa_river);
    add_item( ({ "soft green moss", "soft moss", "green moss", "moss" }),
	BSN("The moss looks like soft green fur."));
    
    add_cmd_item( ({ "log", "soft green moss", "soft moss",
	"green moss", "moss" }),
	({ "touch", "feel", "stroke", "pet" }),
	BSN("The moss is like velvet to the touch."));

    set_anduin_tod_descs();
} /* create_shore_room */


/*
 * Function name:	init
 * Description	:	add player verbs re entering bushes, sitting on log
 */
public void
init()
{
    shore::init();
    init_room_chairs();
    add_action(enter_bushes, "enter");
    add_action(enter_bushes, "crawl");
    add_action(enter_bushes, "north");
    add_action(enter_bushes, "n");
} /* init */


/*
 * Function name:	enter_bushes
 * Description	:	if player is of a small race, let 'em enter
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if ok arg (whether or not they're allowed
 *			to enter), 0 if not.
 */
public int
enter_bushes(string arg)
{
    string	race,
		vb = QVB;
    object	tp = TP;

    if (vb == "enter" &&
	(!strlen(arg) ||
	 !parse_command(LOW(arg), ({}),
	      "[the] [low] [tangled] 'bushes' / 'bush'")))
    {
	NF0("Enter what?\n");
    }
    if (vb == "crawl" &&
	(!strlen(arg) ||
	 (arg != "north" &&
	  !parse_command(LOW(arg), ({}),
	      "'under' / 'in' / 'into' [the] [low] [tangled] "+
	      "'bushes' / 'bush'"))))
    {
	NF0("Crawl where?\n");
    }
    race = RACE(tp);
    check_sitting();
    if (race != "hobbit" &&
	race != "gnome" &&
	race != "dwarf")
    {
	WRITE("You try to make your way into the bushes, but they "+
	    "are too tangled and their thorns too sharp.");
    }
    else
    {
	WRITE("You crouch down and crawl under the bushes.");
	tp->move_living("into the bushes", BUSHES);
    }
    return 1;
} /* enter_bushes */


/*
 * Function name:	do_search
 * Description	:	handle searching the bushes
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 */
public string
do_search(object tp, string arg)
{
    object	*in_bushes;
    string	race;

    if (!parse_command(LOW(arg), ({}),
	               "[the] [low] [tangled] 'bushes' / 'bush'"))
    {
	return "";
    }
    tell_room(BUSHES, "Something shakes the bushes.\n");
    race = RACE(tp);
    if (tp->query_skill(SS_AWARENESS) < (MIN_AWARE + random(RANDOM_AWARE)))
    {
	if (race != "hobbit" &&
	    race != "gnome" &&
	    race != "dwarf")
	{
	    return "You search the bushes, but find only sharp thorns.\n";
	}
	return BSN("The bushes are thick and tangled, but you might "+
	       "be able to enter them.");
    }

    FIX_EUID;
    BUSHES->short();
    in_bushes = FILTER_LIVE(all_inventory(find_object(BUSHES)));
    if (!sizeof(in_bushes))
    {
	if (race != "hobbit" &&
	    race != "gnome" &&
	    race != "dwarf")
	{
	    return "You search the bushes, but find only sharp thorns.\n";
	}
	return BSN("The bushes are thick and tangled, but you might "+
	       "be able to enter them.");
    }
    if (race != "hobbit" &&
	race != "gnome" &&
	race != "dwarf")
    {
	return BSN("You cannot be sure, but you have the feeling "+
	    "that something may be hiding in the bushes.");
    }
    return BSN("You cannot be sure, but you have the feeling "+
	"that something may be hiding in the bushes. You might "+
	"be able to enter the bushes yourself.");
} /* do_search */


/*
 * Function name:	exa_river
 * Description	:	VBFC for the river -- mention any swimmers or boats
 * Returns	:	the river desc
 *
 * can't use the standard exa_water() from shore_room.c since there's
 * water on both sides.
 */
public string
exa_river()
{
    object	*on_river,
		*live_on_river;
    string	desc;
    int		s;

    desc = "To the east and the west, the Anduin glitters "+
	"as it flows past the eyot.\n";

    FIX_EUID;
    if (!objectp(RiverE))
    {
	RIVER_EAST->short();
	RiverE = find_object(RIVER_EAST);
    }
    if (sizeof(on_river = all_inventory(RiverE)))
    {
	if (!TP->query_wiz_level())
	{
	    /* assume that from a distance, cannot see hidden or invis */
	    on_river = filter(filter(on_river,
		&not() @ &->query_prop(OBJ_I_HIDE)),
		&not() @ &->query_invis());
	}
	live_on_river = FILTER_LIVE(on_river);
	s = sizeof(live_on_river);
	if (s)
	{
	    desc += CAP(COMPOSITE_LIVE(live_on_river))+
		    (s == 1 ? " is " : " are ")+
		    "swimming in the river on the east side of the eyot.\n";
	    on_river -= live_on_river;
	}
	s = sizeof(on_river);
	if (s)
	{
	    desc += CAP(COMPOSITE_DEAD(on_river))+
		(s == 1 ? " is " : " are ")+
		"floating in the river on the east side of the eyot.\n";
	}
    }
    if (!objectp(RiverW))
    {
	RIVER_WEST->short();
	RiverW = find_object(RIVER_WEST);
    }
    if (sizeof(on_river = all_inventory(RiverW)))
    {
	if (!TP->query_wiz_level())
	{
	    /* assume that from a distance, cannot see hidden or invis */
	    on_river = filter(filter(on_river,
		&not() @ &->query_prop(OBJ_I_HIDE)),
		&not() @ &->query_invis());
	}
	live_on_river = FILTER_LIVE(on_river);
	s = sizeof(live_on_river);
	if (s)
	{
	    desc += CAP(COMPOSITE_LIVE(live_on_river))+
		    (s == 1 ? " is " : " are ")+
		    "swimming in the river on the west side of the eyot.\n";
	    on_river -= live_on_river;
	}
	s = sizeof(on_river);
	if (s)
	{
	    desc += CAP(COMPOSITE_DEAD(on_river))+
		(s == 1 ? " is " : " are ")+
		"floating in the river on the west side of the eyot.\n";
	}
    }
    return desc;
} /* exa_river */


/*
 * Function name:	exa_log
 * Description	:	VBFC for log; include occupants.
 * Returns	:	string -- the desc
 */
public string
exa_log()
{
    return BSN("The log is quite large, and covered with soft green moss. "+
	"Since there are no trees on the eyot, it must have washed ashore "+
	"from somewhere upstream.")+
	sitting_on_chair(LOG_NAME, TP, 0);
} /* exa_log */


/*
 * Function name:	msgs_before_move
 * Description	:	mask parent so we check for seated players.
 * Arguments	:	object tp -- this_player
 *			string verb -- swim, wade, dive, ...
 *			string watertype -- river, pool, ....
 */
public void
msgs_before_move(object tp, string verb, string watertype)
{
    check_sitting();
    ::msgs_before_move(tp, verb, watertype);
} /* msgs_before_move */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from log occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    shore::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */
