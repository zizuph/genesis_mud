/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_03.c
 *
 * A path on the western edge of TiO, near the enterance to the village
 * 
 * HISTORY: 2003-05-10 Created by Kcirderf
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
    set_long("You stand next to a small pond formed by a stream as it " + 
        "flows between the enormous oak trees that make up this part " + 
        "of the forest. Grass covers the ground between the trees like " + 
        "a green carpet. A wooden bridge crosses the stream " + 
        "here, leading to the northeast, and a dense thicket prevents " + 
        "movement to the west. Above you in the brances of the trees " + 
        "you can see the underside of a small village.\n"); 
        
    add_item(({"bridge", "wooden bridge"}), 
        "The bridge forms a graceful arch across the stream, its surface " +
        "flat except at the very edge where it curves upwards, forming " +
        "a low railing to prevent anyone from falling off. It seems to " + 
        "grow out of the ground like a tree root, and appears to be a " + 
        "single piece as you can find no sign of the wood being joined " + 
        "anywhere. The bridge is the same brown as the trunks of the " + 
        "nearby trees, and gives off the same fresh smell as the living " +
        "oaks.\n"); 

    add_item(({"root"}), 
        "The longer you look at the bridge, the more you think that " + 
        "despite it's size and perfect symmetry that it may just be " + 
        "the root of one of the nearby trees.\n"); 
    
    add_item(({"railing", "wall"}), 
        "The bridge railing is nothing more than a short wall, about two " +
        "two feet high, formed by a sudden curve in the bridges surface, " + 
        "but it should be effective in preventing most people from walking " + 
        "off the bridge into the stream.\n"); 

    add_item(({"surface", "bark"}), 
        "The surface of the bridge, including the railings, appears to be " + 
        "normal oak bark, though it is unusually flat.\n"); 

    add_item(Grass_Words, grass_describe(({"south", "northwest", 
        "to the bridge"}))); 
    add_item(Pond_Words, "@@pond_describe@@"); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Thicket_Words, thicket_describe("west")); 
    add_item(Tree_Words, trees_describe(1, "southeast")); 
    add_item(Village_Words, village_describe()); 

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    pond_tells(); 
    stream_tells(); 
    thicket_tells(); 
      
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_09", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_02", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_01", "up");
}

void
init()
{
    ::init(); 

    add_action(pond_drink, "drink");
    add_action(stream_drink, "drink"); 
}

void
hook_smelled(string smelled)
{
    if (member_array(smelled, ({"bridge", "root", "railing", 
        "surface", "bark"})) >= 0 ) 
    {
        write("The bridge smells just the same as the nearby trees, like " + 
            "a perfectly healthy oak,\n"); 
    }
    else
    {
        common_smells(smelled); 
    }
}


