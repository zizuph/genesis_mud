/*
 * Exit Manager
 *
 * This manager handles the loading of exits for the underground
 * rooms.
 *
 * Created by Petros, April 2009
 */
 
#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <filepath.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

mixed * edges = 
    ({
        // Tunnel #1
        ({ ({ 2, 1 }), ({ 1, 2 }) }),
        ({ ({ 1, 2 }), ({ 2, 3 }) }),
        ({ ({ 2, 3 }), ({ 3, 3 }) }),
        ({ ({ 3, 3 }), ({ 2, 4 }) }),
        ({ ({ 2, 4 }), ({ 3, 4 }) }),
        ({ ({ 3, 4 }), ({ 2, 5 }) }),
        ({ ({ 2, 5 }), ({ 1, 6 }) }),
        ({ ({ 1, 6 }), ({ 1, 7 }) }),
        ({ ({ 1, 7 }), ({ 2, 7 }) }),
        ({ ({ 2, 7 }), ({ 3, 6 }) }),
        ({ ({ 3, 6 }), ({ 4, 6 }) }),
        ({ ({ 2, 7 }), ({ 3, 8 }) }),
        ({ ({ 3, 8 }), ({ 3, 9 }) }),
        ({ ({ 1, 7 }), ({ 1, 8 }) }),
        ({ ({ 1, 8 }), ({ 1, 9 }) }),
        ({ ({ 1, 9 }), ({ 1, 10 }) }),
        ({ ({ 1, 10 }), ({ 2, 10 }) }),
        ({ ({ 2, 10 }), ({ 2, 9 }) }),
        ({ ({ 1, 10 }), ({ 1, 11 }) }),
        ({ ({ 1, 11 }), ({ 2, 11 }) }),
        ({ ({ 2, 11 }), ({ 3, 11 }) }),
//        ({ ({ 3, 11 }), ({ 4, 11 }) }), // Gate #1
        ({ ({ 4, 11 }), ({ 5, 11 }) }),
        ({ ({ 5, 11 }), ({ 6, 11 }) }),
        ({ ({ 6, 11 }), ({ 7, 11 }) }),
        ({ ({ 7, 11 }), ({ 7, 12 }) }),
//      ({ ({ 7, 12 }), ({ 7, 13 }) }), // Gate #4        
        // Tunnel #2
        ({ ({ 5, 4 }), ({ 4, 5 }) }),
        ({ ({ 4, 5 }), ({ 5, 6 }) }),
        ({ ({ 5, 6 }), ({ 6, 5 }) }),
        ({ ({ 6, 5 }), ({ 7, 5 }) }),
        ({ ({ 7, 5 }), ({ 7, 6 }) }),
        ({ ({ 7, 6 }), ({ 7, 7 }) }),
        ({ ({ 7, 7 }), ({ 8, 6 }) }),
        ({ ({ 8, 6 }), ({ 9, 6 }) }),
        ({ ({ 5, 6 }), ({ 4, 7 }) }),
        ({ ({ 4, 7 }), ({ 4, 8 }) }),
        ({ ({ 4, 8 }), ({ 5, 8 }) }),
        ({ ({ 5, 8 }), ({ 6, 9 }) }),
//        ({ ({ 6, 9 }), ({ 6, 10 }) }), // Gate #2
        ({ ({ 6, 10 }), ({ 5, 10 }) }),
        ({ ({ 5, 10 }), ({ 4, 11 }) }),
        ({ ({ 6, 9 }), ({ 7, 8 }) }),
        ({ ({ 7, 8 }), ({ 6, 7 }) }),
        // Tunnel #3
        ({ ({ 14, 9 }), ({ 14, 8 }) }),
        ({ ({ 14, 8 }), ({ 13, 8 }) }),                    
        ({ ({ 13, 8 }), ({ 13, 9 }) }),
        ({ ({ 13, 9 }), ({ 13, 10 }) }),
        ({ ({ 13, 10 }), ({ 12, 10 }) }),
        ({ ({ 12, 10 }), ({ 11, 11 }) }),
        ({ ({ 11, 11 }), ({ 10, 11 }) }),
        ({ ({ 10, 11 }), ({ 9, 10 }) }),
//        ({ ({ 9, 10 }), ({ 8, 11 }) }), // Gate #3
        ({ ({ 8, 11 }), ({ 7, 12 }) }),
        ({ ({ 9, 10 }), ({ 9, 9 }) }),
        ({ ({ 9, 9 }), ({ 10, 9 }) }),
        ({ ({ 10, 9 }), ({ 11, 9 }) }),
        ({ ({ 11, 9 }), ({ 11, 10 }) }),
        ({ ({ 11, 10 }), ({ 12, 9 }) }),
        ({ ({ 9, 9 }), ({ 8, 9 }) }),
        ({ ({ 8, 9 }), ({ 8, 10 }) }),
        ({ ({ 8, 10 }), ({ 7, 10 }) }),
        ({ ({ 8, 9 }), ({ 9, 8 }) }),
        ({ ({ 9, 8 }), ({ 8, 8 }) }),
        ({ ({ 9, 8 }), ({ 9, 7 }) }),
        ({ ({ 9, 8 }), ({ 10, 8 }) }),
        ({ ({ 10, 8 }), ({ 10, 7 }) }),
       
    });

