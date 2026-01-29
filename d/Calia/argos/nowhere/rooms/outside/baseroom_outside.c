/*
    /d/Calia/argos/nowhere/rooms/inside/baseroom_outside.c
  
    This is the base room that will be inherited by all 
    "outside" rooms in Nowhere. That is rooms outside the 
    cliff, not necessarily rooms outside of any building.
    This will contain any functions and property settings 
    specific to these rooms.
  
    HISTORY: 2003-07-13 Created by Kcirderf
  
    Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h" 

inherit "/d/Calia/argos/nowhere/rooms/baseroom.c"; 

// GLOBAL VARIABLES

string* Cliff_Words = ({"cliff"}); 
string* House_Words = ({"house", "houses", "stone houses", "roofs"}); 
string* Road_Words = ({"road", "stone road", "stones", "cobblestones"}); 
string* Village_Words = ({"village"}); 

// FORWARD FUNCTION DEFINITIONS

string describe_cliff(); 
string describe_houses(); 
string describe_road(string* directions); 
string describe_village(); 

// FUNCTIONS

/*
    Name:       describe_cliff
    Purpose:    Describes the cliff that forms the eastern side of
                Nowhere. 
    Arguments:  None
    Returns:    The description
*/
string
describe_cliff() 
{
    return "A tall, gray, stone cliff on the side of a mountain " +
        "forms the eastern edge of this village.\n"; 
}

/*
    Name:       describe_houses
    Purpose:    Describes the houses of the village
    Arguments:  None
    Returns:    The description
*/
string
describe_houses() 
{
    return "The houses of this village appear to be well " + 
        "constructed, with walls of carefully fitted and mortared " + 
        "stone, and roofs of neat thatch. They all appear to be " + 
        "rather short, with walls about five feet tall.\n"; 
   
}

/*
    Name:       describe_road
    Purpose:    Describes the road through Nowhere. 
    Arguments:  None
    Returns:    The description
*/
string
describe_road(string* directions)
{
    string description; 
    int x; 

    description = "The road though here is made up of carefully " + 
        "fitted cobblestones. The gaps between stones are too " + 
        "small for any weeds to grow."; 

    /* Check that at least one direction was supplied */ 
    if( sizeof(directions) > 0)
    {
        description += " The road leads off to the "; 

        if( sizeof(directions) == 1)
        {
            /* Only one direction, so just add it. */ 
            description += directions[0]; 
        }
        else if (sizeof(directions) == 2)
        {
            /* Two directions need an and but no comma */ 
            description += directions[0] + " and " + directions[1]; 
        }
        else
        {
            /* More than two have to be listed */ 
            for (x = 0; x < (sizeof(directions) - 1); x++)
            {
                description += directions[x] + ", ";
            }
        
            description += "and " + directions[sizeof(directions) -1];
        }
        description += "."; 
    }

    description += "\n"; 

    return description; 
}

/*
    Name:       describe_village
    Purpose:    Describes the village in general
    Arguments:  None
    Returns:    The description
*/
string
describe_village() 
{
    return "It's hard to see the village well when you are " + 
        "standing inside of it. It appears to be a small village " +
        "of stone buildings at the base of a cliff.\n";
   
}

// ROOM DEFINITION

void 
create_nowhere_outside_room()
{
}

public nomask void
create_nowhere_room()
{
    set_short("A room outside of the cliff complex of Nowhere"); 
    set_long("A room outside of the cliff complex of Nowhere.\n"); 

    add_prop(ROOM_I_LIGHT, 3); 

    create_nowhere_outside_room();
}

