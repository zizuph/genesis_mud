/*
 * Dwarven Rockfriends Guild module for Guild testing
 * 
 * Created by Petros, April 2010
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define GUILD_OBJ       "/d/Gondor/common/dwarf_guild/belt"
#define GUILD_OBJ_NAME  "_dwarven_race_guild_belt"

public string *
query_guild_shadows_rockfriend()
{
    return ({ "/d/Gondor/common/dwarf_guild/dwarf_shadow" });
}

public string *
query_guild_souls_rockfriend()
{
    return ({ "/d/Gondor/common/dwarf_guild/dwarf_soul" });
}

public mapping
query_guild_skills_rockfriend()
{
    return ([ 
              ]);              
}

public int
start_guild_rockfriend(object player)
{
    if (!present(GUILD_OBJ_NAME, player))
    {
        setuid();
        seteuid(getuid());
        object belt_obj = clone_object(GUILD_OBJ);
        belt_obj->move(player, 1);
        belt_obj->set_owner_name(player->query_real_name());
        player->catch_tell("You are now a Rockfriend. You must wear the belt "
            + "to get the full benefits.\n");
    }
    return 1;
}

public int
stop_guild_rockfriend(object player)
{
    object guild_obj;
    
    if (objectp(guild_obj = present(GUILD_OBJ_NAME, player)))
    {
        guild_obj->remove_object();
    }
    
    return 1;
}
