/*
 * /d/Gondor/river/anduin/lorien2rauros/portage7.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * near the south end of the portage trail
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	BOULDER		(LORIEN_TO_RAUROS_DIR+"boulder")
#define	MIN_CLIMB_SKILL	20
#define	CLIMB_FATIGUE	15
#define	FALL_DAMAGE	20

/* prototypes */
public void	create_gondor();
public void	init();
public string	exa_boulder();
public int	do_climb(string arg);

static object	Boulder;	/* the room */


/*
 * Function name:	create_gondor
 * Description	:	set up the trail
 */
public void
create_gondor()
{
    FIX_EUID;	/* because we may try to load BOULDER room */

    set_short("a narrow trail");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Weathered cliffs curve from north to southeast, and a "+
	"trail threads a narrow gap between the cliffs and "+
	"a massive boulder.");

    set_tod_landtype("trail");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage6", "north", 0, 5);
    add_exit("portage8", "southeast", 0, 5);

    set_no_exit_msg( ({ "northwest", "west", "southwest", "south", }),
	BSN("The cliffs are too steep to climb."));
    set_no_exit_msg( ({ "northeast", "east", }),
	BSN("The massive boulder looms overhead, blocking your movement."));

    add_item( ({ "emyn muil", }),
	BSN("The cliffs of the Emyn Muil are bare and scoured by wind."));
    add_item( ({ "path", "rocky trail", "trail", "land", }),
	BSN("The trail bends from north to southeast through a "+
	    "gap between cliff and boulder."));
    add_item( ({ "space", "narrow gap", "gap", }),
	BSN("The space between boulder and cliffs is fairly narrow."));
    add_item( ({ "huge boulder", "massive boulder",
	"boulder", "boulders", }),
	exa_boulder);
    add_item( ({ "ground", "small rock", "rock",
	"small rocks", "rocks", }),
	BSN("A few small rocks are scattered on the trail."));
    add_item( ({ "weathered cliff", "limestone cliff",
	"cliff", "weathered cliffs", "limestone cliffs", "cliffs", }),
	BSN("The limestone cliffs bend in a gentle curve from "+
	    "north to southeast."));
    add_item( ({ "weathered stone", "stone", "limestone", }),
	BSN("The limestone of the cliffs is weathered and worn."));

    add_cmd_item( ({ "huge boulder", "massive boulder",
	"boulder", "boulders", }),
	({ "shove", "push", "move", "roll", }),
	BSN("Pushing the massive boulder is utterly futile."));

} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add 'climb'
 */
public void
init()
{
    ::init();
    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:	exa_boulder
 * Description	:	describe boulder and occupants
 * Returns	:	string -- the description
 */
public string
exa_boulder()
{
    object	*on_boulder, *lying;
    string	desc1, desc2;

    if (!objectp(Boulder))
    {
    	BOULDER->short();
	Boulder = find_object(BOULDER);
    }
    on_boulder = FILTER_LIVE(all_inventory(Boulder));
    if (!TP->query_wiz_level())
    {
	/* assume that from this distance, cannot see hidden or invis ob */
	on_boulder = filter(filter(on_boulder,
	    &not() @ &->query_prop(OBJ_I_HIDE)),
	    &not() @ &->query_invis());
    }
    lying = filter(on_boulder, &->query_no_show_composite());
    on_boulder -= lying;

    switch (sizeof(on_boulder))
    {
    case 0:
	desc1 = "";
	break;
    case 1:
	desc1 = " "+on_boulder[0]->query_Art_name(TP)+
	    " is standing on the boulder";
	break;
    default:
	desc1 = " "+CAP(COMPOSITE_LIVE(on_boulder))+
	    " are standing on the boulder";
	break;
    }
    switch (sizeof(lying))
    {
    case 0:
	desc2 = "";
	break;
    case 1:
	desc2 = lying[0]->query_art_name(TP)+" is lying on the boulder.";
	break;
    default:
	lying->unset_no_show_composite();
	desc2 = COMPOSITE_LIVE(lying)+" are lying on the boulder.";
	lying->set_no_show_composite(1);
	break;
    }
    if (strlen(desc1))
    {
	if (strlen(desc2))
	{
	    desc1 += ", and "+desc2;
	}
	else
	{
	    desc1 += ". "+desc2;
	}
    }
    else if (strlen(desc2))
    {
	desc1 = " "+CAP(desc2);
    }
    return "The boulder is huge, and easily three times your height.\n"+
	BSN(desc1);
} /* exa_boulder */


/*
 * Function name:	do_climb
 * Description	:	handle attempts to climb boulder (or cliff)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_climb(string arg)
{
    object	tp,
		boulder;

    if (!arg)
    {
	NF0("Climb what?\n");
    }

    arg = LOW(arg);
    if (parse_command(arg, ({}),
	"[up] [the] [weathered] [limestone] 'cliff' / 'cliffs'"))
    {
	WRITE("The limestone crumbles away, and you slip back to the "+
	    "ground.");
	return 1;
    }
    if (!parse_command(arg, ({}),
	"[on] / [up] / [upon] [the] [huge] / [massive] 'boulder'"))
    {
	NF0("Climb what?\n");
    }

    tp = TP;
    if (!tp->query_wiz_level() &&
	(tp->query_skill(SS_CLIMB) < MIN_CLIMB_SKILL ||
	 tp->query_encumberance_weight() > 70))
    {
	WRITE("You try to climb the massive boulder, but fall "+
	    "heavily to the ground.");
	SAY(" tries to climb the boulder, but falls back to the "+
	    "ground.");
	tp->reduce_hit_point(FALL_DAMAGE);
	return 1;
    }

    BOULDER->short();
    boulder = find_object(BOULDER);
    if (!boulder->query_space(tp))
    {
	WRITE("You climb some distance up the boulder, but find there is "+
	    "no room for you on top. You drop back to the ground.");
	SAYBB(" climbs a short distance up the boulder, but "+
	    "then drops back to the ground.");
	return 1;
    }

    if (tp->query_fatigue() < CLIMB_FATIGUE)
    {
	write("You are too tired to climb the boulder.\n");
	return 1;
    }
    tp->add_fatigue(-CLIMB_FATIGUE);
    WRITE("You climb the massive boulder.");
    SAYBB(" climbs the massive boulder.");
    tp->move_living("M", BOULDER);
    SAYBB(" arrives.");
    return 1;
} /* do_climb */
