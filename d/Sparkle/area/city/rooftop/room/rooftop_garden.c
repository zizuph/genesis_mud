/*
 * /w/petros/sparkle/rooftop/room/rooftop.c
 *
 * Rooftop of the Library
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines
#define MAX_LEMONS 5

// Inheritance
inherit ROOFTOP_ROOM_BASE;

// Global Variables
int num_lemons;

// Prototypes
public void             init();
public int              pick_cmd(string args);

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
    
    add_action(pick_cmd, "pick");
} // init

/* 
 * Function name:       create_rooftop_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_rooftop_room()
{
    // Descriptions Section
    set_short("Garden on Rooftop of Genesis Library");
    set_long("The view from up here is simply magnificent. One can see "
           + "all of Sparkle from here. To the east is the Tower of "
           + "Realms, and beyond that are the piers and the sea. To the "
           + "west are the city gates, and beyond that the beautiful "
           + "mountains and forests that lie outside of Sparkle. Below, "
           + "you see the citizens of the city of Sparkle walking along "
           + "the streets. You are in the middle of the Library rooftop. "
           + "Here someone has planted a small garden."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "east", "tower", "tower of realms" }),
                 "The Tower of Realms is located to the east. "
               + "You can probably walk across the rooftop east "
               + "to get a better view of it."
               + "\n");
                              
    add_item( ({ "west", "guild", "adventurer guild", "adventurers guild" }),
                 "The Adventurer Guild is located to the west of the "
               + "Library. You can probably walk across the rooftop west "
               + "to get a better view of it."
               + "\n");
    
    add_item( ({ "rooftop", "rooftops" }),
                 "All around you are various rooftops in Sparkle. You are "
               + "surprised how close they have all been built together. "
               + "You stand in the center of the Library rooftop."
               + "\n");

    add_item( ({ "plants", "garden", "flowers", "flower" }),
                 "It is a small garden in the midst of the rooftop. A great "
               + "amount of love has been placed into the pruning and care "
               + "of these plants. A single tree stands in the middle of "
               + "this little garden, providing a bit of shade."
               + "\n");

    add_item( ({ "tree", "lemon tree", "shade" }),
                 "The tree is a tall, strong, lemon tree. You see many "
               + "bright yellow lemons on the tree which look quite "
               + "ripe. Surprisingly, there are no lemons on the "
               + "ground where the tree has provided ample shade. You "
               + "think you may be able to <pick> a lemon from the "
               + "tree."
               + "\n");

    add_item( ({ "lemon", "lemons" }),
                 "You see many lemons in the lemon tree, but not all of "
               + "them are ripe. You might be able to find a ripe one "
               + "to <pick>."
               + "\n");

    // Properties Section
    add_prop(ROOM_S_MAP_FILE, "library_map.txt");
    
    // Exits Section
    add_exit(ROOFTOP_ROOM_DIR + "rooftop_east", "east", 0);
    add_exit(ROOFTOP_ROOM_DIR + "rooftop_west", "west", 0);
    
    num_lemons = 5;
    
    // Set up the broadcast room calls
    set_broadcast_room_type(ROOM_TYPE_ROOF);
    register_broadcast_rooms( ({ STREET_DIR + "center_f" }) );
    
} // create_rooftop_room

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    if (num_lemons >= MAX_LEMONS)
    {
        return;
    }
    
    if (num_lemons <= (MAX_LEMONS - 2))
    {
        num_lemons += 2;
    }
    else
    {
        num_lemons = MAX_LEMONS;
    }
    
    tell_room(this_object(), "The tree bristles a little as a few lemons "
                           + "ripen fully.\n");
} // reset_room

/*
 * Function name:        pick_cmd
 * Description  :        One can pick a lemon off the tree here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
pick_cmd(string args)
{
    if (!args)
    {
        notify_fail("Pick what?\n");
        return 0;
    }
    
    switch (args)
    {
    case "lemon":
    case "lemon from tree":
        if (num_lemons == 0)
        {
            write("You don't find any ripe lemons on the tree that you "
                + "can pick.\n");
            return 1;
        }

        write ("You carefully select a very ripe yellow lemon and "
             + "quickly yank it from the tree. The tree bristles a little "
             + "and settles back into place. You notice a budding lemon "
             + "beginning to grow where you just picked one.\n");
        --num_lemons;
        clone_object(ROOFTOP_OBJ_DIR + "lemon")->move(this_player(), 1);  
        return 1;
        break;
                
    default:
    }
    
    notify_fail("Pick what?\n");
    return 0;    
}
