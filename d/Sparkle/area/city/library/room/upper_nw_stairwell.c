/*
 * /w/petros/sparkle/library/room/upper_nw_stairwell.c
 *
 * Second Floor Stairwell leading to Restorer's Office
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
    set_short("Second floor northwest stairwell");
    set_long("You are atop the staircase on the second floor of the "
           + "Library. Surprisingly, the walls here are rather bare, "
           + "a stark contrast to the well decorated portion on the "
           + "first floor. To your south, you see a door, but it is "
           + "unclear where it leads to. There is a window above you "
           + "that lets in the light from outside. High above you is "
           + "a beautiful dome-like ceiling."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "stairwell", "second floor", "second floor stairwell",
                 "northwest stairwell" }),
                  "This part of the stairwell sure looks like it could "
                + "do with a little more decorating."
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

    add_item( ({ "walls", "wall" }),
                  "The walls are quite bare here. As you gaze at the "
                + "walls, you can't help but notice the window that "
                + "allows the light to fill this room."
                + "\n"); 
                
    add_item( ({ "dome-like ceiling", "ceiling",
                 "murals", "beautiful murals" }),
                  "The bright light streaming in from the window hits "
                + "the ceiling and reflects the beautiful murals that "
                + "have been painted on it. From here, it is quite "
                + "a magnificent sight."
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
                 "murals", "beautiful murals" }),
                  "The bright light streaming in from the window hits "
                + "the ceiling and reflects the beautiful murals that "
                + "have been painted on it. From here, it is quite "
                + "a magnificent sight."
                + "\n"); 

    add_item( ({ "door" }),
                  "A door presents the only way to continue on this "
                + "floor. You can't tell what it leads to though."
                + "\n"); 
                
    add_item( ({ "light" }),
                  "The light streams in from the window, filling this "
                + "room with the soft, comfortable light that one is "
                + "accustomed to in Sparkle."
                + "\n"); 

    // Properties Section

    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "restorer", "south", 0);
    add_exit(LIBRARY_ROOM_DIR + "nw_stairwell", "down", 0);
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

        new_room = safely_load_master_file(ROOFTOP_ROOM_DIR + "rooftop_west");
        
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

