/*
 * Priests of Takhisis module for Guild testing
 * 
 * Created by Petros, November 2011
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
#include "/d/Ansalon/guild/pot/guild.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public string *
query_guild_shadows_pot()
{
    return ({ "/d/Ansalon/guild/pot/shadow/occ_shadow" });
}

public string *
query_guild_souls_pot()
{
    return ({ "/d/Ansalon/guild/pot/soul/cmdsoul" });
}

public mapping
query_guild_skills_pot()
{
    return ([ 

              ]);              
}

public void
update_spells(object player)
{
    object medallion = present(MEDALLION_ID, player);
    if (objectp(medallion))
    {
        medallion->update_spells();
    }
    player->command("wear medallion");
}

public int
start_guild_pot(object player)
{
    // Add all the guild specific skills
    player->set_skill(PS_SPELLS, 0xFFFFFFFF);
    player->set_skill(PS_GUILD_LEVEL, 149);
    player->set_skill(PS_SKILL_POINTS, 30700);
    player->set_skill(PS_STANDING, 1199);
    
    set_alarm(5.0, 0.0, &update_spells(player));
    
    return 1;
}

public int
stop_guild_pot(object player)
{
    object medallion;
    if (objectp(medallion = present(MEDALLION_ID, player)))
    {
        medallion->remove_object();
    }
    return 1;
}
