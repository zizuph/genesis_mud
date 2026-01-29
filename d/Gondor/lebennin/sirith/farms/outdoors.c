/*
 * /d/Gondor/lebennin/sirith/farms/outdoors.c	
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * standard file for outdoors rooms in SIRITH_FARMS_DIR
 * inherits /d/Gondor/lebennin/sirith/room
 *
 * if no specific setup done, is a field in southern Lebennin planted
 * with a random crop.
 *
 * adds check_lightlevel(), default descriptions, and VBFC for
 * time-of-day-dependent item descriptions
 *
 * known room types are "track", "field" and "pasture".
 * to use this for some other type of outdoor room, you have to roll
 * your own. in create_outdoors(), set:
 *	short via set_short()
 *	long via set_extraline()
 *	noitems via set_noitems(1)
 *	items & cmd items EXCEPT for sky/sun/moon/star/stars
 *	herbs
 * you still get the cool time-of-day effects, tweaked doors and
 * custom msgs for non-existent exits.
 *
 * cool time-of-day effects swiped from common/lib/area_room, which
 * was almost, but not quite, what i needed.
 *
 * varying description/items idea swiped from gorboth, who says he
 * swiped it from mercade.
 *
 * ASSUMPTIONS/WARNINGS:
 * 1) if inheriting rooms set Area, Areatype, Areaname, ... to
 *    0 or to null strings, the default descriptions will have 0's or
 *    odd gaps in them.
 * 2) all fields are enclosed by fairly deep ditches. if this is not so,
 *    remove_item "ditch" and "ditches", and roll your own item desc 
 *    for "field" and "fields".
 * 3) for a given field, there is a non-diagonal (n,s,e,w) exit to a 
 *    track on at most one side of the field. there does not have to 
 *    be a track exit at all. the direction of the track is configured
 *    via set_trackdir().
 * 4) similarly for pastures, at most one (n,s,e,w exit) to a field.
 *    the direction of the field is configured via set_ditchdir().
 * 5) tracks should call set_trackdir() with an array of the non-obvious-
 *    exit-directions to fields. XXX overloading a routine is sloppy.
 * 6) not applying Trackdir to pasture. gonna make it awfully cluttered,
 *    since we have to apply Ditchdir. ("have to", because if they move
 *    from field to pasture, they'll get the crossing-the-ditch msg,
 *    and so they really should get the msg going from pasture to field,
 *    which means that pasture must know about ditch.)  all the same,
 *    decided not to use trackdir for "pasture ditch direction", since
 *    a) it's confusing to use the same variable for two different things
 *    and b) that would preclude ever mentioning tracks from pastures.
 * 7) if noitems is set, you must set extraline 
 * 8) only one door/gate per room (at least for now)
 *
 *
 * Fields may have a track on only one of their n/e/s/w sides.
 * However, if diagonal movement is allowed, then a track to ohhhh
 * the east can also be reached going northeast and southeast.
 * Similarly for pastures and ditches.
 * So, Trackdir and Ditchdir may be initialized with either a string
 * or an array. if the latter, the 0th element of the array is
 * assumed to be the "primary" direction; the others are the diagonals.
 */


#pragma strict_types

#include <macros.h>			/* for VBFC_ME		*/
#include <stdproperties.h>		/* for ROOM_I_LIGHT	*/
#include <language.h>			/* for LANG_ADDART	*/
#include "/d/Gondor/defs.h"
#include "defs.h"

inherit "/d/Gondor/lebennin/sirith/room";
inherit "/d/Gondor/common/lib/herbsearch";

#define	CROPS	 ({ "barley", "wheat", "clover", "oats", "vetch" })
#define CROP_SIZE	5	/* must keep this in sync w/ CROPS */

/*
 * Globals that may be configured via set_*
 */
static string	Areaname = "Lebennin";	/* Lebennin, Rohan, ...		*/
static string	Area = "southern";	/* what area of Areaname ...	*/
static string	Areatype = "field";	/* field, track, pasture, ...	*/
static string	Areacrop;		/* oats, wheat, barley, ...	*/
static string	*Trackdir = ({});      /* direction of track from field	*/
static string	*Ditchdir = ({});    /* direction of ditch from pasture	*/
static string	Extraline;		/* additional room description 	*/
static int	Noitems;		/* !0 -> no area items added	*/
static string	Climbdest;	      /* destination if climb door/gate	*/
				      /* (only makes sense for gates)	*/

