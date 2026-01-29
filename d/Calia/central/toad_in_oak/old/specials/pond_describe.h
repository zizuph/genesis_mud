/*
 * /d/Calia/central/toad_in_oak/specials/pond_describe.h 
 *
 * This is a function for describing the pond. Eventually this will
 * include listing what animals (ducks, toads) are on the pond at 
 * the moment. 
 *
 * HISTORY: [99-03-04] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS 

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "defs.h"

//FORWARD FUNCTION DECLARATIONS

string pond_describe();
string pond_contents();


//FUNCTIONS

/*
 * Function name: pond_describe
 * Description:   Describes the Toad-in-Oak duck pond, including
 *                any ducks currently on it. 
 * Arguments:     None.
 * Returns:       string describing the pond
 */
string
pond_describe()
{
  
    return "The stream that flows through the village has formed " +
        "a small pond here. The water looks to be a little muddy " +
        "as if something had been stirring up the mud at the " + 
        "bottom." + pond_contents() + "\n"; 
}

/*
 * Function name: pond_contents
 * Description:   Describes what's currently swimming around on the pond
 * Arguments:     None.
 * Returns:       string describing the contents
 */
string
pond_contents()
{
    object pond = find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    object *living_things; 
    string contents = "";     
    
    if (pond != 0)
    {
        
        living_things = FILTER_LIVE(all_inventory(pond)); 
        if (sizeof(living_things)) 
        {
            contents = " You can see " + COMPOSITE_ALL_LIVE(living_things) + 
                " on the surface of the pond."; 
        }
        
    }
    else
    {
        contents = " Something seems to be terribly wrong with the pond. " + 
            "You'd better call in a pond repairman."; 
    }

    return contents; 
}


    

