inherit "/std/herb";

#include "/d/Emerald/sys/herb.h"

public int  rarity = 0;
public mapping habitat_map = ([]);
public int  addiction_factor = 0;

public int *query_habitats();

public void
create_emerald_herb()
{
}

private nomask void
create_herb()
{
    create_emerald_herb();
}

/*
 * Function name: query_rarity
 * Description:   Get the rarity of this herb in a given terrain
 * Arguments:     1. (int) the terrain to check or -1 for all terrains
 * Returns:       the (int) rarity, or a mapping of terrains to rarities if
 *                passed -1.
 */
public mixed
query_rarity(int h)
{
    int rarity, i;
    int *habitats;

    if (h == -1)
    {
        return habitat_map + ([]);
    }

    // Check for an exact match to save looping through all habitats.
    rarity = habitat_map[h];
    if (rarity)
    {
        return rarity;
    }

    habitats = query_habitats();
    for (i = 0; i < sizeof(habitats); i++)
    {
        // The terrain must include all the attributes of the herb's
        // habitat to match.
        if ((h & habitats[i]) == habitats[i])
        {
            return habitat_map[habitats[i]];
        }
    }

    return 0;
}

public void
add_habitat(int h, int rarity)
{
    habitat_map[h] = rarity;
}

public void
remove_habitat(int h)
{
    habitat_map = m_delete(habitat_map, h);
}

public int *
query_habitats()
{
    return (int *)m_indices(habitat_map);
}

public void
set_addiction_factor(int af)
{
    addiction_factor = af;
}

public int
query_addiction_factor()
{
    return addiction_factor;
}
