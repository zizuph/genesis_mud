/*
 * Mana Shadow for Magic User Guilds
 * 
 * In order to facilitate incremental changes to the magic system
 * while we recode the magic guilds in Genesis, this shadow has
 * been created to match some of our expectations for what the
 * final product will look like in Genesis. Primarily this shadow
 * changes the mana pool and regeneration rate for those who are
 * in these new guilds.
 *
 * This shadow also handles proper handling of the spell objects
 * for use in the "cast" and "spells" commands.
 *
 * Created by Petros, August 2009
 *
 * Feb 2021 - Zizuph.  Fallthrough cleanly if an ability cannot be loaded.
 *
 */

#pragma strict_types

inherit "/std/shadow";

#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"


#include "/d/Genesis/specials/local.h"
inherit RESOURCE_LIB;

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include <gmcp.h>
#include <state_desc.h>

// Defines
#define     SPELL_MANAGER_SOUL          "/d/Genesis/specials/guilds/souls/spell_manager_soul"

/*
 * Function:    has_mana_shadow
 * Description: When someone has this shadow, this function will return
 *              true.
 */
public int
has_mana_shadow()
{
    return 1;
}

/*
 * Function:    remove_mana_shadow
 * Description: Shadows are hard to remove by calling them directly. We
 *              need this function so that we can target a specific one.
 */
public void
remove_mana_shadow()
{
    remove_shadow();
}

/*
 * Function:    find_spell
 * Description: This shadowed function should be called by the magic
 *              system and will correctly return the spell object
 *              that should be used.
 */
public object
find_spell(string spell)
{
    setuid();
    seteuid(getuid());
    object player = query_shadow_who();
    string * souls = player->query_cmdsoul_list();
    mapping abilities;
    
    if (!strlen(spell))
    {
        return 0;
    }
        
    foreach (string soul : souls)
    {
        if (!m_sizeof(abilities = soul->query_ability_map()))
        {
            continue;
        }
        
        foreach (string name, string file : abilities)
        {
            object ability_ob = find_object(file);
            if (!ability_ob)
            {
                 catch(file->teleledningsanka());
                 ability_ob = find_object(file);
            }
            if (!ability_ob)
            {
                continue;
            }
            if (ability_ob->exist_command(spell)
                && ability_ob->query_spell_can_be_learned(player))
            {
                return ability_ob;
            }
        }
    }

    return shadow_who->find_spell(spell);
}

public int
sort_spellobj(object a, object b)
{
    string a_name = a->query_spell_name();
    string b_name = b->query_spell_name();
    if (!strlen(a_name) || !strlen(b_name))
    {
        return 0;
    }
    
    if (a_name < b_name)
    {
        return -1;
    }
    else if (a_name > b_name)
    {
        return 1;
    }
    return 0;
}

/*
 * Function:    sort_spellobjs
 * Description: Allows the spell list to be sorted.
 */
public object *
sort_spellobjs(object * spellobjs)
{
    return sort_array(spellobjs, sort_spellobj);
}

public string stat_living()
{
    string str = shadow_who->stat_living();

    mixed* effects = shadow_who->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    int active_caid, active_task = 0;
    foreach(object effect : effects)
    {
        if (effect->query_spell_combat_aid())
        {
            active_caid += ftoi(effect->query_spell_combat_aid());
        }
        else if (effect->query_spell_maintained_combat_aid())
        {
            active_caid += ftoi(effect->query_spell_maintained_combat_aid());
        }
        else
        {
            active_task += effect->query_spell_task() / 10;
        }
    }
    return str + sprintf("Sustained spells: %d CAID + %d non-CAID (max sustainable %d) \n", 
        active_caid, active_task, get_maintained_combat_aid(shadow_who));
}


/*
 * Function name: query_spellobjs
 * Description:   return the spellobj list.
 */
public object *
query_spellobjs()
{
    setuid();
    seteuid(getuid());
    object player = query_shadow_who();
    string * souls = player->query_cmdsoul_list();
    object * spellobjs = ({ });
    mapping abilities;
    
    foreach (string soul : souls)
    {
        if (!m_sizeof(abilities = soul->query_ability_map()))
        {
            continue;
        }

        object * current_spellobjs = ({ });        
        foreach (string name, string file : abilities)
        {
            object spellobj = find_object(file);
            if (!spellobj)
            {
                 catch(file->teleledningsanka());
                 spellobj = find_object(file);
            }
            if (!spellobj)
            {
                // The spell failed to load - ignore it.
                continue;
            }
            if (spellobj->query_spell_can_be_learned(player))
            {
                if (!IN_ARRAY(spellobj, spellobjs))
                {
                    current_spellobjs += ({ spellobj });
                }
            }
        }
        current_spellobjs = sort_spellobjs(current_spellobjs);
        spellobjs += current_spellobjs;
    }
    // We now add all the spell objects that are not found in the
    // spell souls.
    object shadow_spellobjs = shadow_who->query_spellobjs();
    foreach (object spellobj : shadow_spellobjs)
    {
        if (!IN_ARRAY(spellobj, spellobjs))
        {
            spellobjs += ({ spellobj });
        }
    }
    return spellobjs;    
}

/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    // We first remove all the spell effects
    SPELL_MANAGER_SOUL->dispel_all_effects(shadow_who);

    shadow_who->notify_death(killer);
}

