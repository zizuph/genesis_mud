/*
 * /w/petros/sparkle/library/room/waiting_room.c
 *
 * Waiting room outside the Office of the Head Librarian
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines
#define SITTING_SHORT_MSG " is sitting"

// Inheritance
inherit LIBRARY_ROOM_BASE;

// Global Variables

// Prototypes
public void             init();
public int              sit_cmd(string arg);
public int              stand_cmd(string arg);
public int              prevent_leave(object ob);


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

    add_action(sit_cmd, "sit");
    add_action(stand_cmd, "stand");
    
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
    set_short("Head librarian's office waiting room");
    set_long("The marble walls are rather bare here in the "
           + "waiting room outside the Head Librarian's office. There is "
           + "a single bench here facing the office doorway to the south. "
           + "It is rather quiet here, as one would expect in a Library. "
           + "To your east you can see the stairwell leading back down "
           + "to the main stacks of the Library."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "walls", "marble walls", "marble wall", "wall",
                 "marble", "bare walls", "bare wall" }),
                 "The marble that makes up the walls seems to be a single "
               + "piece of marble. You aren't sure exactly how that is "
               + "possible. Other than that, there isn't anything special "
               + "about the walls."
               + "\n");

    add_item( ({ "bench", "wooden bench", "simple wooden bench",
                 "simple bench" }),
                 "A simple wooden bench that sits against the bare walls "
               + "allowing people to sit and wait for the Head Librarian. "
               + "\n");
                              
    add_item( ({ "office" }),
                 "The Head Librarian's office is south of the waiting "
               + "room."
               + "\n");

    add_item( ({ "waiting room" }),
                 "You are in the waiting room. There is a bench here for "
               + "for those who are waiting for the Head Librarian."
               + "\n");

    add_item( ({ "office doorway", "doorway" }),
                 "The doorway is the passage into the office of the Head "
               + "Librarian."
               + "\n");

    add_item( ({ "east", "stairwell" }),
                 "The stairwell back down to the first floor is to the "
               + "east."
               + "\n");
               
    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "upper_ne_stairwell", "east", 0);
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
    if(!objectp(present("_head_office_door_out")))
    {
        clone_object(LIBRARY_OBJ_DIR 
                     + "head_office_door")->move(this_object());
    }
} // reset_room

/*
 * Function name: sit_cmd
 * Description  : Allows the player to sit on the bench
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
sit_cmd(string arg)
{
    switch (arg)
    {
    case "on bench":
    case "bench":
        if (this_player()->query_prop(LIVE_S_EXTRA_SHORT) == SITTING_SHORT_MSG)
        {
            notify_fail("You are already sitting down!\n");
            return 0;
        }
    
        write("You sit down on the bench and begin to wait.\n");
        this_player()->add_prop(LIVE_S_EXTRA_SHORT, SITTING_SHORT_MSG);
        return 1;
        break;

    default:
        notify_fail("Sit on what?\n");
    }
    
    return 0;
} // sit_cmd

/*
 * Function name: stand_cmd
 * Description  : Allows the player to stand after sitting
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
stand_cmd(string arg)
{
    if (arg && arg != "up")
    {
        notify_fail("Stand up?\n");
        return 0;
    }    
    
    if (this_player()->query_prop(LIVE_S_EXTRA_SHORT) == SITTING_SHORT_MSG)
    {
        write("You get up from the bench.\n");
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
        return 1;
    }

    notify_fail("You aren't sitting down!\n");
    return 0;
} // stand_cmd

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    if (this_player()->query_prop(LIVE_S_EXTRA_SHORT) == SITTING_SHORT_MSG)
    {
        write("You get up from the bench as you prepare to leave.\n\n");
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    }
    
    return 0;
}
