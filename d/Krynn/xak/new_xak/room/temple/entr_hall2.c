/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit INROOM;

object gDoor;

public void
create_xak_room()
{    
    set_short("In the entrance hall");
    set_long("@@my_long@@");
    
    add_exit(TEMPLE + "entr_hall1", "west");
    
    gDoor = clone_object(OBJ + "d_entr_hall2");
    gDoor->move(TO);
}

public string
my_long()
{
    return "You are standing in an arching entrance hall of the temple of " +
           "Mishakal. This is the eastern part of the hall. On the east " +
	   "wall is a set of " + DOOR(gDoor) + " golden double doors. " +
	   "The floor is made of finest marble and the wealth the " +
	   "city once had is apparent. The hall extends to the west from " +
	   "here.\n";
}








