#include <ss_types.h>

/************************************************************************
 *                     Ability Guild Stat Functions                     *
 ************************************************************************/

static int      Ability_gstat_type = 0,
                Ability_gstat_min_pct = 20,
                Ability_gstat_cap = 100;

/*
 * Function name:   set_guild_stat_modifier
 * Description:     For damage specials, we want to provide a way
 *                  for GMs to scale the damage of their specials
 *                  based on the guild stat. By calling this function
 *                  They can specify which guild stat to use, what
 *                  the minimum damage percentage should be when the
 *                  player has no guild stat at all, and also at
 *                  what guild stat the player achieves the full power
 *                  of the special.
 * Arguments:       (int) guild_type - This is the value for one of the
 *                      guild stats, like SS_LAYMAN, SS_OCCUP, etc.
 *                  (int) min_pct - This is the minimum percentage that
 *                      the special will have when the person has no
 *                      guild stat. This is what players will see when
 *                      they initially enter the guild
 *                  (int) cap - This is the guild stat cap at which the
 *                      player achieves the full amount of the damage.
 *                      For example, if you set this to 150. Then when a
 *                      player achieves 150 guild stat, then they will
 *                      no longer have their damage reduced in the
 *                      query_ability_power function.
 * Returns:         Nothing
 */
public void 
set_guild_stat_modifier(int guild_type, int min_pct, int cap)
{
    switch (guild_type)
    {
        case SS_RACE:
        case SS_OCCUP:
        case SS_LAYMAN:
        case SS_CRAFT:    
            Ability_gstat_type = guild_type;
            break;
        default:
            Ability_gstat_type = 0;
    }
    
    // Min max the min_pct value
    Ability_gstat_min_pct = min(100, max(0, min_pct));
    Ability_gstat_cap = cap;
} /* set_guild_stat_modifier */

/*
 * Function name:   query_guild_stat_minimum_percentage
 * Description:     
 * Arguments:       (object) player
 * Returns:         (int)
 */
public int
query_guild_stat_minimum_percentage(object player)
{
    return Ability_gstat_min_pct;
} /* query_guild_stat_minimum_percentage */

/*
 * Function name:   query_guild_stat_type
 * Description:     
 * Arguments:       (object) player
 * Returns:         (int)
 */
public int
query_guild_stat_type(object player)
{
    return Ability_gstat_type;
} /* query_guild_stat_type */

/*
 * Function name:   query_guild_stat_type_desc
 * Description:     
 * Arguments:       (object) player
 * Returns:         (string)
 */
public string
query_guild_stat_type_desc(object player)
{        
    switch (query_guild_stat_type(player))
    {
        case SS_RACE:
            return "Race";
        
        case SS_OCCUP:
            return "Occupational";
        
        case SS_LAYMAN:
            return "Layman";
        
        case SS_CRAFT:
            return "Craft";
    }
    
    return "None";
} /* query_guild_stat_type_desc */

/*
 * Function name:   query_guild_stat_cap
 * Description:     
 * Arguments:       (object) player
 * Returns:         (int)
 */
public int
query_guild_stat_cap(object player)
{
    return Ability_gstat_cap;
} /* query_guild_stat_cap */

/*
 * Function name:   query_guildstat_modifier_helper
 * Description:     This is the helper function for calc_guild_stat_modifier
 *                  It takes in the values and does a standard set of
 *                  calculations to determine the modifier for the special.
 * Arguments:       (object) player - the player executing the special
 *                  (int) res - the current pen value to be modified
 * Returns:         (int) res modified by guildstat
 */
public varargs int
query_guildstat_modifier(object player, int res, int gstat_type = 0,
    int gstat_min_pct = 0, int gstat_cap = 0)
{
    int gstat_modifier = 100;
    
    if (!objectp(player))
        return res;
    
    if (!gstat_type)
        gstat_type = query_guild_stat_type(player);
    
    if (!gstat_min_pct)
        gstat_min_pct = query_guild_stat_minimum_percentage(player);
    
    if (!gstat_cap)
        gstat_cap = query_guild_stat_cap(player);
    
    if (gstat_type != 0)
    {
        int player_gstat = player->query_stat(gstat_type);
        if (player_gstat < gstat_cap)
        {
            // We're at less than the cap. so we will modify the result
            // downwards based on the scaling from the minimum percentage
            gstat_modifier = (100 - gstat_min_pct) * player_gstat / gstat_cap;
            gstat_modifier += gstat_min_pct;

            res = res * gstat_modifier / 100;
        }
    }
    
    return res;
} /* query_guildstat_modifier_helper */