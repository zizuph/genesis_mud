/*
 * /d/Gondor/lebennin/sirith/farms/track1.c	
 * track in farm community in southern Lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * puts a few rabbits in random field/track rooms.
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

#define	NFIELDS		9
#define	NTRACKS		9
#define	NRABBITS	6

static object	*Rabbits = allocate(NRABBITS);

public void	create_outdoors();
public void	reset_room();


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_noitems(1);
    set_areatype("track");
    set_extraline("The grassy track meanders between open fields.");

    add_exit("track2", "northwest", 0, 2);
    add_exit(LEB_DIR + "rroad/rr6", "south", 0, 2);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"southwest", "west" }),
	"You wander in the fallow fields, then return to the track.\n");

    add_item( ({ "fallow field", "fallow fields", "field", "fields" }),
	BSN("The fields appear to be lying fallow."));
    add_item( ({ "path", "road", "ground", "grass",
	"narrow track", "grassy track", "track" }),
	BSN("The narrow track does not seem to get much use; "+
	    "the grass shows only faint marks of traffic."));
    add_item( ({ "faint marks", "marks",
    	"faint marks of traffic", "marks of traffic" }),
	BSN("Evidently this track is rarely used."));
    set_getnames("grass");
    set_getmsg("You pick some grass, but it's nothing "+
	"unusual; you throw it away.");

    reset_room();
} /* create_outdoors */


/* put NRABBITS into random fields & tracks each reset */
public void
reset_room()
{
    int i, m, n;

    ::reset_room();

    for (i = 0, m = (NTRACKS + NFIELDS); i < NRABBITS; ++i)
    {
	if (objectp(Rabbits[i]))
	{
	    continue;	/* for */
	}
	/* not using clone_npc since am moving the rabbit elsewhere */
	if (objectp(Rabbits[i] = clone_object( NPC_DIR+"rabbit")))
	{
	    Rabbits[i]->set_restrain_path(LIVESTOCK_RESTRAIN);
	    if ((n = random(m)) < NFIELDS)
	    {
	    	Rabbits[i]->move(SIRITH_FARMS_DIR + "fields/field" + (n + 1));
	    }
	    else
	    {
	    	Rabbits[i]->move(SIRITH_FARMS_DIR + "fields/track" +
		    (n - NFIELDS + 1));
	    }
	}
    }
} /* reset_room */
