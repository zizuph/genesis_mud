/*
 *  /w/petros/sparkle/sewer/room/sewer_room_base.c
 *
 *  This will be the base file for every sewer room
 *
 *  Created May 2008, by Petros
 */
#pragma strict_types

#include "defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

inherit SPARKLE_ROOM_BASE;

/* Global Variables */

/* Prototypes */
nomask void        create_sparkle();
public void        create_sewer_room();
public void        init();
public int         drink_cmd(string args);

/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sparkle()
{
    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "library_map.txt");
    
    // Call the base creation function for sewers
    create_sewer_room();

    // Add the try_items after create_sewer_room so that it will not
    // replace the items added by subclasses
    // Room Item Section                              
    try_item( ({ "water", "waters", "murky waters", "murky water" }),
                 "You can barely see through the water since it is "
               + "so very dirty. Occasionally, you see movement, "
               + "possibly from the little critters that must reside "
               + "down in this filthy place."
               + "\n");
                              
    try_item( ({ "floor", "marble floor", "floors", "marble floors",
                 "ground" }),
                 "You can't really see through to the floors of the "
               + "sewer since the water here is so murky."
               + "\n");
    
    try_item( ({ "wall", "walls", "stone" }),
                 "There is enough light here for you to tell that the "
               + "sewers are an underground tunnel system that was hewn "
               + "from stone."
               + "\n");
               
    try_item( ({ "tunnel", "tunnels", "tunnel system" }),
                 "The light is barely enough for you to see in the room "
               + "you are in. It's very difficult to make out the actual "
               + "directions the tunnels go in."
               + "\n");

    try_item( ({ "ceiling" }),
                 "The ceiling of the sewers is rounded, as is this entire "
               + "place. You don't note anything special about the "
               + "ceiling here."
               + "\n");
                   
    try_item( ({ "room", "sewer", "sewer system" }),
                 "You are standing in a part of the sewer system that runs "
               + "underneath the City of Sparkle."
               + "\n");
} // create_sparkle

/*
 * Function name:        create_sewer_room
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_sewer_room()
{
    
} // create_sewer_room


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    
    add_action(drink_cmd, "drink");
} // init

public int
drink_cmd(string args)
{
    if (!args)
    {
        notify_fail("Drink what?\n");
        return 0;
    }
    
    if (parse_command(args, ({ }), "[murky] / [sewer] 'water'"))
    {
        write("You bend down to scoop up some water to drink, but "
            + "the stench causes you to abandon the effort.\n");
        return 1;
    }
    
    notify_fail("Drink what?\n");
    return 0;
}
