/*
 * /d/Gondor/lebennin/sirith/farms/pasture6.c	
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
public object	make_sheep(object *Sheep, object Ram);


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("pasture");

    add_exit("pasture4", "south", 0, 2, 1);
    add_exit("pasture5", "west", 0, 2, 1);
    add_exit("track9", "southwest", 0, 2, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"northwest" }),
	"You roam about the pasture.\n");

    /* force barn to load so sheep are moved here if is daytime */
    call_other(SIRITH_FARMS_DIR + "farm2/barn", "short");
} /* create_outdoors */


/*
 * Function name:	make_sheep
 * Description	:	call clone_npcs() so that sheep get moved here
 *			in daytime
 * Arguments	:	object *Sheep	array to hold sheep
 *			object Ram	and the ram
 * Returns	:	object Ram
 */
public object
make_sheep(object *Sheep, object Ram)
{
    clone_npcs(Sheep, (SIRITH_FARMS_DIR+"npc/sheep"), 4.0, 
	(SIRITH_FARMS_DIR + "fields/pasture"));
    Ram = clone_npc(Ram, (SIRITH_FARMS_DIR+"npc/ram"),
	(SIRITH_FARMS_DIR + "fields/pasture"));
    return Ram;
} /* make_sheep */