/* 
 * Other globals
 */
static string	Areadesc;		/* description for use in long	*/
					/* if Extraline not set		*/
static string	*Getnames = ({ });	/* names that might try to get	*/
static string	Getmsg;			/* for pick/get/take Getnames	*/


/*
 * Prototypes for configuring area ..
 */
public void	set_areaname(string name);
public void	set_area(string area);
public void	set_areatype(string type);
public void	set_trackdir(mixed direction);
public void	set_ditchdir(mixed direction);
public void	set_extraline(string extraline);
public void	set_noitems(int val);
public void	set_climbdest(string path);
public void	set_getnames(mixed names);
public void	set_getmsg(string msg);
public int	set_areacrop(string crop);

/*
 * Other prototypes
 */
public void	create_outdoors();
public void	create_sirith();
public void	init();
static void	set_areadesc0();
static void	set_areadesc1();
public int	check_lightlevel();
public string	long_desc();
public int	ditch_msg();
public int	climb(string arg);
public string	query_areacrop();
public int	pick_crop(string arg);
public int	cross_ditch(string arg);


/*
 * Function name:	create_outdoors
 * Description  :	redefine this to create outdoors rooms
 *			in SIRITH_FARMS_DIR
 */
public void
create_outdoors()
{
} /* create_outdoors */


/*
 * Function name:	create_sirith
 * Description  :	constructor
 */
nomask void
create_sirith()
{
    string	*herbslist;

    add_prop(ROOM_I_LIGHT, check_lightlevel);
    create_outdoors();

    if (!query_short())
    {
	/* e.g., "a field in southern Lebennin" */
	set_short(LANG_ADDART(Areatype)+" in "+Area+" "+Areaname);
    }
    if (!query_long())
    {
	set_long(long_desc);
    }

    /* add items for time-of-day effects.
     * since long_desc() mentions clouds only in the "cannot happen" cases,
     * don't add an item for them.
     */
    try_item(({ "sky", "sun", "moon", "star", "stars" }), long_desc);

    /* be sure Areacrop is set before setting area items */
    if (Areatype == "field" && !strlen(Areacrop))
    {
    	set_areacrop("");
    }

    /*
     * set area default description and items.
     * used to do this all in one routine, but the indentation started
     * approaching the right margin, so decided to pull them out into
     * separate routines.
     */
    if (!Noitems)
    {
    	if (!random(2))
	{
	    set_areadesc0();
	}
    	else
	{
	    set_areadesc1();
	}
    }

    /* if field, pasture or track, have herbs */
    if (Areatype == "field" || Areatype == "pasture")
    {
    	herbslist = HERB_MASTER->query_herbs( ({ "moderate", "meadow",
	                                         "plains", "lebennin" }) );
    	set_up_herbs(({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist), 
       		        ONE_OF_LIST(herbslist) }),
	    	     ({ Areatype, "ground", "grass", "grasses", "plants" }),
		     5);
    }
    else if (Areatype == "track")
    {
    	/* not so many herbs on track */
    	herbslist = HERB_MASTER->query_herbs( ({ "moderate", "plains",
						 "lebennin" }) );
    	set_up_herbs(({ ONE_OF_LIST(herbslist) }),
	             ({ Areatype, "ground" }), 7);
    }


} /* create_sirith */


public void
init()
{
    ::init();
    if (strlen(Climbdest))
    {
        add_action(climb, "climb");
    }

    if (Areatype == "field" ||
        Areatype == "track" ||
        Areatype == "pasture")
    {
        add_action(pick_crop, "get");
        add_action(pick_crop, "take");
        add_action(pick_crop, "pick");

        add_action(cross_ditch, "enter");
        add_action(cross_ditch, "cross");
        add_action(cross_ditch, "jump");
        add_action(cross_ditch, "leap");
    }
} /* init */


/* here are the simple ones ... */
public void	set_extraline(string extraline)	{ Extraline = extraline; }
public void	set_area(string area)		{ Area = area; }
public void	set_areatype(string type)	{ Areatype = type; }
public void	set_areaname(string name)	{ Areaname = name; }
public void	set_noitems(int val)		{ Noitems = val; }
public void	set_climbdest(string path)	{ Climbdest = path; }
public void set_trackdir(mixed direction) { Trackdir = ARRAY(direction); }
public void set_ditchdir(mixed direction) { Ditchdir = ARRAY(direction); }
public void	set_getnames(mixed names) { Getnames = ARRAY(names); }
public void	set_getmsg(string msg)		{ Getmsg = msg; }
public string	query_areacrop()		{ return Areacrop; }


