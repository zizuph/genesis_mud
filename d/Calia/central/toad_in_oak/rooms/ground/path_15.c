/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_15.c
 *
 * A path on the eastern side of TiO, next to the flower garden
 * 
 * HISTORY: 2003-05-11 Created by Kcirderf
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{
    set_short("A path beneath a village in the trees."); 
    set_long("You stand near the south bank of a small stream that babbles as " + 
        "it makes its way between the trunks of the enormous oak trees of " +
        "the forest. A beautiful wooden bridge leads across the water to an " + 
        "area filled with a multitude of brightly colored flowers. Lush green " +
        "grass covers the ground beneath your feet like a carpet. Far above " + 
        "in the branches of the trees you can see the underside of a small " + 
        "village.\n"); 
    
    add_item(({"bridge", "wooden bridge"}), 
        "The bridge that crosses the stream looks almost as if it grew as a " + 
        "natural part of the forest, rising out of the ground like a tree " + 
        "root and crossing the stream without any apparant breaks where " + 
        "pieces have been joined. It gives off the same fresh smell as " +
        "the surrounding trees, and is covered in the same brown bark. " + 
        "The surface of the bridge is relatively smooth, except for the " + 
        "sides, which curve upwards to form a sort of railing.\n"); 

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

    add_item(({"flowers"}), "Across the stream from where you stand grow " + 
        "flowers of a wide variety of types. From here the details are " + 
        "are lost in the mix of bright colours.\n"); 
        
    add_item(Grass_Words, grass_describe(({"southwest", "to the bridge"}))); 
    add_item(Stream_Words, stream_describe()); 
    add_item(Tree_Words, trees_describe(1, "west"));
    add_item(Village_Words, village_describe()); 

    stream_tells(); 
    add_tell("A butterfly flutters by, heading towards the flowers " + 
        "on the far side of the stream.\n"); 
    add_tell("A bee buzzes past your ear on it's way home after a visit " +
        "to the flowers.\n"); 

    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_s", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_14", "southwest"); 
}

void
init()
{
    ::init(); 

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
    else if (smelled == "flowers") 
    {
        write("You can detect a floral scent in the air from here, " + 
            "but you are too far away to really smell the flowers.\n"); 
    }
    else
    {
        common_smells(smelled); 
    }
}



