/*
 * dcamp2x3.c
 *
 * Draconian camp  -  02 x 03
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
public int enter_tower();
object drac1, drac2, drac3;

#define DRAC  "/d/Krynn/std/sivak"
#define DRAC2 "/d/Krynn/std/aurak"

void
reset_kurinost_room()
{

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(RSLIVING + "sivak_leader");
         drac3->set_color("green");
         drac3->move(TO, 1);
     }

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
        "Standing right in front of it, your eyes are " +
        "drawn to the decaying and partially collapsed slender tower " +
        "to your west.");

    // Set up descriptions about the paved path.
    generate_path("west, in to the tall slender tower and southeast, down " +
        "towards the southern entrance to the camp.");

    set_short("before a slender tower in a shady encampment");
    set_long("You stand before a slender tower of elven design that reaches " +
        "up out of the shadows towards the sky. While at a distance " +
        "the tower seemed pristine and white, up close the tower is " +
        "greyed from exposure to the elements and is partly " +
        "collapsed, the top of the tower lying as rubble at the base of " +
        "the tower. " +show_time_of_day());

    add_item(({"base", "rubble", "roof", "northern side"}),
        "Much of the roof and northern side of the tower has collapsed and " +
        "lies as rubble around the base of the tower. The entrance " +
        "is still accessible to your west.\n");
    add_item(({"entrance"}), "The entrance to the tower gapes open to your " +
        "west.\n");

    add_exit(RSROOMS + "dcamp4x5", "southeast", ascend_path, 3);

    add_cmd_item(({"tower", "slender tower", "broken tower"}), 
        "enter","@@enter_tower");

    setup_tells();
    KURINOSTMAP;

    reset_kurinost_room();
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
    write("You follow the narrow path southeast, down towards the " +
        "southern entrance to the camp.\n");

    return 0;
}

string
enter_tower()
{
    if((present(drac1, TO) && CAN_SEE(drac1, TP)) || 
       (present(drac2, TO) && CAN_SEE(drac2, TP)) || 
       (present(drac3, TO) && CAN_SEE(drac3, TP)))
    {
        if(present(drac1, TO))
            drac1->command("emote blocks the way into the broken tower.");
        if(present(drac2, TO))
        {
            drac2->command("scowl");
            drac2->command("say Enter on pains of death!");
        }
        if(present(drac3, TO))
            drac3->command("emote blocks your way towards the tower.");
        return "";
    }

    write("Carefully walking around the piles of rubble you make your " +
        "way into the broken tower.\n");
    say(QCTNAME(this_player()) + " enters the broken tower.\n");

    tell_room(RSROOMS + "dtower1", QCNAME(TP) + " enters the tower.\n");
    TP->move_living("M", RSROOMS + "dtower1",1,0);
    return "";
}