/*
 * Function name:	set_areacrop
 * Description  :	sets the crop of room (e.g., "oats" ) & item descs
 * Arguments	:	the crop
 * Returns      :	non-negative integer if the crop is known (and so 
 *			    good default descriptions can be generated);
 *			negative integer if crop is unknown (in which
 *			    case inheriting room had better do its own
 *			    item descriptions for the crop), or if crop
 *			    was null.
 *
 * if crop arg is null, a crop will be chosen at random from known list.
 *
 */
public int
set_areacrop(string crop)
{
    int	index;

    if (strlen(crop))
    {
	Areacrop = crop;
	index = member_array(Areacrop, CROPS);
    }
    else
    {
    	index = random(CROP_SIZE);
    	Areacrop = CROPS[index];
    }

    if (!Noitems)
    {
	/* add descs of known crops; fake it for unknown */
	switch (Areacrop)
	{
	case "barley":
	    if (try_item(({ "spikes of flowers", "spikes", "grass",
		"grasses", "flower", "flowers", "plant", "plants",
		"thriving crop", "thriving crop of barley",
		"crop", "barley" }),
		BSN("The flat-bladed grass has dense, "+
	    	    "bearded spikes of flowers.")))
	    {
		Getnames = ({ "barley", "crop", "spikes of flowers",
		    "spikes", "grass", "grasses", "flower",
		    "flowers", "plant", "plants" });
		Getmsg = "You pick a spike of barley, then toss it away.";
	    }
	    break;
	case "vetch":
	    if (try_item(({ "leaf", "leaves", "plant", "plants",
		"flower", "flowers", "thriving crop",
		"thriving crop of vetch", "crop", "vetch" }),
	    	BSN("The leafy plant has large purple flowers.")))
	    {
		Getnames = ({ "vetch", "crop", "leaf", "leaves", "plant", 
		    "plants", "flower", "flowers" });
		Getmsg = "You pick a few leaves of the vetch, then toss "+
			"them away.";
	    }
	    break;
	case "oats":
	    if (try_item(({ "grass", "grasses", "plant", "plants",
		"thriving crop", "thriving crop of oats", "crop",
		"oat", "oats" }),
	    	BSN("The tall, tufted grass has fairly broad blades.")))
	    {
		Getnames = ({ "grass", "grasses", "plant", "plants",
		    "crop", "oat", "oats" });
		Getmsg = "You pick a few oats, then toss them away.";
	    }
	    break;
	case "wheat":
	    if (try_item(({ "grass", "grasses", "plant", "plants",
		"spikes of wheat", "spikes of grain", "grain",
		"thriving crop", "thriving crop of wheat", "crop", "wheat" }),
	    	BSN("The tall grass has dense spikes of grain.")))
	    {
		Getnames = ({ "wheat", "crop", "grass", "grasses",
		    "spikes of wheat", "spikes of grain", "plant",
		    "plants", "grain" });
		Getmsg = "You pick a spike of wheat, then toss it away.";
	    }
	    break;
	case "clover":
	    if (try_item(({ "plant", "plants", "leaf", "leaves", "flower",
		"flowers", "thriving crop", "thriving crop of clover",
		"crop", "clover" }),
	    	BSN("The low-growing plant has triplets of leaves and "+
		        "rose-coloured flowers.")))
	    {
		Getnames = ({ "clover", "crop", "plant", "plants",
		    "leaf", "leaves", "flower", "flowers" });
		Getmsg = "You pick a sprig of clover, then toss it away.";
	    }
	    break;
	default:
	    if (try_item(({ "thriving crop", "thriving crop of "+Areacrop,
	    	"plant", "plants", Areacrop, "crop" }),
	    	BSN("The "+Areacrop+" appears to be thriving.")))
	    {
		Getnames = ({ Areacrop, "crop", "plant", "plants" });
		Getmsg = "You pick some of the "+Areacrop+
			", then toss it away.";
	    }
	    break;
	} /* switch Areacrop */
    } /* if (!Noitems ) */

    return index;
} /* set_areacrop */



