/*
 * Priests of Takhisis (New)
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

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Ansalon/guild/new_pot/guild.h"


public string *
query_guild_shadows_pot_new()
{
    return ({ "/d/Ansalon/guild/new_pot/shadow/occ_shadow" });
}

public string *
query_guild_souls_pot_new()
{
    return ({ "/d/Ansalon/guild/new_pot/soul/cmdsoul", 
              "/d/Ansalon/guild/new_pot/soul/help",
              "/d/Ansalon/guild/new_pot/soul/standing",
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_pot_new()
{
    return ([ 
              ]);              
}

public void update_medallion(object player)
{
    present(MEDALLION_ID, player)->update_spells();
}


public int
start_guild_pot_new(object player)
{
    setuid();
    seteuid(getuid());
    player->set_alignment(-1200);

    // Add all the guild specific skills
    player->set_skill(PS_SPELLS, 0xFFFFFFFF);
    player->set_skill(PS_GUILD_LEVEL, 149);
    player->set_skill(PS_SKILL_POINTS, 30700);
    player->set_skill(PS_STANDING, 1199);
    player->add_prop(DARK_LADY_ASPECT, 1);
    set_alarm(4.0, 0.0, &update_medallion(player));
    return 1;
}

public int
stop_guild_pot_new_old(object player)
{
    setuid();
    seteuid(getuid());
    
    return 1;
}
