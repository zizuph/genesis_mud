/*
 * Gate #1 - Outside
 *
 * This is the gate that is at the end of Tunnel #1. 
 *
 * Created by Petros, April 2009
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines
#define OTHER_ROOM     (UNDERGROUND + "undergrnd04_11")

// Inheritance
inherit "/std/door";

// Global Variables

// Prototypes
public void             create_door();
public string           stone_gate_description();

/*
 * Function name: create_door
 * Description:   Sets default names and id
 */
void
create_door()
{
    ::create_door();
    add_name( ({ "_underground_tunnel_gate_outside" }) );
    set_door_name( ({ "gate", "stone gate" }) );
    set_door_desc(&stone_gate_description());
    set_door_id("_underground_tunnel_gate");
    set_other_room(OTHER_ROOM);
    set_open_desc("The stone gate to the east is open.\n");
    set_open_mess( ({ "opens the stone gate to the east.\n",
                      "The stone gate to the west swings open.\n" }) );
    set_closed_desc("The stone gate to the east is closed.\n");
    set_close_mess( ({ "closes the stone gate to the east.\n",
                       "The stone gate to the west swings shut.\n" }) );
    set_pass_command( ({ "east", "e" }) );
    set_lock_command("lock");
    set_unlock_command("unlock");

    set_lock_name("scorpion lock");
    set_lock_desc("A lock in the form of a scorpion indentation.");
    set_lock_mess( ({ "pulls the scorpion scarab from the indentation "
                    + "in the stone gate.\n",
                      "The stone gate seals completely flush with "
                    + "the wall.\n" }) );
    set_unlock_mess( ({ "presses the scorpion scarab into the indentation "
                      + "in the stone gate.\n",
                        "The stone gate makes a loud groaning noise as "
                      + "it becomes unsealed from the wall.\n" }) );
                      
    set_open(0);
    set_locked(1);
    set_key(GATE_ONE_KEY);
}

/* 
 * Function name:       stone_gate_description
 * Description  :       Function to return the proper long description
 *                      for the gate.
 * Arguments    :       none
 * Returns      :       string - gate description
 */
public string
stone_gate_description()
{
    string description;
    
    description = "The stone gate is barely visible under the dim "
        + "light. You can see an indentation in the middle of "
        + "the gate in the shape of a scorpion. ";

    if (query_open())
    {
        description += "The stone gate is currently open.\n";
    }
    else
    {
        description += "The stone gate is currently closed.\n";
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
    ::do_open_door(mess);
    
    if (query_open())
    {
        // door is currently open. we add the exit
        environment(this_object())->add_exit(OTHER_ROOM, "east", 0);
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
    ::do_close_door(mess);
    
    if (!query_open())
    {
        environment(this_object())->remove_exit("east");
    }
}

void
do_unlock_door(string mess)
{
    ::do_unlock_door(mess);
    
    if (environment(this_player()) == environment(this_object()))
    {
        write("The stone gate makes a loud groaning noise as "
            + "it becomes unsealed from the wall.\n");
    }
}
