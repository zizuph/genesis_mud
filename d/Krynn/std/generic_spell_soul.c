/*
 * Common spell soul for monsters and npcs.
 *
 * Add spells you want your npc to cast to the cmdlist 
 * below, then in the npc's create_krynn_monster 
 * function add:
 *
 *  clone_object("/d/Genesis/specials/guilds/shadows/mana_shadow")->shadow_me(TO);
 *  add_cmdsoul("/d/Krynn/std/generic_spell_soul");
 *  add_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");
 *  update_hooks(); 
 *
 *  In the creature's special_attack function simply add 
 *  the spell casting name as a command (i.e. command("toxicblast"); )
 *
 * Npcs will then cast spells like a player.
 *
 * Example npc can be found at:
 *   /d/Krynn/turbidus_ocean/living/sahuagin_priestess.c
 *
 * Created by Arman, November 2020
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#define SOHM_SPELLS "/d/Krynn/guilds/sohm/spells/"

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return "Generic Krynn Npc Spell Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}
  
public mapping
query_cmdlist()
{
    return ([
        // aurak npc spells not available to players
        "aurakdisarm"       : "do_ability",
        "aurakfire"         : "do_ability",
        // sahuagin npc spells not available to players
        "toxicblast"        : "do_ability",
        // triton npc spells not available to players
        "steamblast"        : "do_ability",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "aurakdisarm"      : SOHM_SPELLS + "aurak_disarm_spell",
        "aurakfire"        : SOHM_SPELLS + "aurak_flame_spell",
        "toxicblast"       : "/d/Krynn/turbidus_ocean/spells/priestess_toxic_blast",
        "steamblast"       : "/d/Krynn/south_courrain/living/titan_steam_blast",

    ]);
}
