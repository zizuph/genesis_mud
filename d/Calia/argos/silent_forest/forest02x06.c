/*
 * forest02x06.c
 *
 * Forest location in silent forest.
 *
 * Copyright (C): Tianar, Jul 2003
 *
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
    cliffs = NOCLIFF;
    // Add specifics to longdescription.
    extra_long = "";
    // Set description of exits.
    set_exit_desc(2, "north and northwest");
    
    make_me_forest(extra_long, loc_type, cliffs);
    
    add_exit(SFDIR + "forest02x07.c", "north", 0, FOREST_FATIGUE,
        EXITNOTOBVIOUS);
    add_exit(SFDIR + "forest01x07.c", "northwest", 0, FOREST_FATIGUE,
        EXITNOTOBVIOUS);
}
