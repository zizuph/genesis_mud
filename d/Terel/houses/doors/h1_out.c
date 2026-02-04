/*
 * Calathin Townhouse 1 Door
 * h1_out.c
 *
 * Lilith, Mar 2022
 *
 */
#pragma strict_types
#pragma save_binary 

inherit "/d/Genesis/houses/house_door";

#include "../calathin1/h1.h"
#include <options.h>

#define EXIT    "north"

public void
create_door()
{
    set_door_id(DOOR_ID);
	set_key(HOUSE_NAME);
    set_pass_command(EXIT);
    set_house_name(HOUSE_NAME);
	
	set_other_room(H1 +"living");
    set_door_name( ({"red door", "door", "sturdy door",
        "red door", "wooden door", "holly berry red door"}) );
    set_door_desc("This sturdy door is painted beautiful "+
        "holly-berry red color. It appears to be the entrance "+
        "into a wealthy person's townhouse. If you " +
        "don't have a key, perhaps you could knock and " +
        "see if the owner is home?\n");
    set_fail_pass("A member of the Calathin guard steps up "+
        "and denies you entry.\n"+
        "You are guided back out onto the front stoop.\n");
    set_lock_command("lock");
    set_lock_name(({"lock", "iron lock", "wrought iron lock", 
	    "door lock", "house lock"}));
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_knock_command("knock");
    set_no_pick();
    set_no_show_composite(1);
}


int pass_door(string arg) {
    if (this_player()->query_option(OPT_BLOCK_INTIMATE)
         && !this_player()->query_wiz_level())
    {
        write("You decide against entering into the house.\n");
        return 1;
    }
    return ::pass_door(arg);
}

