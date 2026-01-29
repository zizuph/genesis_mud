/* /d/Faerun/guilds/black_flame/rooms/bf_entrance.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";


public int
block_nonmembers()
{
    if (BF_MASTER->is_lay_bf(this_player()->query_name()) == 1)
    {          
        return 0;
    }    
    
    write("Only members of the Order of the Black Flame can "
    +"move in that direction.\n");
    
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("Inside the Temple of Kossuth");
    
    set_long("By the looks of the temple and drawing on "
    +"past experiences with temples in general, you’d be "
    +"quick to assume the temple to be cold and unwelcoming "
    +"but surprisingly you are greeted with a dry, comfortable "
    +"warmth. The area is lit and obviously heated by several "
    +"large, lit braziers. To the north, between a set of "
    +"curtains, you see what can only be the center of the "
    +"building acting like a courtyard of sorts, but you’re "
    +"unable to see much detail through the opening. "
    +"There are hallways going in both east and west "
    +"direction, but their curved nature reveals little "
    +"about what’s around the corner.\n");
    
    add_item(({"wall", "walls"}),
        "The walls are smooth and white, made from "
        +"some kind of dense stone.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In "
        +"contrast to the white walls, the floor almost "
        +"looks black.\n");
        
    add_item(({"hallway", "hallways"}),
        "The hallway extending east and west seem to be "
        +"having the same white stone and dark floor as here. "
        +"You don’t see anything special in either direction from here.\n");
        
    add_item(({"brazier", "braziers"}),
        "The braziers are made of cast iron, and are filled "
        +"with burning firewood at the moment.\n");
        
    add_item(({"curtain", "curtains"}),
        "The curtains are white and heavy. Embroidered in a pattern "
        +"across them are small symbols of a twisting flame. They "
        +"look quite valuable.\n");
        
    add_item(({"courtyard"}),
        "You cannot see much through the small "
        +"gap in the curtains.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_join", "north");
    add_exit(BF_ROOMS_DIR + "bf_corridor4", "east", block_nonmembers);
    add_exit(BF_ROOMS_DIR + "bf_corridor3", "west", block_nonmembers);
    
    // exit
    add_exit("/d/Faerun/highroad/rooms/temproad02", "south");
                          
    
    reset_faerun_room();
}