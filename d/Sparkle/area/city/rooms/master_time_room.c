/*
 * /d/Sparkle/area/city/rooms/master_time_room.c
 *
 * Master Time Room for the City of Sparkle
 *
 * Created by Petros, April 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

// Defines

// Inheritance
inherit "/std/room";

// Global Variables
object time_keeper;

// Prototypes
public void             create_room();
public void             init();
public void             reset_room();
public void             notify_timekeeper();
public object           get_timekeeper();


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
} // init

/* 
 * Function name:       create_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_room()
{
    set_short("Master Time Room");
    set_long("This is the Master Time Room of the City of Sparkle\n\n");
    // Room Item Section                              

    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Exits Section
    
    reset_room();
} // create_room

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
    float genesis_hour;
    float delay_seconds;
    mixed * calls;
            
    time_keeper = find_object(OBJ_DIR + "master_time_object");    
    if (!time_keeper || sizeof(object_clones(time_keeper)) == 0)
    {
        time_keeper = clone_object(OBJ_DIR + "master_time_object");

        time_keeper->move(this_object(), 1);

        calls = get_all_alarms();
        foreach (mixed call : calls)
        {
            remove_alarm(call[0]);
        }

        // Notify the npc's once per hour.
        genesis_hour = 3600.000 / 55.000;
        delay_seconds = (3600.0 - itof(get_timekeeper()->s_get_time() % 3600)) 
                        / 55.0;
        delay_seconds += 1.0; // slight delay because time right around
                              // the hour is a bit iffy
        set_alarm(delay_seconds, genesis_hour, 
                  &notify_timekeeper());        
    }
} // reset_room

public object
get_timekeeper()
{
    if (!time_keeper)
    {
        reset_room();
    }
    
    return time_keeper;
}

public void
notify_timekeeper()
{
    get_timekeeper()->notify_npcs();
}