/*
 * Function name:	set_areadesc0
 * Description	:	set default area & items using set 0
 */
static void
set_areadesc0()
{
    int s;
    switch (Areatype)
    {

    case "field":
	Areadesc = "A thriving crop of "+Areacrop+" covers the "+
	    "field, which is enclosed by fairly deep ditches.";
	if (sizeof(Trackdir))
	{
	    Areadesc += " Beyond the "+Trackdir[0]+
		" ditch runs a narrow track.";
	    try_item(({ Trackdir[0]+" ditch", "narrow track",
		"track", "path", "road" }),
		BSN("A narrow track runs beyond the ditch on the "+Trackdir[0]+
		    " side of the field."));
	    /* we ignore diagonal ditch items for now. if anyone ever
	     * files a complaint, we'll add 'em.
	     */
	}
	try_item(({ "field", "fields" }),
	    BSN("The field is circled on all sides by a fairly "+
		"deep ditch, and appears to be sown with "+Areacrop+"."));
	try_item(({ "soil", "dirt", "loam", "ground" }),
	    BSN("The soil seems to be a well-drained, fertile loam."));
	try_item(({ "deep ditches", "deep ditch",
	    "dry ditches", "dry ditch", "ditches", "ditch" }),
	    BSN("The ditch is at least three feet deep. It completely "+
		"encloses the field."));
	/* plus directions */
	try_item(({ "north ditch", "south ditch", "east ditch",
	    "west ditch", "northeast ditch", "northwest ditch",
	    "southeast ditch", "southwest ditch" }),
	    BSN("The ditch is at least three feet deep. It completely "+
		"encloses the field."));
    	break; /* case "field" */
   
   case "track":
	Areadesc = "There does not seem to be much traffic on the track.";
	try_item(({ "path", "road", "ground", "grassy track",
	   "narrow track", "track" }),
	    BSN("The narrow track does not seem to get much use; "+
		"ankle-high grass grows largely undisturbed."));
	try_item(({ "field", "fields" }),
	    BSN("The fields, which appear to be sown with some kind of "+
		"crop, are enclosed by good-sized ditches."));
	try_item(({ "crop", "crops", "plant", "plants" }),
	    BSN("The crops appear to be healthy, but you cannot "+
		"see details from here."));

	/* from tracks, give 'em a hint re entering fields */
	if ((s = sizeof(Trackdir)))
	{
	    try_item(({ "deep ditches", "deep ditch",
	        "dry ditches", "dry ditch", "ditches", "ditch" }),
	        BSN("The ditches that separate the fields from "+
		    "each other and from the track are fairly deep, "+
		    "but probably could be crossed with moderate effort."));
	    while (s-- > 0)
	    {
		try_item( Trackdir[s]+" ditch",
	            BSN("The "+Trackdir[s]+" ditch is fairly deep, but "+
		        "probably could be crossed with moderate effort."));
	    }
	}

	if (try_item( "grass",
	    BSN("The narrow track does not seem to get much use; "+
	    "ankle-high grass grows largely undisturbed.")))
	{
	    /* this is lame, but i'm stumped */
	    Getnames = ({ "grass" });
	    Getmsg = "You pick some grass, but it's nothing "+
		"unusual; you throw it away.";
	}

	break;	/* case "track" */

   case "pasture":
	if ((s = sizeof(Ditchdir)))
	{
	    Areadesc = "A mixture of grasses, dotted with wildflowers, "+
		"covers the pasture, and a deep ditch runs along its "+
		Ditchdir[0]+" edge.";
	    try_item(({ "deep ditches", "deep ditch",
	    	"dry ditches", "dry ditch", "ditches", "ditch" }),
		BSN("The ditch is perhaps three feet deep."));
	    while (s-- > 0)
	    {
		try_item(Ditchdir[s]+" ditch", 
		    BSN("A fairly deep ditch runs along the "+Ditchdir[0]+
		        " edge of the pasture."));
	    }
	}
	else
	{
	    Areadesc = "A mixture of grasses, dotted with wildflowers, "+
		"covers the pasture.";
	}

	/* not "field" -- reserve that for cultivated fields */
	try_item(({ "pasture", "meadow" }),
	    BSN("The pasture is thickly covered with various "+
		"grasses."));
	try_item(({ "grass", "grasses", "plant", "plants", "ground" }),
	    BSN("A mixture of grasses ... some tall and sharp-edged, "+
		"others compact and broad-bladed ... grow thickly. "+
		"Wildflowers add a sprinkling of bright colours."));
	if (try_item(({ "flower", "flowers", "wildflower", "wildflowers" }),
	    BSN("Colourful wildflowers are scattered over the pasture.")))
	{
	    /* this is lame, but i'm stumped */
	    Getnames = ({ "flower", "flowers", "wildflower",
		"wildflowers" });
	    Getmsg = "You admire the wildflowers, but decide "+
		"to let them grow undisturbed.";
	}
	break;	/* case "pasture" */

    } /* switch(Areatype) */
} /* set_areadesc0 */


