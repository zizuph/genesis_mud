/*
 * Old Elemental Worshippers of Calia module for Guild testing
 * 
 * Created by Petros, March 2013
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

#include "/d/Calia/worshippers/specials/worshipper.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

public string *
query_guild_shadows_worshipper_old()
{
    return ({ "/d/Calia/worshippers/specials/worshipshadow" });
}

public string *
query_guild_souls_worshipper_old()
{
    return ({ "/d/Calia/worshippers/specials/worshipsoul" });
}

public mapping
query_guild_skills_worshipper_old()
{
    return ([ 
        SS_CARVED   : WATER_FLAG | FIRE_FLAG | EARTH_FLAG | AIR_FLAG,
        SS_PATRON_ELEMENTAL : FIRE_FLAG,
              ]);              
}

public int
start_guild_worshipper_old(object player)
{
    
    setuid();
    seteuid(getuid());
    
    // Add the guild object, and the 4 spell objects
    clone_object("/d/Calia/worshippers/objects/pentacle")->move(player);
    clone_object("/d/Calia/worshippers/objects/wand")->move(player);
    clone_object("/d/Calia/worshippers/objects/chalice")->move(player);
    clone_object("/d/Calia/worshippers/objects/dagger")->move(player);
    clone_object("/d/Calia/worshippers/objects/sceptre")->move(player);
    
    return 1;
}

public int
stop_guild_worshipper_old(object player)
{
    present("worshipper_chalice", player)->remove_object();
    present("worshipper_wand", player)->remove_object();
    present("worshipper_dagger", player)->remove_object();
    present("worshipper_sceptre", player)->remove_object();
    present("worshipper_pentacle", player)->remove_object();
    
    return 1;
}