/*
 * Function:    find_adjacent_rooms
 * Description: Given a room coordinate, it looks through the
 *              edges to find all the adajacent rooms. This
 *              returns an array of room coordinates
 */
public mixed *
find_adjacent_rooms(int * coordinate)
{
    mixed * rooms = ({ });
    
    if (sizeof(coordinate) != 2)
    {
        return rooms;
    }
    
    foreach (mixed * edge : edges)
    {
        if (edge[0][0] == coordinate[0] 
            && edge[0][1] == coordinate[1])
        {
            rooms += ({ edge[1] });
        }
        else if (edge[1][0] == coordinate[0]
                 && edge[1][1] == coordinate[1])
        {
            rooms += ({ edge[0] });
        }
    }

    return rooms;
}

/* 
 * Function:    get_direction
 * Description: returns the direction that should be used from the
 *              source to the destination. It uses the coordinate
 *              system to determine the direction.
 */
public string
get_direction(int * source, int * destination)
{
    string xdesc, ydesc;
    
    xdesc = "";
    ydesc = "";
    if (source[0] > destination[0])
    {
        xdesc = "west";
    }
    else if (source[0] < destination[0])
    {
        xdesc = "east";
    }
    
    if (source[1] > destination[1])
    {
        ydesc = "north";
    }
    else if (source[1] < destination[1])
    {
        ydesc = "south";
    }
    
    return ydesc + xdesc;       
}

/*
 * Function:    load_exits
 * Description: This takes in a room file and sees if it can
 *              find exits for it. It goes ahead and directly
 *              adds the exits for those that it finds.
 */
public void
load_exits(object room)
{
    string filename, path;
    int xCoord, yCoord;
    
    path = FILE_PATH(MASTER_OB(room));
    filename = FILE_NAME(MASTER_OB(room));
    if (sscanf(filename, "undergrnd%d_%d", xCoord, yCoord) != 2)
    {
        send_debug_message("underground_exits", "did not parse "
            + "filename " + filename + " correctly.");
        return;
    }
    
    mixed * rooms = find_adjacent_rooms( ({ xCoord, yCoord }) );
    foreach (int * coordinate : rooms)
    {
        string direction = get_direction( ({ xCoord, yCoord }), coordinate );
        string otherfile = sprintf("undergrnd%:02d_%:02d", 
                                   coordinate[0], coordinate[1]);
        room->add_exit(path + otherfile, direction, 0);
        send_debug_message("underground_exits", "Exit added to room "
            + filename + " at the " + direction + " exit to the room "
            + otherfile + ".");                                          
    }
}
