/*
 * /d/Gondor/river/anduin/carrock2lorien/riverbottom05.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_underwater";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/underwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_underwater();
public void	enter_inv(object ob, object from);
public void	surface(object pl);
public int	block_swim_south();


/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long("Underwater.\n" +
	BSN("The dark waters seem to flow from north " +
	    "to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    /* no rocks */
    add_exit("river05", "up");
    add_exit("riverbottom04", "north");
    add_exit("riverbottom06", "south", block_swim_south);
    set_distance("north", 25); 
    set_distance("south", 25);

} /* create_anduin_underwater */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to force floating players to surface
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob) &&
	ob->query_prop(OBJ_I_WATER_MOVE) == WATER_MOVE_FLOAT)
    {
	set_alarm(5.0, 0.0, &surface(ob));
    }
} /* enter_inv */


/*
 * Function name:	surface
 * Description	:	force floating players to surface
 * Arguments	:	object pl -- the player
 */
public void
surface(object pl)
{
    object 	savetp;

    if (living(pl) &&
	ENV(pl) == TO)
    {
	savetp = TP;
	set_this_player(pl);
	write("The current churns violently, forcing you to the " +
	    "surface.\n");
	SAYBB(" leaves up.");
	pl->move_living("M", (CARROCK_TO_LORIEN_DIR + "river05"));
	SAYBB(" arrives.");
	set_this_player(savetp);
    }
} /* surface */


/*
 * Function name:	block_swim_south
 * Description	:	block attempts to swim south. we want them to have to
 *			use boats.
 * Returns	:	0 if exit is allowed, 1 if not
 */
public int
block_swim_south()
{
    string	vb = QVB;
    if (vb == "south" ||
	vb == "swim")
    {
	WRITE("You begin to swim south, but after a few moments " +
	    "in the deep chill waters, you give up and rise to " +
	    "the surface.");
	TP->move_living("up", (CARROCK_TO_LORIEN_DIR + "river05"));
	return 1;
    }
    return 0;
} /* block_swim_south */