/*
 * Function name:	set_areadesc1
 * Description	:	set default area & items using set 1
 */
static void
set_areadesc1()
{
    int s;
    switch (Areatype)
    {

    case "field":
	Areadesc = "The field is circled on all sides by a fairly "+
		   "deep ditch, and appears to be sown with "+Areacrop+".";
	if (sizeof(Trackdir))
	{
	    Areadesc += " A grassy track parallels the "+
		Trackdir[0]+" edge "+ "of the field, beyond the ditch.";
	    try_item(({ Trackdir[0]+" ditch", "narrow track",
		"track", "path", "road" }),
		BSN("Beyond the ditch on the "+Trackdir[0]+
		    " edge of the field runs a narrow track."));
	    /* we ignore diagonal ditch items for now. if anyone ever
	     * files a complaint, we'll add 'em.
	     */
	}
	try_item(({ "field", "fields" }),
	    BSN("A thriving crop of "+Areacrop+" covers the field, "+
		"which is enclosed by fairly deep ditches."));
	try_item(({ "soil", "dirt", "loam", "ground" }),
	    BSN("The soil is a rich brown loam."));
	try_item(({ "deep ditches", "deep ditch",
	    "dry ditches", "dry ditch", "ditches", "ditch" }),
	    BSN("A dry ditch, probably three feet deep, runs around "+
		"the entire field."));
	/* plus directions */
	try_item(({ "north ditch", "south ditch", "east ditch",
	    "west ditch", "northeast ditch", "northwest ditch",
	    "southeast ditch", "southwest ditch" }),
	    BSN("A dry ditch, probably three feet deep, runs around "+
		"the entire field."));
    	break; /* case "field" */
   
   case "track":
	Areadesc = "The narrow track does not seem to get much use.";
	try_item(({ "path", "road", "ground", "narrow track",
	    "grassy track", "narrow track", "track" }),
	    BSN("The grassy track shows few signs of traffic."));
    	add_item( ({ "signs", "signs of traffic" }),
	    BSN("It would seem that few travel this way."));
	try_item(({ "field", "fields" }),
	    BSN("The fields are ringed by fairly deep ditches "+
		"and covered by green plants."));
	try_item(({ "crop", "crops", "plant", "plants" }),
	    BSN("You cannot see the plants very well from here."));

	/* from tracks, give 'em a hint re entering fields */
	if ((s = sizeof(Trackdir)))
	{
	    try_item(({ "deep ditches", "deep ditch",
	        "dry ditches", "dry ditch", "ditches", "ditch" }),
	        BSN("The ditches enclosing the fields are perhaps three "+
		    "feet deep. They probably could be crossed with "+
		    "moderate effort."));
	    while (s-- > 0)
	    {
		try_item( Trackdir[s]+" ditch",
	            BSN("The "+Trackdir[s]+" ditch is perhaps three "+
		        "feet deep. It probably could be crossed with "+
		        "moderate effort."));
	    }
 	}

	if (try_item( "grass",
	    BSN("The grassy track shows few signs of traffic.")))
	{
	    /* this is lame, but i'm stumped */
	    Getnames = ({ "grass" });
	    Getmsg = "You pick a stalk of grass, but it's not "+
		"very interesting; you throw it away.";
	}
	break;	/* case "track" */

   case "pasture":
	if ((s = sizeof(Ditchdir)))
	{
	    Areadesc = "The pasture is thickly covered with various "+
		       "grasses, and bordered by a ditch to the "+
		       Ditchdir[0]+".";
	    try_item(({ "deep ditches", "deep ditch",
	    	"dry ditches", "dry ditch", "ditches", "ditch" }),
		BSN("A fairly deep ditch runs along the "+Ditchdir[0]+
		    " edge of the pasture."));
	    while (s-- > 0)
	    {
		try_item(Ditchdir[s]+" ditch", 
		    BSN("A fairly deep ditch runs along the "+Ditchdir[0]+
		        " edge of the pasture."));
	    }
	}
	else
	    Areadesc = "The pasture is thickly covered with various "+
		       "grasses.";

	/* not "field" -- reserve that for cultivated fields */
	try_item(({ "pasture", "meadow" }),
	    BSN("A mixture of grasses, dotted with wildflowers, "+
		"covers the pasture."));
	try_item(({ "grass", "grasses", "plant", "plants", "ground" }),
	    BSN("Grasses of varying heights, sprinkled with "+
		"colourful wildflowers, carpet the pasture."));
	if (try_item(({ "flower", "flowers", "wildflower", "wildflowers" }),
	    BSN("Bright wildflowers add a sprinkling of colour "+
		"to the pasture.")))
	{
	    /* this is lame, but i'm stumped */
	    Getnames = ({ "flower", "flowers", "wildflower",
		"wildflowers" });
	    Getmsg = "You admire the wildflowers, but decide "+
		"to let them grow undisturbed.";
	}
	break;	/* case "pasture" */

    } /* switch(Areatype) */
} /* set_areadesc1 */


