/*
 * /w/petros/sparkle/sewer/room/sewer1.c
 *
 * A part of the sewer system underneath the sewer in Sparkle
 *
 * Created by Petros, April 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit SEWER_ROOM_BASE;

// Global Variables

// Prototypes
public void             init();
public void             create_sewer_room();
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
 * Function name:       create_sewer_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sewer_room()
{
    // Descriptions Section
    set_short("Sparkle Sewers");
    set_long("You stand knee deep in the murky waters of the sewer "
           + "system underneath the City of Sparkle. The stench here "
           + "is almost unbearable. A ladder here leads up."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "hole", "ladder" }),
                 "A ladder here leads up to a hole above. It must be "
               + "one of the ways to get out of this sewer."
               + "\n");
                              
    // Properties Section
    
    // Exits Section
    add_exit(SEWER_ROOM_DIR + "sewer_entrance", "up", 0);
    add_exit(SEWER_ROOM_DIR + "sewer2", "west", 0);
    add_exit(SEWER_ROOM_DIR + "sewer3", "east", 0);
    add_exit(SEWER_ROOM_DIR + "sewer5", "north", 0);    
} // create_sewer_room

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
    object rat;
    int num_rats;
    
    if (!present("rat")) {
        num_rats = random(6) + 2;    
        for (int i = 0; i < num_rats; ++i) {
            rat = clone_object(SEWER_NPC_DIR + "sewer_rat");
            rat->move(this_object());
        }
    }
} // reset_room

/*
 * Function name:        climb_cmd
 * Description  :        Allow the user to climb down
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
climb_cmd(string args)
{
    if (!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (parse_command(args, ({ }), 
         "[up] [ladder]"))
    {
        this_player()->move_living("up", 
                                   SEWER_ROOM_DIR + "sewer_entrance");
        return 1;        
    }
    
    notify_fail("Climb what?\n");
    return 0;
}
