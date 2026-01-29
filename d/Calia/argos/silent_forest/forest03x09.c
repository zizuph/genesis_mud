/*
 *   forest03x09.c
 * 
 * Forest location in silent forest.
 *
 * Baldacin@Genesis, Sep 2003
 */

#pragma strict_types

// I N C L U D E D   F I L E S
#include "ldefs.h"

inherit FORESTSTD;

// G L O B A L   V A R S

// P R O T O T Y P E S

// P R I V A T E   F U N C T I O N S

// P U B L I C   F U N C T I O N S

/*
 *  FUNCTION: create_room
 *  Arguments:
 *  Returns  :
 * 
 * Sets up the room, calls make_me_forest with proper
 * arguments to add descriptions.
 *
*/
public void
create_room()
{
    int loc_type, cliffs;
    string extra_long;
    
    // Location is forest.
    loc_type = MM_FOREST;
    // No cliffs here.
    cliffs = ADDCLIFF;
    // Add specifics to longdescription.
    extra_long = "To the northeast a small opening is visible in the cliff wall.";    
    add_item(({"opening", "cave"}), "On the northeast cliff wall the outlines of "+
      "a small opening is visible.\n");
    
    // There are cliffs. Give direction to them.                 
    set_cliff_dir("east and northeast");
    // Set description of exits.
    set_exit_desc(3, "northeast, south and west");
    
    make_me_forest(extra_long, loc_type, cliffs);
    
    add_exit(SFDIR + "cave04x10.c", "northeast", 0, FOREST_FATIGUE,
        EXITNOTOBVIOUS);
    add_exit(SFDIR + "forest03x08.c", "south", 0, FOREST_FATIGUE,
        EXITNOTOBVIOUS);
    add_exit(SFDIR + "forest02x09.c", "west", 0, FOREST_FATIGUE,
        EXITNOTOBVIOUS);
}

