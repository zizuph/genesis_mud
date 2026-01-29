/*
 * name_macros.c
 *
 * This file contains a few functions used in the support
 * for met/nonmet area descriptions in Eldoral and Castle
 * Chimera.
 */
#include "defs.h"

/*
 * Function name: player_knows_castle
 * Description  : Returns true if the player has discovered
 *                the name of Castle Chimera.
 * Arguments    : n/a
 * Returns      : True if known, false if not.
 */
public int
player_knows_castle()
{
    return TP->query_skill(SK_ELDORAL_CASTLE_NAME) &
        SK_CASTLE_NAME_VALUE;
}

/*
 * Function name: player_knows_eldoral
 * Description  : Returns true if the player has discovered
 *                the name of Eldoral.
 * Arguments    : n/a
 * Returns      : True if known, false if not.
 */
public int
player_knows_eldoral()
{
    return TP->query_skill(SK_ELDORAL_CASTLE_NAME) &
        SK_ELDORAL_NAME_VALUE;
}

/*
 * Function name: castle_name
 * Description  : Used to generate a VBFC string return
 *                to describe the castle depending on if
 *                the player has discovered it's name.
 * Arguments    : n/a
 * Returns      : "Castle Chimera" if known.
 *                "an old castle" if not known.
 */
public string
castle_name()
{
    if (player_knows_castle())
        return "Castle Chimera";
    return "an old castle";
}

/*
 * Function name: lake_name
 * Description  : Same as castle_name, except works for
 *                references to Eldoral Lake.
 * Arguments    : n/a
 * Returns      : "Eldoral Lake" or "a mist-shrouded lake".
 */
public string
lake_name()
{
    if (player_knows_eldoral())
        return "Eldoral Lake";
    return "a mist-shrouded lake";
}

/*
 * Function name: island_name
 * Description  : Same as lake_name, except works for
 *                the island itself.
 * Arguments    : n/a
 * Returns      : "Eldoral Isle" or "a forested island".
 */
public string
island_name()
{
    if (player_knows_eldoral())
        return "Eldoral Isle";
    return "a forested island";
}
