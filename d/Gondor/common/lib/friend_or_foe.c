/*
 *        /d/Gondor/common/lib/friend_or_foe.c
 *
 *        Note that for Rohan, there is a different file,
 *        /d/Gondor/rohan/friend_foe.c
 *
 *        Olorin
 *
 *        This version:
 *        Copyright (c) 1996, 1997 by Christian Markus
 *
 *        Modification log:
 *        Deagol, April 2004
 *        Tigerlily, May 2004--added Rangers of the Westlands
 * 
 *        Cotillion, 2018-07-11
 *        - Refactored, updated guild list to reflect new guilds
 *        Finwe, May 2020, added more guilds
 */
#pragma save_binary
#pragma strict_types

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

static string *good = ({ "Gondorian Rangers Guild", "Rangers of the North", 
        "Rangers of the Westlands", "Solamnian Knights", 
        "Calian warrior's guild", "Heralds of the Valar", "Noldor of Imladris", 
        "Holy Order of the Stars", "Elemental Clerics of Calia"});

static string *evil = ({ "Morgul Mages", "Dragonarmy", "Angmar Army", 
        "Priests of Takhisis", "Necromancers Of Vile Darkness", 
        "Drow of Underdark", "Templars of Takhisis", "Orcs of Middle Earth", 
        "Red Fang Guild", "Warlocks of Faerun", "Fire Knives" });

public int
evil_guild_test(object pl)
{
    if (member_array(pl->query_guild_name_occ(), evil) >= 0 || 
        member_array(pl->query_guild_name_lay(), evil) >= 0 || 
        member_array(pl->query_guild_name_race(), evil) >= 0) 
    {
        return 1; 
    }

    return pl->query_prop(LIVE_I_UNDEAD) >= 1;
}

public int
good_guild_test(object pl)
{
    if (member_array(pl->query_guild_name_occ(), good) >= 0 ||
        member_array(pl->query_guild_name_lay(), good) >= 0 || 
        member_array(pl->query_guild_name_race(), good) >= 0)
    {   
        return 1;
    }
    return 0;
}

/*
 * Function name: hook_friend_or_foe
 * Description:   Redefine this function to add more checks.
 * Argument:      pl   - object pointer to player
 * Returns:       1/-1 - Return value is taken as friend or foe value,
 *                0    - Standard checks are made to calculate the friend or foe value
 */
public int
hook_friend_or_foe(object pl)
{
    return 0;
}

/*
 * int query_friend_or_foe(object pl)
 * returns: -1 = goblins, morgul mages, angmarim, align < -250
 *           0 = others
 *           1 = elves, rangers, paladines, align > 750
 */
public varargs int
query_friend_or_foe(mixed pl)
{
    int     friend_or_foe;
    string  race;

    if (stringp(pl))
        pl = find_living(LOW(pl));
    else if (!objectp(pl))
        pl = TP;

    if (!objectp(pl))
        return 0;

    ;

    if (friend_or_foe = hook_friend_or_foe(pl))
        ;
    else if (evil_guild_test(pl))
        friend_or_foe = -1;
    // We use query_race_name() here to add specific checks for
    // e.g dark elves etc:
    else if (( (race = pl->query_race_name()) == "goblin") && good_guild_test(pl) )
        friend_or_foe = 0;
    else if ((race = pl->query_race_name()) == "goblin")
        friend_or_foe = -1;
    else if (pl->query_alignment() < -250)
        friend_or_foe = -1;
    else if (pl->query_alignment() > 750)
        friend_or_foe = 1;
    else if ((race == "elf") || good_guild_test(pl))
        friend_or_foe = 1;
    return friend_or_foe;
}

