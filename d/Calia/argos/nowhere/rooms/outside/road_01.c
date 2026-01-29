/*
    /d/Calia/argos/nowhere/rooms/outside/road_01.c
   
    Part of the road in Nowhere, at the entrance of the 
    village. 
  
    HISTORY: 2003-07-13 Created by Kcirderf
  
    Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/d/Calia/argos/nowhere/rooms/outside/baseroom_outside.c";

// FUNCTIONS

/*
    Name:           hook_smelled
    Purpose:        Adds smells to certain items in the room.                 
    Arguments:      str typed by the player 
    Returns:        nothing
 */
void
hook_smelled(string smelled)
{

    if (member_array(smelled, ({"hut", "roof", 
        "doorway", "sign", "wooden sign", "lettering", "planks",
        "wood"})) >= 0) 
    {
        write("The wood of the hut and sign smells faintly of " + 
            "rot.\n");
    }
    else if (smelled == "fred")
    {
        write("YUCK!\n"); 
    }
    

}

// ROOM DEFINITION

void 
create_nowhere_outside_room()
{
    set_short( "A road through a small village."); 
    set_long("You stand on a stone road near the western edge of " +
        "a small village at the base of a large cliff. There are " +
        "a number of low stone houses around you, and a " +
        "dilapidated wooden hut just to the north. There is a " + 
        "wooden sign near the entrance to the hut.\n"); 

    add_exit( NOWHERE_ROOMS_OUTSIDE + "visitors", "north"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_02",  "northeast"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_07",  "east"); 

    add_item(({"hut", "wooden hut", "walls", "roof", "doorway"}),
        "It looks as if it were constructed in a hurry and then " +
        "ignored for several years. The walls and the roof are " + 
        "rotting wooden planks fastened together with rusted " + 
        "nails. Whatever door there was is gone, leaving a " + 
        "gaping opening with rusted hinges, and it looks as if " +
        "part of the roof has fallen in as well. There is a " + 
        "faded wooden sign next to the doorway.\n" ); 

    add_item(({"planks", "wood"}), 
        "The wooden planks that make up the hut are old, rotting, " + 
        "and in some cases broken.\n"); 
    
    add_item(({"nails"}), 
        "These old rusted nails are barely holding together the " + 
        "rotten wood of the hut.\n"); 

    add_item(({"hinges"}), 
        "These old hinges are so rusted it's not surprising the " + 
        "door is missing.\n"); 

    add_item(({"sign", "wooden sign", "lettering"}), 
        "The sign is nothing more than two pieces of wood nailed " +
        "together and shoved into the ground. The wood has " + 
        "turned grey and the lettering is so faded as to be " + 
        "almost unreadable. If you squint and look at it a bit " + 
        "sideways, it looks as if it might say:\n" +
        "     Visitor's Center\n"); 

    add_item(Cliff_Words, describe_cliff()); 
    add_item(House_Words, describe_houses()); 
    add_item(Road_Words, describe_road(({"northeast", 
        "east, curving southwards between two houses"}))); 
    add_item(Village_Words, describe_village()); 

    add_cmd_item(({"sign", "wooden sign", "lettering"}), ({"read"}), 
        "The sign is nothing more than two pieces of wood nailed " +
        "together and shoved into the ground. The wood has " + 
        "turned grey and the lettering is so faded as to be " + 
        "almost unreadable. If you squint and look at it a bit " + 
        "sideways, it looks as if it might say:\n" +
        "     Visitor's Center\n"); 
        
}

    
