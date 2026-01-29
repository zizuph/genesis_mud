/*
 * Undead Maker
 *
 * This undead maker clones undead monsters and configures
 * them for use in the game.
 *
 * Created by Petros, November 2008
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define TUNNEL_NPCS     "/d/Calia/eldoral/tunnel/npcs/"

// Global Variables
public mapping      avail_undeads = ([
    "skeleton" : TUNNEL_NPCS + "skeleton",
    "zombie"   : TUNNEL_NPCS + "zombie",
    "banshee"  : TUNNEL_NPCS + "banshee",
    "heucuva"  : TUNNEL_NPCS + "heucuva",
    "ghoul"    : TUNNEL_NPCS + "ghoul",
    "wraith"   : TUNNEL_NPCS + "wraith",
    "devourer" : TUNNEL_NPCS + "devourer",
]);

// The create function is called for every object. We mask it here
// to do some basic initialization for the maker
public void
create()
{
    
}

public varargs object
clone_undead(string race, int level = 0)
{
    object npc;
    
    if (!IN_ARRAY(race, m_indices(avail_undeads)))
    {
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    npc = clone_object(avail_undeads[race]);
    if (objectp(npc) && level)
    {
        npc->default_config_undead(level);
    }
    
    return npc;
}
