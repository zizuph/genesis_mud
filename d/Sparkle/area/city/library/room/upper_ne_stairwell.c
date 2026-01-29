/*
 * /w/petros/sparkle/library/room/upper_ne_stairwell.c
 *
 * Second floor northeast stairwell leading to the Head Librarian's
 * office.
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include "defs.h"

// Defines

// Inheritance
inherit LIBRARY_ROOM_BASE;
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Global Variables

// Prototypes
public void             init();
public int              climb_cmd(string args);
public void             create_library_room();

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

    add_action(climb_cmd, "climb");
     
} // init

/* 
 * Function name:       create_library_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_room()
{
    // Descriptions Section
    set_short("Second floor northeast stairwell");
    set_long("This is the second floor of the northeast stairwell. You "
           + "can see the walls here are also filled with paintings, like "
           + "the ones that you saw on the first floor. It is a lot "
           + "brighter here than on the first floor because of the "
           + "proximity of the window here. The dome-like ceiling glows "
           + "softly from the reflection of the light upon it. To the "
           + "west, you see a small waiting area. You can also proceed "
           + "down the marble staircase with the exquisite railing."
           + "\n\n");
  
    // Room Item Section                              
    add_item( ({ "stairwell", "second floor", "second floor stairwell",
                 "northeast stairwell" }),
                  "You are standing on the second floor of the northeast "
                + "stairwell. The stairwell comprises of some amazing "
                + "artwork in addition to the functional staircase that "
                + "allows one to travel between the floors."
                + "\n"); 
                
    add_item( ({ "staircase", "marble staircase", "stairs", "stair" }),
                  "The stairs are hewn from high quality marble, and have "
                + "been made in such a way that they give a brilliant "
                + "shine. You wonder how much effort it takes to clean "
                + "such a staircase day in and day out."
                + "\n"); 

    add_item( ({ "railing", "exquisite railing" }),
                  "The railing is made of pure gold. The touch of the "
                + "gold on the skin is almost enough to make you tingle "
                + "with a bit of greed."
                + "\n"); 

    add_item( ({ "walls", "wall", "paintings", "painting" }),
                  "The walls are filled with paintings. From here at the "
                + "top of the stairwell, however, you can't quite "
                + "approach them. Above the paintings you see "
                + "a window that lets in light from the outside."
                + "\n"); 
                
    add_item( ({ "window" }),
                  "A rectangular window approximately the size of two "
                + "adult humans streams in the light from the outside. "
                + "You notice that beneath the window are some steps that "
                + "have been built into the wall."
                + "\n"); 

    add_item( ({ "steps" }),
                  "It is rather strange to find steps beneath the window. "
                + "It's hard to imagine why they would be necessary. You "
                + "think that you might be able to climb them."
                + "\n"); 

    add_item( ({ "reflection", "dome-like ceiling", "ceiling",
                 "murals", "beautiful murals", "dome", "mural" }),
                  "The bright light streaming in from the window hits "
                + "the ceiling and reflects the beautiful murals that "
                + "have been painted on it. From here, it is quite "
                + "a magnificent sight."
                + "\n"); 

    add_item( ({ "waiting area", "west" }),
                  "You see a small waiting area to your west."
                + "\n"); 
                
    add_item( ({ "light" }),
                  "The light streams in from the window, illuminating "
                + "and enhancing all the things in this stairwell."
                + "\n"); 

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "waiting_room", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "ne_stairwell", "down", 0);
} // create_library_room

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
} // reset_room

/*
 * Function name:        climb_cmd
 * Description  :        The player can climb the steps and get up onto
 *                       the window ledge. This allows the player to 
 *                       view Sparkle from high up, as well as possibly
 *                       allow them to get onto the roof later for the
 *                       roof aspects of Sparkle
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
climb_cmd(string args)
{
    object old_room, new_room;
    object * watchers;
    
    if (!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }
    
    switch (args)
    {
    case "steps":
    case "step":
    case "to window":
    case "window":
        // Because we write our own leave/arrive messages, we need to
        // do a little processing to make sure that people who can't be
        // seen do not get the messages.
        old_room = this_object();
        set_dircmd(args);
        write ("You climb up the steps and find yourself on a very "
             + "small ledge. With the wind blowing so strongly, you "
             + "catch a hold of the roof and quickly climb up onto "
             + "the roof.\n");

        // Send a message to the old room to tell them what happened
        watchers = FILTER_LIVING_OBJECTS(all_inventory(old_room));
        watchers = filter(watchers, this_player()->check_seen);
        watchers -= ({ this_player() });
        watchers->catch_msg(QCTNAME(this_player()) + " climbs out "
            + "the window.\n", watchers);

        new_room = safely_load_master_file(ROOFTOP_ROOM_DIR + "rooftop_east");
        
        if (!objectp(new_room))
        {
            return 1;
        }
            
        watchers = FILTER_LIVING_OBJECTS(all_inventory(new_room));
        watchers = filter(watchers, this_player()->check_seen);
        watchers -= ({ this_player() });        
        if (this_player()->move_living("M", new_room) == 0)
        {
            // Move was a success.
            // Write the arrival messages in the new room
            watchers->catch_msg(QCTNAME(this_player()) + " climbs up "
                + "onto the roof.\n");
        }
        return 1;

    case "wall":
    case "walls":
        write("You attempt to climb the " + args + ", but you cannot "
            + "seem to get a firm footing on the slippery marble. You may "
            + "want to try the steps instead.\n");
        break;

    default:    
    }
    
    notify_fail("Climb what?\n");
    return 0;
}
