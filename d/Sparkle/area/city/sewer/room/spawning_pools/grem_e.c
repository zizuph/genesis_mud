/*
 *  /w/aeg/sparkle/sewer/spawning_pools/grem_e.c
 *
 *  This is the east room for the gremlin spawning pools.
 *
 *  Created FEB 22 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

/* Includes */
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */

/* Inheritance */
inherit SEWER_ROOM_BASE;

/* Global Variables */

/* Prototypes */
public void             init();
public void             create_sewer_room();

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} // init

/* 
 * Function name:       create_sewer_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sewer_room()
{
    // Descriptions Section
    set_short("Spawning pool in the sewer");
    set_long("These sewers appear to be tainted more than normal. Someone, "
           + "or something, has crafted dams of rubbish and debris to "
           + "block the flow of the sewage, creating pools. The sewer water "
           + "has been made stagnant and appears to be heated by some "
           + "unknown source. The smell is unbearable."
           + "\n\n");
 
    // Room Item Section                              
                              
    // Properties Section
    add_prop(ROOM_S_MAP_FILE, "spawning_pools_map.txt");    

    
    // Exits Section
    add_exit(SPAWNING_POOLS + "grem_c", "west", 0);
    add_exit(SPAWNING_POOLS + "grem_n", "northwest", 0);
    /* add_exit(SPAWNING_POOLS + "grem_e_ne", "northeast", 0);
    add_exit(SPAWNING_POOLS + "grem_e_se", "southeast", 0);
    */ 
        
} // create_sewer_room

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    object spawn;
    int num_spawn;
    
    if (!present("gremlin")) {
        num_spawn = random(6) + 2;    
        for (int i = 0; i < num_spawn; ++i) {
            spawn = clone_object(SEWER_NPC_DIR + "gremlin_spawn");
            spawn->move(this_object());
        }
    }
} // reset_room

