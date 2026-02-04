/*
 * Calathin Townhouse 1 Door
 * h1_in.c
 *
 * Lilith, Mar 2022
 *
 */
 
#pragma strict_types
#pragma save_binary 

inherit "/std/door";

#include "../calathin1/h1.h"

#define EXIT    "south"

public void
create_door()
{
    set_door_id(DOOR_ID);
	set_key(HOUSE_NAME);
    set_pass_command(EXIT);

    set_other_room(JUNK_ROOM);
    set_door_name( ({"red door", "door", "sturdy door",
        "red door", "wooden door"}) );
    set_door_desc("This red door looks very sturdy. "+ 
        "It is the main entrance into the townhouse. "+
        "If you hear someone knocking you might examine "+
        "the window to see who is there. "+
        "There is a small sign on the door.\n"+
        "On the other side of the door is the west end "+
        "of Calathin town.\n");
    set_fail_pass("The door is securely locked.\n");
    set_lock_command("lock");
    set_lock_name(({"lock", "iron lock", "wrought iron lock", 
	    "door lock", "house lock"}));
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_knock_command("knock");

    set_no_pick();
}

