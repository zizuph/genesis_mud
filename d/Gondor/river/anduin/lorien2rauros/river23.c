/*
 * /d/Gondor/river/anduin/lorien2rauros/river23.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * halfway between sarn gebir and the argonath
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_onwater();
public string	tod_descs();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("halfway between sarn gebir and the argonath, "+
	    "359 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Rocky cliffs overshadow the waters as they race south "+
	"under a narrow lane of sky.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );


    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("south");
    set_upstreamdir("north");
    set_currentstr(6);	/* rapid */
    set_depth(1524);	/* 50 feet */
    /* no rocks */

    add_exit("river22", "north");
    set_distance("north", 20);
    add_exit("river24", "south");
    set_distance("south", 20);
    add_exit("riverbottom23", "down");
    /* no shore rooms */

    add_item( ({ "narrow lane of sky", "narrow lane", "lane" }),
	tod_descs);
    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "deep water", "deep waters",
	"hurrying river", "river", }),
	BSN("The deep waters race south between sheer cliffs."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank", 
    	"east side", "east shore", "east bank", "western side",
	"western shore", "western bank", "west side", "west shore",
	"west bank", "shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("Sheer cliffs rise straight up from the water to "+
	    "overshadow the river."));
    add_item( ({ "ravine", "over-hanging cliff", "over-hanging cliffs",
	"rocky cliff", "rocky cliffs", "sheer cliff", "sheer cliffs",
	"cliff", "cliffs", }),
	BSN("The cliffs rise like high shadowy walls with their feet "+
	    "in the hurrying river."));
    add_item( ({ "high shadowy wall", "high wall", "shadowy wall",
	"high shadowy walls", "high walls", "shadowy walls", 
	"wall", "walls", }),
	BSN("The over-hanging cliffs all but block the sky."));
    add_item( ({ "base", "feet",  }),
	BSN("The cliffs plunge directly into the river, with "+
	    "no trace of a beach at their base."));
    add_item( ({ "steep gray stone", "steep stone", "gray stone", "stone" }),
	BSN("The cliffs are steep gray stone."));
    add_item( ({ "emyn muil" }),
	BSN("The cliffs of the Emyn Muil rise like walls above "+
	    "the river."));
} /* create_anduin_onwater */


/*
 * Function name:	tod_desc
 * Description  :	return time-dependent desc for room long
 *			or sky items (e.g., sun, moon, stars)
 *			mask parent to say a little more about "sky".
 * Returns      :	the description
 */
public string
tod_descs()
{
    string	desc,
		exad = TO->query_exa_arg();

    if (exad == "sky" ||
	exad == "lane" ||
	exad == "narrow lane" ||
	exad == "narrow lane of sky")
    {
	desc = BSN("The over-hanging cliffs shut out much of the sky. "+
	       "From the little you can see, it appears to be "+
	       tod()+" in the Emyn Muil.");
    }
    else
    {
	desc = ::tod_descs();
    }
    return desc;
} /* tod_descs */
