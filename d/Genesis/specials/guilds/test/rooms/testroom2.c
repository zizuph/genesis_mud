/*
 * Test Room
 *
 * Create test npcs here and have them fight each other.
 * Can specify multiple battles at once.
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
 
inherit "/d/Genesis/specials/guilds/test/rooms/testroom_base";

public void
create_room()
{
    ::create_room();
    
    add_exit("/d/Genesis/specials/guilds/test/rooms/testroom3", "east");        
    add_exit("/d/Genesis/specials/guilds/test/rooms/testroom1", "west");        
}
