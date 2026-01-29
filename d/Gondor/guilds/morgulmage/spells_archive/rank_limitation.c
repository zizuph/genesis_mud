/*
 *  /d/Gondor/guilds/morgulmage/spells/rank_limitation.c
 * 
 *  File containing the system to limit spell usage by rank. This
 *  file can't be used on it's own an needs to be included in 
 *  the spells, as they already inherit the different base spells.
 *
 *  Created by Eowul, September 2009
 */

static int morgul_rank = -1;

/*
 * Function:    query_spell_can_be_learned
 * Description: This function is called by /d/Genesis/specials/abilities.c
 *              in order to determine whether the player can actually
 *              add this spell. This will allow guilds to customize the
 *              learning path for the caster guild, limiting access to
 *              spells until certain conditions are met.
 */
public int query_spell_can_be_learned(object player)
{
    if (morgul_rank == -1) return 1;
    if (player->query_npc()) return 1;
    if (player->query_wiz_level()) return 1;
    if (player->query_morgul_level() >= morgul_rank) return 1;
    return 0;
}

/*
 * Function:    set_morgul_rank
 * Description: Set the rank required to cast the spell
 * Arguments  : rank - the rank needed to cast the spell
 */
void set_morgul_rank(int rank)
{
    morgul_rank = rank;
}

int query_morgul_rank()
{
    return morgul_rank;
}