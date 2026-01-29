/*
 * Elemental School of Gelan
 *
 * This room will contain the base elements that will be a part of
 * every room in the school that is in Gelan
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include "defs.h"

inherit ROOM_OBJECT;
inherit "/d/Calia/lib/room_tell";

// Prototypes
public void create_school_room();
public int  try_item(mixed names, mixed desc);

/*
 * Function:    create_room
 * Description: Set up defaults for the temple room
 */
public nomask void
create_room()
{
    // Put default properties here before calling create_school_room
    // so that create_school_room can override any defaults
    set_short("A bare room");
    set_long("This is a bare room in the Elemental School of Gelan.\n"); 

    try_item( ({ "academy", "gelan academy", "gelan academy of elemental arts",
                 "academy of elemental arts" }),
                 "The Academy is a serene place where one can train in the "
               + "blessed Arts of Elemental channeling. This part of the "
               + "Gelan School is constructed mostly from white marble "
               + "imported from the quarries of Argos.\n");                     
    
    try_item( ({ "marble" }),
                 "Most of the Academy is constructed from finely hewn marble "
               + "that came from the quarries of Argos. The marble is "
               + "brilliantly white, giving the entire place a very serene "
               + "feel.\n");
               
    try_item( ({ "ground", "floor" }),
                 "The floor beneath you is constructed of finely hewn "
               + "marble.\n");
    
    try_item( ({ "ceiling" }),
                 "You glance up at the ceiling and realize that it is "
               + "no ordinary ceiling. Above you is a high ceiling, with "
               + "beautiful fresco paintings, meticulously drawn.\n");
    
    try_item( ({ "fresco paintings", "paintings", "painting",
                 "frescoes" }),
                 "The fresco paintings depict the Elementals of Calia "
               + "in various scenes, both awesome and terrifying.\n");
               
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "The Academy is a peaceful place! There will "
        + "be no combat upon the school grounds.\n");
        
    // Call each room's create_school_room
    create_school_room();
}

/*
 * Function:    create_school_room
 * Description: This method should be masked and defined in each
 *              school room to override defaults set in create_room
 */
public void
create_school_room()
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
