/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

object gDoor;

public void
create_xak_room()
{    
    set_short("In a circular room");
    set_long("@@my_long@@");

    add_exit(TEMPLE + "paths_dead", "down", "@@down");
    add_item("pedestal", "A simple stone column rising through the" +
             " centre of the stairway.\n");
    
    gDoor = clone_object(OBJ + "d_stairs");
    gDoor->move(TO);
}

public string
my_long()
{
    return "You have entered a circular dome. The room is bare except " +
           "for a high, broken pedestal in the midst of a " +
	   "spiraling stair, aptly known as the 'Paths of the dead'. " +
           "On the west wall is a set of " + DOOR(gDoor) + " golden double " +
           "doors. The stair leads down to the crypts below.\n";
}

public int
down()
{
    write("You decend down the dark stairway.\n");
    return 0;
}








