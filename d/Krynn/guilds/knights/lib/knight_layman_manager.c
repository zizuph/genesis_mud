/*
 * Knight Layman Manager
 * 
 * This module keeps track of the laymans that are allowed by the
 * Knights of Solamnia.
 *
 * Created by Petros, November 2008
 */
 

#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../guild.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public string *     allowed_guilds = ({ });

// Defines
#define DATA        (KDATA + "allowed_laymans")

// Prototypes

                    
// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }
}

private int
is_impossible_layman(string name)
{
    // Certain layman guilds in the registry are not possible to even
    // join. This includes guilds like SCoP and Vampires which take up
    // more than one guild slot.
    switch (name)
    {
    case "cadet":
    case "cavalry":
    case "knight":
    case "pot":
    case "scop":
    case "vampire":
    case "vamps":
    case "mino": // can't be a minotaur knight
        return 1;
    }
    
    return 0;
}

private int
is_open_layman(string name)
{
    if ((SECURITY->query_guild_type(name) & G_LAYMAN)
        && SECURITY->query_guild_phase(name) == "open")
    {
        if (is_impossible_layman(name))
        {
            return 0;
        }
        return 1;
    }
    
    return 0;
}

private int
is_magic_layman(string name)
{
    if (SECURITY->query_guild_style(name) == "cleric"
        || SECURITY->query_guild_style(name) == "magic")
    {
        return 1;
    }
    
    return 0;
}

private int
is_thief_layman(string name)
{
    if (SECURITY->query_guild_style(name) == "thief")
    {
        return 1;
    }
    
    return 0;
}

private int
is_allowed_by_conclave(string name)
{
    if (IN_ARRAY(name, allowed_guilds))
    {
        return 1;
    }
    
    return 0;
}

public mapping
query_available_laymans()
{
    string * all_guilds, * avail_laymans;
    mapping results;
    
    setuid();
    seteuid(getuid());
    all_guilds = SECURITY->query_guilds();    
    avail_laymans = filter(all_guilds, is_open_layman);

    results = ([ ]);
    foreach (string guild : avail_laymans)
    {
        results[guild] = SECURITY->query_guild_long_name(guild);
    }
    return results;
}

public mapping
query_allowed_laymans()
{
    mapping results;
    
    setuid();
    seteuid(getuid());
    results = ([ ]);
    foreach (string guild : allowed_guilds)
    {
        results[guild] = SECURITY->query_guild_long_name(guild);
    }
    return results;
}

public mapping
query_restricted_laymans()
{
    string * avail_laymans;
    mapping results;
    
    setuid();
    seteuid(getuid());
    results = ([ ]);
    
    avail_laymans = m_indices(query_available_laymans());
    avail_laymans -= allowed_guilds;
    foreach (string guild : avail_laymans)
    {
        results[guild] = SECURITY->query_guild_long_name(guild);
    }
    return results;
}

public int
add_allowed_layman(string name)
{
    if (IN_ARRAY(name, allowed_guilds))
    {
        // Guild has already been added
        return 0;
    }

/*  Commented out to allow testing of guilds in development

    if (!is_open_layman(name))
    {
        // Can't add something that's not open.
        return 0;
    }
*/
    
    allowed_guilds += ({ name });
    setuid();
    seteuid(getuid());
    save_object(DATA);
    return 1;
}

public int
remove_allowed_layman(string name)
{
    if (!IN_ARRAY(name, allowed_guilds))
    {
        // Guild has already been removed
        return 0;
    }

    allowed_guilds -= ({ name });
    setuid();
    seteuid(getuid());
    save_object(DATA);
    return 1;
}