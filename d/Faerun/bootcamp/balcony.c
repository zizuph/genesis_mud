/* /d/Faerun/bootcamp/balcony.c
 *
 * A training room 
 *
 * Nerull, 2017
 */

#include "/d/Faerun/defs.h"

#include <stdproperties.h>

inherit "std/room";


/*
 * Function name: create_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);

    set_short("A large balcony");
    
    set_long("This is a large balcony overlooking the front of the building. "
        +"It extends out over the entrance and allows anyone here to observe "
        +"visitiors to the guild. A set of stairs leads downstairs and back "
        +"into the guild house.\n");

        
    add_item(({"balcony"}),
        "It is made of marble and is half-circle shaped. It extends " 
        +"out over the entrance of the building and affords a view below. " 
        +"A rail runs along the perimeter of the balcony and prevents " 
        +"anyone from falling off.\n");

    add_item(({"rail"}),
        "The rail is about waist high and runs along the outside " 
        +"of the balcony. It is wide and flat, and held up by "
        +"balustrades.\n");
        
    add_item(({"balustrade", "balustrades"}),
        "The balustrades are urn shaped and waist high. They are made " 
        +"of marble and hold the rail in place along the perimeter of " 
        +"the balcony.\n");
        
    add_item(({"entrance"}),
        "You are unable to see the entrance. It is covered by this " 
        +"balcony.\n");
        
    add_item(({"building", "guild hall", "guildhall", "guildhouse",
            "guild house",}),
        "It is a large building, made of marble blocks, and spreads " 
        +"out to your left and right.\n");
        
    add_item(({"stairs", "staircase", "stair case"}),
        "The staircase is circular and made of iron. It is set against " 
        +"a wall and leads downstairs.\n");
    
    add_exit("/d/Faerun/bootcamp/lounge", "lounge");
}



