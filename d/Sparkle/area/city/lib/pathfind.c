/*
 * Pathfind Library Module
 *
 * This library will allow you to find the shortest path
 * between two rooms. Inherit this file, and define
 * is_valid_room to determine which rooms are accessible 
 * and which are not.
 *
 * Created March 2008, by Novo
 * Modified April 2008, Petros - support for doors, loading rooms
 * Modified April 2009, Petros - support for debug messages
 * Modified June 2009, Petros - cleaned up code, added customizable 
 *                              max distance
 */

// Includes
#include <macros.h>
#include <files.h>

// Inherits
inherit "/d/Sparkle/area/city/lib/utility_functions";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public int          m_distance = 50; // default it to 50

/*
 * Function:    set_max_pathfind_distance
 * Description: Allows a customizable max pathfind distance
 *              This is the farthest depth that the algorithm
 *              will travel when looking for the shortest path
 *              to the destination.
 */
public void
set_max_pathfind_distance(int distance)
{
    m_distance = distance;
}

/*
 * Function:    query_max_pathfind_distance
 * Description: Returns the customizable max pathfind distance
 *              This is the farthest depth that the algorithm
 *              will travel when looking for the shortest path
 *              to the destination.
 */
public int
query_max_pathfind_distance()
{
    return m_distance;
}

/*
 * Function:    is_valid_room
 * Description: This is the user function that is called for every room
 *              during the algorithm. By default, it returns 0.
 *              In order for the pathfind algorithm to work, one
 *              should define this function and define exactly what
 *              should be computed.
 *              Note: This function is called by validate_room.
 * Arguments:   str - the path of the room
 * Returns:     1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    return 0;
}

/*
 * Function:    validate_room
 * Description: This function takes a room file and loads the room file
 *              to ensure that it's a valid room, then validates the object
 *              to make sure that it's a room. Of course, it also checks
 *              to make sure that this room is allowed to be part of
 *              the shortest path algorithm (is_valid_room)
 * Arguments  : roomfile - the path to the room to check
 * Returns    : 0/1 - invalid/valid
 */
public nomask int
validate_room(string roomfile)
{
    object room;
    
    if (!is_valid_room(roomfile))
    {
        // No need to proceed further. The npc has declared this
        // to be an invalid room
        return 0;
    }
    
    // First see if we can even load the file and check to see if 
    // it's a real room
    if (!objectp(room = safely_load_master_file(roomfile))
        || !IS_ROOM_OBJECT(room))
    {
        return 0;
    }

    return 1;
}

public string
clean_filename(string file)
{
    if (!strlen(file))
    {
        return "";
    }
    
    if (wildmatch("*.c", file))
    {
        return file[..-3];
    }
    
    return file;
}

public mixed
get_room_exits(string roomfile)
{
    object room;
    string * exits;
    string * door_commands;
    object * doors;
    
    // We assume that the room is valid, since get_room_exits
    // only gets called when we are sure that the node is
    // a valid room
    room = safely_load_master_file(roomfile);
    // Get all the normal exists
    exits = room->query_exit();
    
    // Clean the exits
    for (int index = 0; index < sizeof(exits); index += 3)
    {
        exits[index] = clean_filename(exits[index]);
        string dir, vbfc;
        if (sscanf(exits[index], "%s@@%s", dir, vbfc))
        {
            vbfc = call_other(room, vbfc);
            if (strlen(vbfc))
            {
                exits[index] = dir + vbfc;
            }
        }
    }
    
    // Now check for door exits
    doors = FILTER_DOOR_OBJECTS(all_inventory(room));
    foreach (object door : doors)
    {
        if (sizeof(door->query_pass_command()))
        {
            door_commands = door->query_pass_command();
            exits += ({ clean_filename(door->query_other_room()), 
                door_commands[0], 0 });
        }
    }
    
    return exits;
}

public string
get_lowest_cost(string * unprocessed_rooms, mapping nodes)
{
    string lowest_room;
    int    lowest_cost = query_max_pathfind_distance();
    
    foreach (string room : unprocessed_rooms)
    {
        mixed * node = nodes[room];
        if (node[0] < lowest_cost)
        {
            lowest_cost = node[0];
            lowest_room = room;
        }
    }
    
    return lowest_room;
}

