/*
 * /d/Gondor/lebennin/sirith/farms/pasture2.c	
 * field in farm community in southern Lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

public void	create_outdoors();
public object	make_cattle(object *Cows, object Bull);


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("pasture");

    add_exit("pasture3", "east", 0, 2, 1);
    add_exit("field7", "southeast", ditch_msg, 3, 1);
    add_exit("track7", "south", 0, 2, 1);
    add_exit("field6", "southwest", ditch_msg, 3, 1);
    add_exit("pasture1", "west", 0, 2, 1);

    set_no_exit_msg( ({ "north", "northeast", "northwest" }),
	"You wander about the pasture.\n");

    set_ditchdir( ({ "southeast", "southwest" }) );

    add_item( ({ "field", "fields", "ditch", "ditches" }),
	"Ditches enclose the fields to the southeast and southwest.\n");

    /* force barn to load so cattle are moved here if is daytime */
    call_other(SIRITH_FARMS_DIR + "farm1/barn2", "short");
} /* create_outdoors */

/*
 * Function name:	make_cattle
 * Description	:	call clone_npcs() so that cattle get moved here
 *			if it's daytime
 * Arguments	:	object *Cows	array to hold cows
 *			object Bull	and the bull
 */
public object
make_cattle(object *Cows, object Bull)
{
    clone_npcs(Cows, SIRITH_FARMS_DIR+"npc/cow", 4.0, 
	SIRITH_FARMS_DIR + "fields/pasture");
    Bull = clone_npc(Bull, SIRITH_FARMS_DIR+"npc/bull",
	SIRITH_FARMS_DIR + "fields/pasture");
    return Bull;
} /* make_cattle */
