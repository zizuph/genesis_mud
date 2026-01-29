/*
 * Base Pier Object
 *
 * Inherit this to provide basic ship start/restart functionality
 * to the room. Ship controller objects can call piers to have them
 * restart their own ships.
 *
 * Created by Petros, March 2009
 */
 
#pragma strict_types

#include "ship.h"

// Variables
private string  Ship_file;

/*
 * Function:    set_ship_line
 * Description: This should be called by each pier to indicate
 *              the details of the Ship Line. The shipfile indicates
 *              what ship this pier creates.
 */
public int
set_ship_line(string short_desc, string shipfile, string long_desc)
{
    if (wildmatch("*.c", shipfile))
    {
        shipfile = shipfile[..-3]; // remove the .c
    }
    
    Ship_file = shipfile;
    
    return SHIP_CONTROL_ROOM->set_ship_line(short_desc, shipfile, long_desc);
}

/* 
 * Function:    query_ship_file
 * Description: Mask this function to specify which ship
 *              this particular pier handles.
 */
public string
query_ship_file()
{
    return Ship_file;    
}

/*
 * Function:    is_controllable_pier
 * Description: Indicates whether this pier room can be controlled
 *              so that start_ship can be called on it.
 */
public int
is_controllable_pier()
{
    return 1;
}

/*
 * Function:    start_ship
 * Description: This function checks for existing ships. If there is
 *              already one, it does nothing. If there are no
 *              existing ships, it will go ahead and clone it and
 *              start it.
 * Arguments:   bRestart - Set this to true if you want it to destroy
 *                         existing ships and start a new one.
 * Returns:     0/1 - failure/success
 */
public int
start_ship(int bRestart = 0)
{
    setuid();
    seteuid(getuid());
    
    return SHIP_CONTROL_ROOM->start_ship(this_object(), bRestart);
}


