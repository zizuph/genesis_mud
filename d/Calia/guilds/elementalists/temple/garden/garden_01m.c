/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "../defs.h"

inherit GARDEN_ROOM_BASE;

// Defines

// Prototypes

public void
create_garden_room()
{
    try_item( ({ "northeast" }),
        "It looks like you can go northeast from here where there is "
      + "a pretty open lawn.\n");
    
    try_item( ({ "wall" }),
        "The wall here continues to the west, south, and northeast.\n");
    
    try_item( ({ "lawn", "open lawn", "flat area", "area" }),
        "You can't make out too many details from here, but it does appear "
      + "that a pretty open lawn lies to the northeast from here. It looks "
      + "fairly inviting.\n");
    
    add_exit(ELEMENTALIST_GARDEN + "garden_01l", "west");
    add_exit(ELEMENTALIST_GARDEN + "garden_02m", "south");
    add_exit(ELEMENTALIST_GARDEN + "diabrecho_g", "northeast");
}

/*
 * Function:    describe_long
 * Description: VBFC function to provide the long description
 */
public string
describe_long()
{
    string description = ::describe_long();
    // Remove the newlines that are put by default by the base class
    description = description[..-3];
    // Now add our own description here
    description += " The wall makes a turn to the northeast, where you "
        + "spot a pretty flat area with an open lawn.\n\n";
    return description;
}
