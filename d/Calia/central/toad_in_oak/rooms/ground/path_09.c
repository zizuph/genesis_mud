/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_09.c
 *
 * A path on the western edge of TiO
 * 
 * HISTORY: 2003-05-11 Created by Kcirderf
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c";

#include <stdproperties.h>
#include "defs.h"

// FORWARD FUNCTION DEFINITIONS

int pond_drink(string command);

// FUNCTIONS

/* 
    Name        pond_drink
    Purpose     Respond if the player tries to drink from the pond
    Arguments   command typed by the player
    Returns     Integer indication success or failure
*/ 
int
pond_drink(string command)
{
    int success = 1; 

    if(parse_command(command, this_object(), 
        "[water] 'from' [the] 'pond'")) 
    {
        write("The water of the pond appears to be a little muddy. You " +
            "think the nearby stream would be better for drinking.\n"); 
    }
    else
    {
        success = 0;
    }

    return success; 
}

// ROOM DEFINITION

void
create_tio_ground_room()
{
    set_short("A path beneath a village in the trees."); 
    set_long("A small pond is fed by a sparkling stream that makes its way " +
        "through the forest near where you stand. The oaks that surround " + 
        "you are enormous, and you can see a village built into their " + 
        "branches far above. Green grass grows all around, filling the " + 
        "spaces between the pond, the trees, and a dense tangle of brush " + 
        "that lies to the west.\n"); 

    add_item(Grass_Words, grass_describe(({"north", "southeast"}))); 
    add_item(Pond_Words, "@@pond_describe@@"); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Thicket_Words, thicket_describe("west")); 
    add_item(Tree_Words, trees_describe(1, "east")); 
    add_item(Village_Words, village_describe()); 
    
    pond_tells();
    stream_tells();
    thicket_tells();        

    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_03", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10", "southeast"); 
}

void
init()
{
    ::init(); 

    add_action(pond_drink, "drink");
    add_action(stream_drink, "drink"); 
}

