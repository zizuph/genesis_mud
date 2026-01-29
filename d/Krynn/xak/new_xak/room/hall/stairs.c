/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("Below the Paths of the dead");
    set_long("You have entered a small square chamber in the centre " +
	     "of which is a spiral staircase that leads up to the " +
	     "temple complex above. The stairway is aptly known as " +
	     "the Paths of the dead. A pedestal rises up the centre " +
	     "of the staircase. There is an oder of dankness and decay " +
	     "in the air, which seems to come from east where you spot " +
	     "an imense hall.\n");

    add_exit(TEMPLE + "paths_dead", "up", "@@up");
    add_exit(HALL + "entry", "east");

    add_item("pedestal", "A simple stone column rising through the " +
             "centre of the stairway.\n");
}

public int
up()
{
    write("You climb up the dark stairway.\n");
    return 0;
}
