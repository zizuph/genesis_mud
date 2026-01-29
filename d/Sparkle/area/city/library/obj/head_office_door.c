/*
 * /w/petros/sparkle/library/obj/head_office_door.c
 *
 * Door to the Office of the Head Librarian (Outside)
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit "/std/door";

// Global Variables

// Prototypes
public void             init();
public void             create_door();
public string           office_door_description();


/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} // init

/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
void
create_door()
{
    ::create_door();
    add_name( ({ "_head_office_door_out" }) );
    set_door_name( ({ "door", "office door" }) );
    set_door_desc(&office_door_description());
    set_door_id("_head_office_door");
    set_other_room(LIBRARY_ROOM_DIR + "headoffice");
    set_open_desc("The office door to the south is open.\n");
    set_open_mess( ({ "opens the office door to the south.\n",
                      "The office door to the north swings open.\n" }) );
    set_closed_desc("The office door to the south is closed.\n");
    set_close_mess( ({ "closes the office door to the south.\n",
                       "The office door to the north swings shut.\n" }) );
    set_pass_command( ({ "south", "s" }) );
    
    set_open(0);
    set_locked(0);
}

/* 
 * Function name:       office_door_description
 * Description  :       Function to return the proper long description
 *                      for the door.
 * Arguments    :       none
 * Returns      :       string - door description
 */
public string
office_door_description()
{
    string description;
    
    description = "The door has the words \"Head Librarian\" written "
                + "across the middle of the door. ";

    if (query_open())
    {
        description += "The door is currently open.\n";
    }
    else
    {
        description += "The door is currently closed.\n";
    }
    
    return description;    
}

/* 
 * Function name:       do_open_door
 * Description  :       Adds an exit when someone opens the door
 * Arguments    :       mess - message for opening the door
 * Returns      :       void/nothing
 */
void
do_open_door(string mess)
{
    string waiting_room = LIBRARY_ROOM_DIR + "waiting_room";
    ::do_open_door(mess);
    
    if (query_open())
    {
        // door is currently open. we add the exit
        waiting_room->add_exit(LIBRARY_ROOM_DIR + "headoffice", 
                               "south", 0);
    }
}

/* 
 * Function name:       do_close_door
 * Description  :       Remove an exit when they close the door
 * Arguments    :       mess - message to close the door
 * Returns      :       void/nothing
 */
void
do_close_door(string mess)
{
    string waiting_room = LIBRARY_ROOM_DIR + "waiting_room";
    ::do_close_door(mess);
    
    if (!query_open())
    {
        // door is currently open. we add the exit
        waiting_room->remove_exit("south");
    }
}