/*
 * Function:    find_path
 * Description: This function uses Dijkstra's algorithm to determine the
 *              shortest path between two rooms. Dijkstra's algorithm is
 *              a greedy algorithm, so when it arrives at the end room,
 *              we know it's the shortest exit.
 * Arguments:   startroom - the path to the starting room
 *              endroom - the path to the ending room
 * Returns:     an array of strings containing the directions
 *              to walk in order to reach the end room.
 */
public mixed 
find_path(string startroom, string endroom)
{
    startroom = clean_filename(startroom);
    endroom = clean_filename(endroom);

    if (!validate_room(startroom))
    {
        return ({ });   
    }

    if (!validate_room(endroom))
    {
        return ({ });   
    }
    
    if (endroom == startroom)
    {
        return ({ });   
    }

    // Each Node in the Graph is characterized by this mapping relationship
    // room filename   :   cost to get to room from source (incl fatigue)
    //                     direction to get here (eg. southwest)
    //                     room to get here (eg. /room/chapel)
    //                     visited

    string * unprocessed_rooms = ({ });
    mapping  nodes = ([ ]);
    
    // Add the start room to both the unprocessed rooms and the nodes
    nodes[startroom] = ({ 0, "", "", 0 });
    unprocessed_rooms += ({ startroom });
    
    while (sizeof(unprocessed_rooms))
    {
        string current_room = get_lowest_cost(unprocessed_rooms, nodes);
        if (!strlen(current_room))
        {
            break;
        }
        
        if (current_room == endroom)
        {
            send_debug_message("pathfind", "Found end room "
                + endroom + ".");
            break;
        }
        
        mixed current_node = nodes[current_room];
        current_node[3] = 1; // Mark this node as visited
        unprocessed_rooms -= ({ current_room });
        if (!validate_room(current_room))
        {
            continue;
        }
        
        mixed exits = get_room_exits(current_room);
        if (!sizeof(exits))
        {
            send_debug_message("pathfind", "No exits found in "
                + current_room + ".");
            continue;
        }
        
        int total_cost = current_node[0];    
        // Go through each of the exits, updating paths as needed
        // Exits are stored in groupings of three: file, direction, func
        for (int index = 0; index < sizeof(exits); index += 3)
        {
            string exit_room = exits[index];
            mixed to_node = nodes[exit_room];
            if (!stringp(exit_room) // exits can be functions
                || !strlen(exit_room)
                || !validate_room(exit_room)
                || (sizeof(to_node) && to_node[3] == 1))
            {
                // The room is not a valid exit or it has already been
                // visited.
                continue;
            }

            int exit_cost = max(1, current_room->query_tired_exit(index / 3));
            int new_cost = total_cost + exit_cost;
            /* If too expensive, ignore it */
            if (new_cost > query_max_pathfind_distance())
            {
                send_debug_message("pathfind", "The room exit in " 
                    + current_room + " to " + exit_room
                    + " exceeds the maximum pathfind distance.");
                continue;
            }
              
            string exit_direction = exits[index + 1];
            // If new room, add it to our lists.  If old, update only if
            // we found a new shorter path
            if (!sizeof(to_node))
            {
                to_node = ({ new_cost , exit_direction, current_room, 0 });
                nodes += ([ exit_room : to_node ]);
                unprocessed_rooms += ({ exit_room });
            }
            else
            {
                /* Don't update finished nodes, and don't update if the
                new path is longer than our best so far */
                if (new_cost < to_node[0])
                {
                    to_node[0] = new_cost;
                    to_node[1] = exit_direction;
                    to_node[2] = current_room;
                }
            }
        }
    }

    
    /* We have searched all paths, time to build our result from
       the end to the start */
    
    /* Did we find a path to the end room? */
    if (!nodes[endroom])
    {
        return ({ });
    }
    
    string * dirs = ({ });

    while (endroom != startroom)
    {
        mixed current_node = nodes[endroom];
        
        //Each direction goes to the front of the list
        dirs = ({ current_node[1], current_node[2] }) + dirs;
        endroom = current_node[2];
    }
    
    return dirs;       
}

