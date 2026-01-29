/*
 * Author     : Nuf
 * File       : /d/Genesis/start/human/sparkle/docks/ware1_1a.c
 * Description: Base floor storeroom in warehouse 1. Contains 
 *              some searchable crates and a cellar/basement. 
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
public string do_search(object tp, string arg);

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
        /* Should NOT happen */
        default: 
            write("You try in vain to move in that direction, but find it impossible.\n");
            return 1;
    }
    tell_room(ENV(TP), QCNAME(TP) + " takes a stroll off to the " +
                       dir + " corner.\n", TP);
    write("You walk to the " + dir + " corner and lurk around.\n");
    return 1;
}

/* Function : do_search
 * Arguments: object tp - the object performing the search
 *            string arg - the argument passed with the search
 * Returns  : string with the description of the search event.
 * Purpose  : perform special searches
 */
public string
do_search(object tp, string arg)
{
    string msg, saymsg;
    object ob;

    arg = lower_case(arg);
    
    if ( parse_command(arg, ({}), "[the] 'northwest' / 'nw' 'crate'") )
    {   
	msg = "finding something.\n";
	saymsg = "finding something.\n";
    }
    else
    {
        return "";
    }
    say(saymsg);
    return msg;
}

void
create_room()
{
    object door, key;

    set_short("A storeroom on the ground floor");
    set_long("A storeroom on the ground floor.\n"+
             "Large crates are piled up in here. Some of them have"+
             "gathered some dust, and some of them seem to have been"+
             "placed there recently. Supporting beams goes from the roof"+
             "down to the floor. To the east and south there are connections "+
             "to the rest of the warehouse. A small door is to the west.\n");

    add_item(({"beam", "beams"}), "The wooden beams are supporting the roof. They "+
                                  "go from the roof to the ground and from each "+
                                  "beam stretches a diagonal beam also up to the roof.\n");
    add_item(({"crates"}), "You see crates in stacked in the four corners "+
                           "of the room.\n");
    add_item(({"corners"}), "There are four corners, southwest, southeast, "+
                            "northwest and northeast.\n");
    add_item(({"corner"}), "Which corner?\n");
    add_item(({"sw corner", "southwest corner", "ne corner", "northeast corner",
               "se corner", "southeast corner"}), "The corner has a few heavy crates, "+
               "with smaller ones stashed upon.\n");
    add_item(({"sw crate", "southwest crate", "ne crate", "northeast crate", "se crate",
               "southeast crate"}), "The crate has circle with three dots burnt into "+
               "the side.\n");     
    add_item(({"nw corner", "northwest corner"}), "The corner has heavy crates piled "+
               "upon eachother. One of the crates has a strange mark on it.\n");
    add_item(({"nw crate", "northwest crate"}), "The crate has heavy crates piled upon "+
               "eachother. One of the crates has a circle with four dots burnt into the "+
               "side.\n");

    /* Exits */
    add_exit("", "northwest", &nowalk(WALK_NW), 0, 1);
    add_exit("", "northeast", &nowalk(WALK_NE), 0, 1);
    add_exit("", "southeast", &nowalk(WALK_SE), 0, 1);
    add_exit("", "southwest", &nowalk(WALK_SW), 0, 1);

    add_exit("/d/Genesis/start/human/sparkle/docks/" + "ware1_1b.c", "north");
    add_exit("/d/Genesis/start/human/sparkle/docks/" + "ware1_1c.c", "west");

    /* Doors */
    door = clone_object("/d/Genesis/start/human/sparkle/docks/doors/" + "w1_pier15_out");
    door->move(this_object());


    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(OBJ_I_SEARCH_TIME, 5); 
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

public void 
init()
{
    ::init();
}
