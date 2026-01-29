/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom20.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 * 
 * Exists only to hold dropped items -- on surface, water
 * is too turbulent to permit diving.
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_underwater";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/underwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_underwater();
public int	unq_no_move(string str);


/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long("Underwater.\n"+
	BSN("The dark, rocky waters seem to flow from north to south."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "north", "northwest" }) );
    set_downstreamdir( ({ "south", "southwest" }) );
    set_currentstr( ({ 7, 7 }) ); /* rough */ 
    set_rock_density(ROCKY);
    add_exit("river20", "up");
} /* create_anduin_underwater */


/*
 * Function name:	unq_no_move
 * Description	:	mask parent to force 'em to surface
 * Arguments	:	string str -- command line arg
 * Returns	:	1 -- always
 */
public int
unq_no_move(string str)
{
    WRITE("You try to swim "+QVB+", but the churning waters "+
	"tumble you to the surface.");
    TP->move_living("up", LORIEN_TO_RAUROS_DIR+"river20");
    return 1;
}
