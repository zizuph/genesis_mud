/*
 * /w/petros/sparkle/rooftop/room/rooftop_east.c
 *
 * Rooftop of the Library
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
inherit ROOFTOP_ROOM_BASE;
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Global Variables

// Prototypes
public void             init();
public int              climb_cmd(string args);
public void             create_rooftop_room();

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
 * Function name:       create_rooftop_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_rooftop_room()
{
    // Descriptions Section
    set_short("Rooftop of Genesis Library");
    set_long("The view from up here is simply magnificent. One can see "
           + "all of Sparkle from here. To the east is the Tower of "
           + "Realms, and beyond that are the piers and the sea. To the "
           + "west are the city gates, and beyond that the beautiful "
           + "mountains and forests that lie outside of Sparkle. Below, "
           + "you see the citizens of the city of Sparkle walking along "
           + "the streets. You realize you are at the northeast corner "
           + "of the Genesis Library rooftop. From here, you can climb "
           + "down to the window ledge."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "west", "guild", "adventurer guild", "adventurers guild" }),
                 "The Adventurer Guild is located to the west of the "
               + "Library. You can probably walk across the rooftop west "
               + "to get a better view of it. To your west on the rooftop "
               + "you also see a lot of plants that someone has placed on "
               + "the roof."
               + "\n");
                              
    add_item( ({ "east", "tower", "tower of realms" }),
                 "You stand on the northeastern edge of the rooftop. To "
               + "your east, you can tell just how close you are to the "
               + "next building, which is the Tower of Realms."
               + "\n");
    
    add_item( ({ "ledge", "window ledge" }),
                 "A window ledge is right below you, over the edge of "
               + "the roof to the east. You think you might be able to "
               + "climb down to it and into the library."
               + "\n");

    add_item( ({ "rooftop", "rooftops" }),
                 "All around you are various rooftops in Sparkle. You are "
               + "surprised how close they have all been built together. "
               + "Along the rooftop of the Library, you can walk to the "
               + "west. You also see a strange array of plants "
               + "to the west of you."
               + "\n");

    add_item( ({ "plants" }),
                 "The rooftop seems to contain an array of plants to the "
               + "west of you. You might be able to get a closer look if "
               + "you walked a little west."
               + "\n");

    // Properties Section
    add_prop(ROOM_S_MAP_FILE, "library_map.txt");
    
    // Exits Section
    add_exit(ROOFTOP_ROOM_DIR + "rooftop_garden", "west", 0);
    
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

} // reset_room

/*
 * Function name:        climb_cmd
 * Description  :        This is the way to get back down off the roof
 *                       back into the Library
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
climb_cmd(string args)
{
    object * watchers;
    object old_room, new_room;
    
    if (!args)
    {
        notify_fail("Climb where?\n");
        return 0;
    }
    
    switch (args)
    {
    case "down":
    case "down ledge":
    case "down to ledge":
        // Because we write our own leave/arrive messages, we need to
        // do a little processing to make sure that people who can't be
        // seen do not get the messages.
        old_room = this_object();
        set_dircmd(args);
        write("You climb back down to the ledge, and realize how windy "
            + "it is, and quickly head into the Library stairwell "
            + "through the window.\n");

        // Send a message to the old room to tell them what happened
        watchers = FILTER_LIVING_OBJECTS(all_inventory(old_room));
        watchers = filter(watchers, this_player()->check_seen);
        watchers -= ({ this_player() });
        watchers->catch_msg(QCTNAME(this_player()) + " climbs down "
            + "to the ledge.\n", watchers);

        new_room = safely_load_master_file(LIBRARY_ROOM_DIR + "upper_ne_stairwell");
        
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
            watchers->catch_msg(QCTNAME(this_player()) + " climbs in "
                + "through the window.\n");
        }
            
        return 1;
                
    default:
    }
    
    notify_fail("Climb down to ledge?\n");
    return 0;
}