/*
 * Function name:	ditch_msg
 * Description  :	write a nice you-cross-the-ditch msg
 * Returns      :	0 (exit is possible)
 */
public int
ditch_msg()
{
    switch(random(3))
    {
    case 0:
	write("You leap the ditch to the "+QVB+".\n");
	break;
    case 1:
	write("You cross the "+QVB+" ditch.\n");
	break;
    case 2:
	write("You jump across the ditch.\n");
	break;
    }
    return 0;
} /* ditch_msg */


/*
 * Function name:	check_lightlevel
 * Description  :	determine lightlevel based on time of day
 * Returns	:	light level (always positive)
 *
 * copied from /d/Gondor/common/lib/area_room.c
 */
public int
check_lightlevel()
{
    switch (tod())
    {
    case "night":
        return 1;
    case "early morning":
    case "evening":
        return 2;
    case "morning":
    case "noon":
    case "afternoon":
        return 3;
    default:
        return 1;
    }
} /* check_lightlevel */



/*
 * Function name:	long_desc
 * Description  :	create time-dependent long desc for room
 * Returns      :	the description
 *
 * swiped from /d/Gondor/common/lib/area_room.c and changed to
 * handle items as well as room long.
 *
 * if Exa_arg is set, then the player did "exa sun/sky/stars/moon ...".
 * if Exa_arg is not set, then the player did "look".
 *
 * initialize the description string accordingly (null if the former,
 * room description if the latter), then append the appropriate
 * time-of-day information.
 *
 * if player did "look", return desc.
 * if examined something, write the desc and return empty string;
 *
 */
