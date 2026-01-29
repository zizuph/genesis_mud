/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("On the Paths of the dead");
    set_long("You are walking on a spiral stairway, known as the " +
	     "Paths of the dead. In the midst of the stairway is a " +
	     "pedestal.\n");

    add_exit(HALL + "stairs", "down", "@@down");
    add_exit(TEMPLE + "stairs", "up", "@@up");

    add_item("pedestal", "A simple stone column rising through the" +
             " centre of the stairway.\n");
}

public int
down()
{
    write("You decend down the dark stairway.\n");
    return 0;
}

public int
up()
{
    write("You climb up the dark stairway.\n");
    return 0;
}







