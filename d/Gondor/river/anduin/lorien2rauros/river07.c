/*
 * /d/Gondor/river/anduin/lorien2rauros/river07.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~130 miles south of the silverlode, between day 3 and 
 * day 4 campsites.
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
public string	scenery_msgs(object ob, string vb, string dir);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("~130 miles downstream from the silverlode, between day 3 and "+
	    "day 4 campsites."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River flows from north to southwest through "
      + "a treeless land. On the river's west border, forests of "
      + "great reeds pass by, often shutting out all view to the west.");
    set_tod_landname("the Brown Lands");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("southwest");
    set_upstreamdir("north");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river06", "north");
    set_distance("north", 25);
    add_exit("river08", "southwest");
    set_distance("southwest", 30);
    add_exit("riverbottom07", "down");
    /* no shore rooms for now */


    /* thanks to gorboth for help with the items :-) */
    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin flows in a smooth curve from north "
	  + "to southwest. Its waters are deep.") );
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	"The eastern shore is bleak and empty.\n");
    add_item( ({ "border", "borders", "western bank", "west bank",
	"western shore", "west shore" }),
        BSN("The fluttering borders of the western shore of the river "
	  + "drift slowly by. Forests of great reeds grow in dense "
	  + "patches along their edge.") );
    add_item( ({ "forests", "great reeds", "forests of great reeds", "patch",
	"patches", "reeds" }),
        BSN("The withered plumes of the reeds bend and toss in "
	  + "the light cold airs, hissing softly and sadly. Here and "
	  + "there through openings, you catch sudden glimpses of "
	  + "rolling meads.") );
    add_item( ({ "rolling meads", "meads", "wide plains", "plains",
	"grass" }),
        BSN("The land upon the west is in many places green with wide "
	  + "plains of grass and rolling meads. Far beyond, hills are "
	  + "visible against the sky, and beyond them on the edge of "
	  + "sight, a dark line.") );
    add_item( ({ "dark line", "line", "ranks",  "misty mountains",
	"mountains" }),
        BSN("In the distance the southernmost ranks of the Misty "
          + "Mountains march as a dark line on the edge of sight.") );
    add_item( ({ "foothills", "foothill",  "hills", "hill" }), 
	"Beyond the meads rise low foothills.\n");
    add_item( ({ "brown lands", "banks", "river bank", "river banks",
   	"bank", "land", "shore", "shores" }), 
	BSN("The land is bleak and treeless. Forests of great reeds "
	  + "block the view west.") );

} /* create_anduin_onwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people or boats are going upstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- "swim", "wade", "row", "dive", "wash"
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "north" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, "+
	           "the Anduin bends to the northwest.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