public string
long_desc()
{
    string	timestr = tod(),
		moon,
		desc;
    object	clock;

    /* check whether we need to set moon; catch error cases for examine */
    if (timestr == "night")
    {
	if (Exa_arg == "sun")
	{
	    return BSN("The sun is not visible at night.");
	}
	if (objectp(clock = find_object(CLOCK)))
	{
	    moon = clock->query_moon();
	}
    }
    else /* timestr is not night */
    {
	if (Exa_arg == "moon")
	{
	    return BSN("The moon is not visible during the day.");
	}
	if (Exa_arg == "star" ||
	    Exa_arg == "stars")
	{
	    return BSN("The stars are not visible during the day.");
	}
    }


    /* initialize desc differently, according to whether we were
     * called as a result of "look" or of "exa sun/sky/moon/..."
     */
    if (!strlen(Exa_arg))
    {
	/* player did "look" */
    	desc = capitalize(query_short())+". ";
    	if (strlen(Extraline))
	{
            desc += Extraline+" ";
	}
    	else
	{
	    desc += Areadesc+" ";
	}
	if (!strlen(timestr))
	{
	    return BSN(desc);
	}
    }
    else
    {
	/* player did "exa sky/sun/stars/..." */
	if (!strlen(timestr))
	{
	    write(BSN("Clouds obscure the sky."));
	    return "";
	}
	desc = "";
    }


    /* now append the tod info */
    if (timestr == "night" &&
        (!Exa_arg ||
	 Exa_arg == "sky" ||
         Exa_arg == "star" ||
	 Exa_arg == "stars"))
    {
        desc += "A sprinkling of Elbereth's stars can be seen " +
		"twinkling high above Middle-Earth. It is night in " +
		Areaname + ". ";
    } 	/* timestr == "night" and should see the stars */
 

    if (timestr == "night" &&
        (!Exa_arg ||
	 Exa_arg == "sky" ||
	 Exa_arg == "moon"))
    {
        switch(moon)
        {
        case "full":
            desc += "The full moon, fair Ithil, bathes the " +
		    Areatype + " in liquid silver light."; 
            break;
        case "waxing crescent":
            desc += "The crescent moon illuminates the " + 
		   Areatype + " faintly.";
            break;
        case "waxing gibbous":
	    desc += "The moon, now approaching full, casts " +
		    "a silvery light."; 
	    break;
        case "waning gibbous":
	    desc += "The moon, now past full, still casts a " +
		    "serviceable white light."; 
	    break;
        case "waning crescent":
            desc += "The moon tilts its slender upturned " +
		    "horns over the gloomy landscape."; 
            break;
        default:
	    /* only add this msg if exa'd moon. it'd look silly to
	     * add this to desc when we've already talked about the stars
	     */
	    if (Exa_arg == "moon")
	    {
	        desc += "The sky is obscured by dark clouds.";
	    }
            break;
        }
    }	/* if timestr == "night" and should see the moon */


    /* ok, it's daytime ... */
    if (timestr != "night" &&
        (!Exa_arg ||
	 Exa_arg == "sky" ||
	 Exa_arg == "sun"))
    {
	switch(timestr)
	{
        case "afternoon":
            desc += "Daylight shines across " + Areaname + "."+
                " It is afternoon.";
            break;
    	case "morning":
        	desc += "The sun is on its way up in the morning sky "
           	     + "to the east.";
            break;
        case "noon":
            desc += "The sun is almost at its peak on its way across "
                 + "the sky. It is noon in " + Areaname + ".";
            break;
        case "evening":
            desc += "The sun is setting in the west, colouring the sky "
                 + "golden red.";
            break;
        case "early morning":
            desc += "The sun is rising in the east, casting long shadows "
                 + "across "+Areaname+".";
	    break;
	default:
	    /* actually, looking at the clock code, it appears this
	     * default case is unnecessary -- tod() defaults to "night".
	     * however, that could change behind my back, so ...
	     */
	    desc += "The sky is obscured by dark clouds.";
	    break;
	}
    }	/* it's daytime */

    if (Exa_arg)
    {
	/* player examine'd something ... write the desc */
	if (desc == "")
	{
	    desc = "Clouds obscure the sky.";
	}
	write(BSN(desc));
	return "";
    }
    /* else player did "look" ... return the desc */
    return BSN(desc);
} /* long_desc */


/*
 * Function name:	climb
 * Description	:	let players climb the door/gate
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 if not
 *
 * originally was doing this only in farm1/pigsty as part of quest (see
 * comments there), but it occurred to me that if i could climb
 * a gate in one part of the farm, then i should be able to climb
 * gates in other parts of the farm, too.
 */
public int
climb(string arg)
{
    mixed	doornames;
    object	door;

    if (objectp(door = present(SIRITH_DOOR)))
    {
	doornames = door->query_door_name();
	if ((stringp(doornames) &&
	     arg == doornames) ||
	    (pointerp(doornames) &&
	     member_array(arg, doornames) >= 0))
	{
	    if (!door->query_open())
	    {
		set_dircmd(arg);
		write(BSN("You scramble over the "+arg+"."));
		TP->move_living("over the "+arg+"", Climbdest);
	    }
	    else
	    {
		write(BSN("Climbing an open "+arg+" is pointless."));
	    }
	    return 1;
	}
    }
    NFN0("Climb what?");
} /* climb */


/*
 * Function name:	pick_crop
 * Description	:	handle attempts to get/pick/take crop in fields
 *			or wildflowers in pastures
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if arg was crop/wildflower, 0 if not
 *
 * Cannot do this via add_cmd_item() because that prevents
 * getting a flower if one is lying in the room. :-(
 */
