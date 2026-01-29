/*
 * Calia Utility Functions
 * 
 * Put any misc functions here that may be useful.
 *
 * Created by Petros, May 2011
 */

#pragma strict_types

#include <files.h>
#include <macros.h>

inherit "/d/Sparkle/area/city/lib/utility_functions";

/* 
 * Function:    move_living_special_exit
 * Description: The purpose of this function is to capture a lot of common
 *              code into one function and allow someone to code the movement
 *              of someone moving to a special exit. This is typically used
 *              in code like "enter hole" or "climb tree".
 * Arguments:   player - the player who is doing the moving
 *              roomfile - the room that the player should be moved to
 *              exit_args - the extra arguments after the actual command. For "climb tree", this would be "tree"
 *              messages - This should be an array with the following messages defined
 *                  self_message - message that is shown to player as he is being moved
 *                  leave_message - message shown to people in old room as he is leaving
 *                  arrive_message - message shown to people in new room as he arrives
 */ 
public int
move_living_special_exit(object player, string roomfile, string exit_args, string * messages)
{
    if (!objectp(player) || !strlen(roomfile) || sizeof(messages) != 3)
    {
        return 0;
    }
    object exit_room = safely_load_master_file(roomfile);
    if (!objectp(exit_room))
    {
        return 0;
    }
       
    // Because we write our own leave/arrive messages, we need to
    // do a little processing to make sure that people who can't be
    // seen do not get the messages.
    object old_room = environment(player);
    old_room->set_dircmd(exit_args);
    write(messages[0]);

    // Send a message to the old room to tell them what happened
    object * watchers = FILTER_LIVING_OBJECTS(all_inventory(old_room));
    watchers = filter(watchers, player->check_seen);
    watchers -= ({ player });
    watchers->catch_msg(QCTNAME(player) + " " + messages[1] + "\n");
    
    watchers = FILTER_LIVING_OBJECTS(all_inventory(exit_room));
    watchers = filter(watchers, player->check_seen);
    watchers -= ({ player });        
    if (player->move_living("M", exit_room) == 0)
    {
        // Move was a success.
        // Write the arrival messages in the new room
        watchers->catch_msg(QCTNAME(player) + " " + messages[2] + "\n");
    }
    
    return 1;
}
