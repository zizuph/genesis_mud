/* abilities.c - Combat ability routines
 *
 * Usage:
 * 1) inherit this module as your command soul
 * 2) add lines to your command map
 * 3) replace query_ability_map with your name to file mapping
 *
 * Example:
 * #include "/d/Genesis/specials/defs.h"
 * inherit ABILITIES_LIB;
 *

 * public mapping
 * query_ability_map()
 * {
 *     return ([
 *     "dokick" : ABILITY_DIR+"examples/kick"
 *      ]);
 * }
 * 
 *  
 * mapping
 * query_cmdlist()
 * {
 *     return ([
 *       "dokick" : "do_ability",
 *       
 *     ]);
 * }
 * 
 *
 *
 *  Modifications:
 *   October 5, 2009 - Added check for spell's learnability to support guild
 *                     specific learn paths for spells, Petros 
 */
#pragma strict_types

#include <macros.h>

/*
 * Function name: query_ability_map
 * Description:   Get the ability mapping (gAbilities)
 * Returns:       A mapping.
 */
public mapping
query_ability_map()
{
    return ([ ]);
}


public object
get_ability_object(string name)
{
    mixed ability = query_ability_map()[name];

    if (stringp(ability))
    {
        setuid();
        seteuid(getuid());
        LOAD_ERR(ability); 
        return find_object(ability);
    }

    if (objectp(ability))
    {
        return ability;
    }

    return 0;
}

/*
 * Function name: abort_ability
 * Description:   Called when concentration is aborted
 * Arguments:     string ability - the ability that was aborted
 */
public void
abort_ability(string ability)
{
    get_ability_object(ability)->abort_ability(this_player());
}


/*
 * Function name: do_ability
 * Description:   Called to initiate ability.  This is where
 *                we initialize the ability, do some preliminary checks. and
 *                apply initial ability costs
 * Arguments:     verb - The verb that initiated this ability.
 *                arg  - The arguments to the verb.
 * Returns:       True if the ability failed, false otherwise
 */
public int
do_ability(string arg)
{
    object ability;
    
    string verb=query_verb();

    object player = this_player();
    object * targets = ({});

    if (!(ability = get_ability_object(verb)))
    {
        return 0;
    }

    return ability->do_ability(arg);

}

public void add_spells(object player)
{
    object ability;
    object * dups;
    // This should be called to add all spells based on abilities to
    // the spell objects being tracked by /std/living/spells.c
    foreach (string spellname : sort_array(m_indexes(query_ability_map())))
    {
        ability = get_ability_object(spellname);
        if (ability->query_spell())
        {
            // We check for duplicate spells and remove them before
            // adding in the new spell.
            dups = filter(player->query_spellobjs(), 
                          &->exist_command(ability->query_spell_name()));
            foreach (object duplicate : dups)
            {
                player->remove_spellobj(duplicate);
            }
            // Only add the spell object if query_spell_can_be_learned
            // returns true.
            if (ability->query_spell_can_be_learned(player))
            {                
                player->add_spellobj(ability);
            }
        }
    }
}

public void remove_spells(object player)
{
    foreach (string key : m_indexes(query_ability_map()))
    {
        object ability = get_ability_object(key);
        if (ability->query_spell())
        {
            player->remove_spellobj(ability);
        }
    }
}
