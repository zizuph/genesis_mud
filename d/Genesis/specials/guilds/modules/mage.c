/*
 * Morgul Mages module for Guild testing
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

public string *
query_guild_shadows_mage()
{
    return ({ "/d/Gondor/guilds/morgulmage/morgul_shadow",
              "/d/Genesis/specials/guilds/shadows/mana_shadow",
           });
}

public string *
query_guild_souls_mage()
{
    return ({ "/d/Gondor/guilds/morgulmage/morgul_soul", 
              "/d/Gondor/guilds/morgulmage/morgul_spells", 
              "/d/Genesis/specials/guilds/souls/spell_manager_soul" });
}

public mapping
query_guild_skills_mage()
{
    return ([ 
                SS_WEP_SWORD      : 50,
                SS_WEP_SWORD      :   50,    
                SS_BLIND_COMBAT   :   20,
                SS_DEFENCE        :   65,
                SS_ACROBAT        :   20,
                SS_SPELLCRAFT     :   100,
                SS_ELEMENT_DEATH  :   100,
                SS_ELEMENT_AIR    :   85,
                SS_ELEMENT_FIRE   :   90,
                SS_FORM_ILLUSION  :   85,
                SS_FORM_CONJURATION  :   90,
                SS_FORM_ENCHANTMENT  :   80,
                SS_FORM_ABJURATION   :   75,
                SS_AWARENESS   :   50,
              
              ]);              
}

public void
use_new_spells(object player)
{
    player->set_using_original_spells(0);
}

public int
start_guild_mage(object player)
{
    setuid();
    seteuid(getuid());
    
    set_alarm(1.0, 0.0, &use_new_spells(player));
    return 1;
}

public int
stop_guild_mage(object player)
{
    return 1;
}
