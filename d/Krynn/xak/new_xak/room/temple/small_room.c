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
    set_short("In a small room");
    set_long("@@my_long@@");

    add_exit(TEMPLE + "chamber2", "west");
    
    gDoor = clone_object(OBJ + "d_small_room");
    gDoor->move(TO);
}

public string
my_long()
{
    return "You are standing in a small room east of the main chamber. " +
           "What this room was originally ment to be used for, is beyond " +
	   "you. On the east wall is " + ADOOR(gDoor) + " golden double " +
	   "door.\n";
}








