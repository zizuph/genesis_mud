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
 */

#pragma strict_types

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public int      last_mana       = -1;
public int      recursive_lock  =  0;
public string   mana_log        =  0;

// Defines
#define     MANA_REGEN_MULTIPLIER       3.0
#define     MANA_POOL_DIVIDER           3
#define     SPELL_MANAGER_SOUL          "/d/Genesis/specials/guilds/souls/spell_manager_soul"

// Prototypes
public void     add_mana(int sp);
public int      query_mana();
public int      query_max_mana();

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
 * Function:    set_mana_log
 * Description: Sets the mana change logfile. This will cause all the
 *              changes in mana to get logged by this shadow. Use a
 *              unique filename per shadow. All log files will be placed
 *              inside of /d/Genesis/specials/guilds/log
 */
public void
set_mana_log(string filename)
{
    mana_log = filename;
}

/*
 * Function:    query_mana_log
 * Description: Returns the filename (full path) of the log at
 *              /d/Genesis/specials/guilds/log/ that will contain
 *              the logs for this shadow.
 */
public string
query_mana_log()
{
    if (strlen(mana_log))
    {
        return "/d/Genesis/specials/guilds/log/" + mana_log;
    }
    return 0;
}

/*
 * Function:    query_adjusted_mana
 * Description: Returns the adjusted mana that this shadow
 *              offers.
 */
public int
query_adjusted_mana()
{
    return min(shadow_who->query_mana(), query_max_mana());
}

/*
 * Function name:   set_mana
 * Description:     Set the number of mana points that a player has. Mana
 *                  points are more commonly known as spellpoints. The
 *                  mana points can not bet set to more than the amount
 *                  that is calculated by query_max_mana.
 * Arguments:       sp: The new amount of mana points.
 */
void
set_mana(int sp)
{
    shadow_who->set_mana(sp);
    last_mana = query_adjusted_mana();
}
 
/*
 * Function name:   add_mana
 * Description:     Add a certain amount of mana points
 * Arguments:       sp: The number of mana points to change.
 */
void
add_mana(int sp)
{
    int current_mana = query_mana();
    current_mana += sp;
    shadow_who->set_mana(current_mana);
    if (sp != 0)
    {
        string source = MASTER_OB(previous_object());
        if (calling_function() != "query_mana")
        {
            send_debug_message("mana_shadow", "adding " + sp + " mana results in " 
                + shadow_who->query_mana() + " of " + query_max_mana() + " remaining. (" 
                + source + ")",
                query_mana_log());
        }
    }
    last_mana = query_adjusted_mana();
}

/*
 * Function name:   query_mana
 * Description:     Gives the number of mana points that the living has
 * Returns:         The number of mana points.
 */
public int
query_mana()
{
    int mana = min(shadow_who->query_mana(), query_max_mana());
    
    if (recursive_lock || calling_function() == "add_mana")
    {
        return mana;
    }
    
    recursive_lock = 1;
    if (last_mana != -1)
    {
        // It is only -1 on the first time query_mana is called
        int regen_amount = mana - last_mana;
        last_mana = mana; // Set the new mana amount
        int additional_regen = 0;
        if (mana != query_max_mana())
        {
            additional_regen = min(ftoi(itof(regen_amount) * (MANA_REGEN_MULTIPLIER - 1.0)), query_max_mana() - mana);
            if (additional_regen > 0)
            {
                add_mana(additional_regen);
            }
        }
        if ((regen_amount + additional_regen) > 0)
        {
            send_debug_message("mana_shadow", "regenerating " 
                + (regen_amount + additional_regen) + " mana results in " 
                + query_adjusted_mana() + " of " + query_max_mana() + " remaining. "
                + "(Regeneration)", query_mana_log());         
        }
    }
    else
    {
        // Setting initial last_mana amount.
        last_mana = mana;
    }
    
    recursive_lock = 0;
    return mana;
}

/*
 * Function name:   query_max_mana
 * Description:     Calculates that maximum of mana points that a living
 *                  can get.
 * Returns:         The maximum.
 */
public int
query_max_mana()
{
    int old_max = shadow_who->query_max_mana();
    
    // We divide first, and add 90 mana (3 spell casts)
    return (old_max / MANA_POOL_DIVIDER) + 90;
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
            if (file->exist_command(spell)
                && file->query_spell_can_be_learned(player))
            {
                return find_object(file);
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
            if (file->query_spell_can_be_learned(player))
            {
                object spellobj = find_object(file);
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

