/*
 * dcamp6x3.c
 *
 * Draconian camp  -  06 x 03
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "local.h"

inherit CAMPBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int ascend_path();
public int descend_path();

object drac1, drac2, drac3;

#define DRAC  "/d/Krynn/std/sivak"
#define DRAC2 "/d/Krynn/std/bozak"

void
reset_kurinost_room()
{
     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move(TO, 1);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC2);
         drac2->set_color("green");
         drac2->move(TO, 1);
     }

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(RSLIVING + "sivak_leader");
         drac3->set_color("green");
         drac3->move(TO, 1);
     }
}

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    // Set up basic camp descriptions.
    generate_camp(DCAMP_BROKENPATH,
        "Standing near the middle of the camp, your eyes are " +
        "drawn to the central depression of the camp just below " +
        "you towards the west.");

    // Set up descriptions about the paved path.
    generate_path("northwest, down towards the northern entrance " +
        "to the camp and southwest, up towards the southern " +
        "entrance to the camp.");

    set_short("middle of a shady encampment near a rickety tavern");
    set_long(show_long_desc() + "A rickety tavern has been assembled " +
        "against the palisade here.\n");

    add_item(({"rickety tavern", "tavern"}), "A tavern has been crudely " +
        "assembled against the palisade here, giving the draconian and " +
        "hobgoblin forces something to do when off duty. You can enter " +
        "it through its door.\n");

    add_item(({"door"}), "A wooden door allows access to the tavern here. " +
        "You can enter it.\n");

    add_cmd_item(({"door", "through the door", "through door", "the door",
        "tavern", "rickety tavern"}), "enter","@@enter_tavern");

    add_exit(RSROOMS + "dcamp5x2", "northwest", descend_path, 3);
    add_exit(RSROOMS + "dcamp4x5", "southwest", ascend_path, 3);

    setup_tells();
    KURINOSTMAP;

    reset_kurinost_room();
}

string
enter_tavern()
{
    write("You push through the door and enter a dimly lit rickety tavern.\n");
    say(QCTNAME(this_player()) + " enters the rickety tavern.\n");

    tell_room(RSROOMS + "tavern", QCNAME(TP) + " enters the tavern.\n");
    TP->move_living("M", RSROOMS + "tavern",1,0);
    return "";
}


/*
 *  FUNCTION : ascend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you climb up the path. Show additional description
 *  of the path.
 *
 */
public int
ascend_path()
{
    write("Following the narrow path on a gentle upward slope, " +
        "you head southwest, up towards the southern entrance to " +
        "the camp.\n");

    return 0;
}


/*
 *  FUNCTION : descend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk down the path. Show additional description
 *  of the path.
 *
 */
public int
descend_path()
{
    write("Following the narrow path on a gentle downward slope, " +
        "you head northwest, down towards the southern entrance " +
        "to the camp.");

    return 0;
}

