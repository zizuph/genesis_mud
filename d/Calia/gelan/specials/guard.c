/* 	this is a special file of the town Gelan

    coder(s):   Merlin

    history:    26. 3.93    changed goto_room for dummy     Merlin
                20. 2.93    removed error                   Merlin
                10. 2.93    some corrections                Merlin
                14. 1.93    created                         Merlin

    purpose:	path server for guard system

    to do:      none
    bug:        none known
*/

#include "specials.h"
#include GUARD_INCLUDE

#define NEXT_MEETING    0
#define MEETING         1
#define NEXT_ROOM       2
#define DUMMY           ":-)"                   /* not used as a command ! */

/* prototypes */
string extract_filename(string path);

#include "room_mapping.h"

/*
 * Function name: nearest_meeting_point
 * Description:   return the nearest meeting point
 * Arguments:     room id
 * Returns:       meeting point number
 */

int
nearest_meeting_point(string roomid)
{
    roomid = extract_filename(roomid);

    return rooms[roomid][NEXT_MEETING];
}



/*
 * Function name: next_room
 * Description:   gives direction of next room
 * Arguments:     meeting point, source room id, destination room id
 * Returns:       string for direction
 *
 * Explanation: Given the nearest meeting point 
 *              (0 south mp, 1 - west mp, 2 - east mp, 3 - north mp) 
 *              the source room id and the destination room id, return the 
 *              direction to proceed in. This will either be towards 
 *              a meeting point (on the first leg of the journey) or 
 *              towards the destination (on the second leg of the journey).
 *                                                            Maniac
 */

string
goto_room(int meeting, string source, string destination)
{

    source = extract_filename(source);
    destination = extract_filename(destination);

    if(source == destination)
        return 0;

    if(!rooms[source])
        return 0;

    if(rooms[source][NEXT_ROOM][destination])
        if(rooms[source][NEXT_ROOM][destination] == DUMMY)
            return 0;
        else
            return rooms[source][NEXT_ROOM][destination];
    else
        return rooms[source][MEETING][meeting];
}



/*
 * Function name: extract_filename
 * Description:   splits the filename from a full path
 * Arguments:     string with path
 * Returns:       string with filename
 */

string
extract_filename(string path)
{
    string * strs;

    if(!path)
        return 0;

    strs = explode(path,"/");

    return strs[sizeof(strs)-1];
}