public int
pick_crop(string arg)
{
    if (!strlen(arg) ||
	objectp(present(arg, TO)) ||
        member_array(arg, Getnames) < 0)
    {
	return 0;
    }
    write(BSN(Getmsg));
    return 1;
} /* pick_crop */


/*
 * Function name:	cross_ditch
 * Description	:	move the player when s/he leaps/jumps/crosses
 *			the ditch
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand arg, 0 if not
 *
 * N.B. cannot use notify_fail in most of the error msgs here
 * because the soul's "cross" and "jump" will override it.
 */
public int
cross_ditch(string arg)
{
    string	direction,
		tmpstr,
		*ddirs = ({ }),		/* directions of ditches */
    		*nondiags = ({ });	/* non-diagonal ...	 */
    object	tp = TP;
    int		n;

    if (!strlen(arg))
    {
	NF0(capitalize(QVB)+" what?\n");
    }

    /* looking for:
     *		cross/leap/jump [across] [direction] ditch
     * if there's a ditch in more than one direction, user
     * must be specific.
     *
     * ("cross across" sounds silly, but it's not worth
     * pulling out as a special case)
     */

    if (arg == "ditches" || arg == "across ditches")
    {
	write("You can only cross one ditch at a time.\n");
	return 1;
    }

    ddirs = (Areatype == "pasture" ? Ditchdir : Trackdir);
    if (arg == "ditch" ||
	arg == "across ditch")
    {
	/* they didn't specify direction -- if there's more than one
	 * ditch (or no ditch), fail. check n/s/e/w directions first;
	 * if there are none of those, then check diagonals.
	 */
	if (Areatype == "field")
	{
	    /* fields have ditches on all sides */
	    write(capitalize(QVB)+" which ditch?\n");
	    return 1;
	}

	nondiags = ddirs - ({ "northeast", "southeast",
	    "northwest", "southwest" });
	if ((n = sizeof(nondiags)) > 1)
	{
	    write(capitalize(QVB)+" which ditch?\n");
	    return 1;
	}
	else if (n == 1)
	{
	    direction = nondiags[0];
	}
	else if ((n = sizeof(ddirs)) > 1)
	{
	    write(capitalize(QVB)+" which ditch?\n");
	    return 1;
	}
	else if (n == 1)
	{
	    direction = ddirs[0];
	}
	else
	{
	    write(capitalize(QVB)+" what?\n");
	    return 1;
	}
    }
    else if (!sscanf(arg, "across %s ditch", tmpstr) &&
             !sscanf(arg, "%s ditch", tmpstr))
    {
	/* nope, no direction ... fall on sword */
	if (sscanf(arg, "%s ditches", direction))
	{
	    write("You can only cross one ditch at a time.\n");
	}
	else
	{
	    write(capitalize(QVB)+" what?\n");
	}
	return 1;
    }
    else
    {
	/* is the user-specified dir in tmpstr any good? */
	if (Areatype != "field" &&
	    (!sizeof(ddirs) ||
	     member_array(tmpstr, ddirs) < 0))
	{
	    write("There is no "+tmpstr+" ditch to cross.\n");
	    return 1;
	}
	direction = tmpstr;
    }

    if (QVB == "enter")
    {
	WRITE( ({
	    "You scramble into the "+direction+
		" ditch for a moment, but find nothing of interest "+
		"and hop back out.",
	    "You jump down into the "+direction+" ditch, then climb out.",
	    "You briefly enter the "+direction+
		" ditch, but find nothing to hold your attention. "+
		"You jump out again.",
	    })[random(3)] );
	/* just do one SAY msg. otherwise, i'll need to handle 
	 * "scramble" and "jump down into" vs "jump across", and so on.
	 */
	SAY(" briefly enters the "+direction+
	    " ditch, then jumps out again.");
	    
    }
    else if (!tp->query_wiz_level())
    {
	tp->command(direction);
    }
    else
    {
	/* inconvenient for wizards, but i don't feel like
	 * doing all the move-and-fatigue stuff myself
	 */
	write("Ordinarily, this room would do\n"+
              "   this_player()->command(\""+direction+"\");\n"+
              "Since you're a wizard, that won't work.\n"+
              "Please do the command yourself.\n");
    }
    return 1;
} /* cross_ditch */
