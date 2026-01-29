/*
 * City of Gelan Base Room
 *
 * This room will contain the base elements that will be a part of
 * every room in the city of Gelan
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include "defs.h"

inherit ROOM_OBJECT;

// Prototypes
public void create_gelan_room();
public int  try_item(mixed names, mixed desc);

/*
 * Function:    create_room
 * Description: Set up defaults for the room
 */
public nomask void
create_room()
{
    // Put default properties here before calling create_gelan_room
    // so that create_gelan_room can override any defaults
    set_short("A bare room");
    set_long("This is a bare room in the city of Gelan.\n"); 
               
    add_prop(ROOM_S_MAP_FILE, "gelan_map.txt");
    
    // Call each room's create_gelan_room
    create_gelan_room();
}

/*
 * Function:    create_gelan_room
 * Description: This method should be masked and defined in each
 *              room to override defaults set in create_room
 */
public void
create_gelan_room()
{
    // Define this in your own room
}

/*
 * Function:    try_item
 * Description: checks to see if an item already exists within a given object, 
 *              and if it does not, it then adds it as add_item() would.                
 * Arguments:   mixed names - string or array of strings, the
 *                            item name(s).
 *              mixed desc  - string or function, the description.
 * Returns:     int - the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         items_added;
    string      *exists;

    items_added = 0;
    if (pointerp(names)) 
    { 
        exists = ({});
        foreach (string name : names)
        {
            if (item_id(name)) 
            {
                exists += ({ name });
            }
        }
        names -= exists;
        if (sizeof(names))
        {
            add_item(names, desc);
        }
        items_added = sizeof(names);
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        items_added = 1;
    }
    return items_added;
}
