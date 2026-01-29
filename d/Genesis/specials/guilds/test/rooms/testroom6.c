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
set_opponent_files()
{
    opponent_one = "/d/Genesis/specials/guilds/test/npcs/test_knight_bm";
    opponent_two = "/d/Genesis/specials/guilds/test/npcs/test_aa_bg";
}

public void
create_room()
{
    ::create_room();
    
    add_exit("/d/Genesis/specials/guilds/test/rooms/testroom5", "west");        
}
