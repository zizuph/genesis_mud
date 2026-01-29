/*
 * Author     : Nuf
 * File       : /d/Genesis/start/human/sparkle/docks/alley1a.c
 * Description: 
 */

#pragma save_binary
#pragma strict_types

#include "/d/Genesis/start/human/sparkle/defs.h"
#include "local.h"

inherit STD_ROOM;

#include <stdproperties.h> 	/* For standard properties */
#include <macros.h>    	/* For pre-defined macros */
#include <tasks.h>     	/* For difficulty and stat defines */
#include <ss_types.h>  	/* For skill defines */

/* Prototypes */

/* Defines */

/* Function : nowalk
 * Arguments: string arg - the argument passed with the search
 * Returns  : string with the description of the search event.
 * Purpose  : perform special searches
 */
public int
nowalk(string dir)
{
    switch (dir)
    {
        case WALK_NW: break;
        case WALK_NE: break;
        case WALK_SE: break;
        case WALK_SW: break;
        case WALK_DOWN: 
        /* Should NOT happen */
        default: 
            write("You try in vain to move in that direction, but find it impossible.\n");
            return 1;
    }
    return 1;
}

public void
create_room()
{
    object door, key;

    set_short("A storeroom on the ground floor");
    set_long("A storeroom on the ground floor.\n"+
             "Large crates are piled up in here. Some of them have "+
             "gathered some dust, and some of them seem to have been "+
             "placed there recently. Supporting beams goes from the roof "+
             "down to the floor. To the east and south there are connections "+
             "to the rest of the warehouse.\n");


    /* Exits */

    /* Doors */
    door = clone_object("/d/Genesis/start/human/sparkle/docks/doors/" + "w1_alley_in");
    door->move(this_object());

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
