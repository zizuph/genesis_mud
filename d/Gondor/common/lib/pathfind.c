/*
 * /d/Gondor/common/lib/pathfind.c
 *
 * This library will allow you to find the shortest path
 * between two rooms.  Inherit this file, and define
 * is_valid_room to determine which rooms are accessible 
 * and which are not.
 * Created March 2008, by Novo
 * Modified April 2008, Petros - support for doors, loading rooms
 * Copied to Gondor by Eowul, April 2009
 */

#include <macros.h>
#include <files.h>

#define MAX_PATHFIND_DISTANCE 50

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    return 0;
}

/*
 * Function name: validate_room
 * 
 * This function takes a room file and loads the room file
 * to ensure that it's a valid room, then validates the object
 * to make sure that it's a room. Of course, it also checks
 * to make sure that the npc allows this room to be part of
 * the shortest path algorithm
 * 
 * Arguments  : roomfile - the path to the room to check
 * Returns    : 0/1 - invalid/valid
 *              
 */
public int
validate_room(string roomfile)
{
    object room;
    
    if (!is_valid_room(roomfile))
    {
        // No need to proceed further. The npc has declared this
        // to be an invalid room
        return 0;
    }
    
    // First see if we can even load the file
    if (LOAD_ERR(roomfile))
    {
        return 0;
    }
    
    room = find_object(roomfile); // object should be loaded now
    // Now check to see if it's a real room
    if (!IS_ROOM_OBJECT(room))
    {
        return 0;
    }
        
    return 1;
}

public mixed
get_room_exits(string roomfile)
{
    object room;
    string * exits;
    string * door_commands;
    object * objects;
    
    // We assume that the room is valid, since get_room_exits
    // only gets called when we are sure that the node is
    // a valid room
    room = find_object(roomfile);
    // Get all the normal exists
    exits = room->query_exit();
    
    // Now check for door exits
    objects = all_inventory(room);
    foreach (object obj : objects)
    {
        // Check if it's a door
        if (IN_ARRAY("/std/door.c", inherit_list(obj))
            && sizeof(obj->query_pass_command()) > 0)
        {
            door_commands = obj->query_pass_command();
            exits += ({ obj->query_other_room(), door_commands[0], 0 });
            break;
        }
    }
    
    return exits;
}

/*
 * Function name: find_path
 * 
 * This function uses Dijkstra's algorithm to determine the
 * shortest path between two rooms.
 * 
 * Arguments  : startroom - the path to the starting room
 *              endroom - the path to the ending room
 * Returns   :  an array of strings containing the directions
 *              to walk in order to reach the end room.
 *              
 */
public mixed find_path(string startroom,string endroom)
{
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

    /* This is the mapping of rooms of the form:
     *
     * room path : cost, (fatigue units)
     *             direction to get here, (eg. southwest)
     *             room to get here, (/room/chapel)
     *             not yet final (1=incomplete, 0=final)
     *
     */
    mapping nodes;
    
    // List of filenames to process
    string * rooms_to_check;

    nodes = ([ startroom : ({ 0, "", "", 1 }) ]);
    rooms_to_check = ({ startroom });
    
    while (sizeof(rooms_to_check))
    {
        /* First we find the shortest node on our todo list */
        string current_node = rooms_to_check[0];
        int node_cost = nodes[current_node][0];

        for (int i=0;i<sizeof(rooms_to_check);i++)
        {
          if (nodes[rooms_to_check[i]][0] < node_cost)
          {
            current_node = rooms_to_check[i];
            node_cost=nodes[current_node][0];
          }
        }
        
        /* Take it off our todo list, and make sure it looks valid */
        rooms_to_check -= ({ current_node });
        nodes[current_node][3]=0;

        if (!current_node || !validate_room(current_node))
          continue;
          
        //This is already cheapest, let's cut out unused some effort.  
        if (current_node==endroom)
          break;
            
        mixed exits = get_room_exits(current_node);
        if (!exits)
          continue;
        
        /* Now to go through the exits, updating paths as needed */          
        for (int i=0;i<sizeof(exits);i+=3)
        {
            int exit_cost=node_cost + current_node->query_tired_exit(i/3);

            /* If too expensive, ignore it */
            if (exit_cost>MAX_PATHFIND_DISTANCE)
              continue;
              
            /* Allow our file to restrict pathfinding to specific paths
             * or rooms 
            */  
            if (!is_valid_room(exits[i]))
              continue;
             
            mixed to_node = nodes[exits[i]];
            
            /* If new room, add it to our lists.  If old, update only if
               we found a new shorter path */
            if (!to_node)
            {
                to_node = ({ exit_cost , exits[i+1], current_node, 0 });
                nodes +=([ exits[i] : to_node ]);
                rooms_to_check += ({ exits[i] });
            }
            else
            {
                /* Don't update finished nodes, and don't update if the
                new path is longer than our best so far */
                if ((to_node[0]<exit_cost) && to_node[3])
                {
                   nodes[exits[i]] = ({ exit_cost,exits[i+1], 
                    current_node,1 });
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

    while (endroom!=startroom)
    {
        mixed current_node = nodes[endroom];
        
        //Each direction goes to the front of the list
        dirs = ({ current_node[1], current_node[2] }) + dirs;
        endroom = current_node[2];
    }
    
    return dirs;   
    
}

