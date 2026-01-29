/*
 * Spirit Circle of Psuchae module for Guild testing
 * 
 * Created by Petros, March 2009
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
query_guild_shadows_scop()
{
    return ({ "/d/Calia/guilds/scop/specials/spiritshadow",
             "/d/Calia/guilds/scop/specials/spiritlayshadow" });
}

public string *
query_guild_souls_scop()
{
    return ({ "/d/Calia/guilds/scop/specials/spiritsoul",
              "/d/Calia/guilds/scop/specials/spiritlaysoul" });
}

public mapping
query_guild_skills_scop()
{
    return ([ 
                SS_ELEMENT_LIFE     :   60, 
                SS_SPELLCRAFT       :   90,
                SS_DEFENCE          :   80,
                SS_WEP_CLUB         :   75,
                SS_AWARENESS        :   60,
                SS_HERBALISM        :   70,
                SS_FORM_DIVINATION  :   80,
                SS_FORM_TRANSMUTATION   : 80,
                SS_FORM_ENCHANTMENT :   60,
                SS_FORM_CONJURATION :   60,
                SS_TRADING          :   60,
                SS_PARRY            :   50,
                SS_LANGUAGE         :   60,
                SS_APPR_VAL         :   60,
                114021              :   100, // spirit spells
              ]);       
}

public void
remove_action_limiter(object player)
{
    object limiter;
    
    if (objectp(limiter = present("_spirit_action_limiter_", player)))
    {
        limiter->remove_object();
    }
    player->remove_prop(LIVE_M_MOUTH_BLOCKED);        
}

public void
add_spells(object player)
{
    object spellbook;

    player->set_skill(114023, 0xFF);
    
    setuid();
    seteuid(getuid());
    spellbook = clone_object("/d/Calia/guilds/scop/objects/apprentice_spells");
    spellbook->move(player, 1);
    spellbook->update_first_spells();
    spellbook->update_second_spells();
    spellbook->update_third_spells();
    spellbook = clone_object("/d/Calia/guilds/scop/objects/master_spells");
    spellbook->move(player, 1);
    spellbook->update_fourth_spells();
    spellbook->update_fifth_spells();
    spellbook->update_sixth_spells();
    spellbook->update_seventh_spells();
    spellbook = clone_object("/d/Calia/guilds/scop/objects/elder_spells");
    spellbook->move(player, 1);
    spellbook->update_eighth_spells();    
}

public int
start_guild_scop(object player)
{
    set_alarm(5.0, 0.0, &remove_action_limiter(player));
//    set_alarm(5.0, 0.0, &add_spells(player));
    return 1;
}

public int
stop_guild_scop(object player)
{
    object spellbook;
    
    remove_action_limiter(player);
    if (objectp(spellbook = present("_spirit_elder_spells_", player)))
    {
        spellbook->remove_object();
    }
    if (objectp(spellbook = present("_spirit_master_spells_", player)))
    {
        spellbook->remove_object();
    }
    if (objectp(spellbook = present("_spirit_apprentice_spells_", player)))
    {
        spellbook->remove_object();
    }
    return 1;
}
