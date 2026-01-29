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
 */
#pragma save_binary
#pragma strict_types

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

public int
evil_guild_test(object pl)
{
    return (pl->query_guild_name_occ() == "Morgul Mages"  ||            // Morgul Mage
            pl->query_guild_name_occ() == "Dragonarmy" ||              // Dragonarmies of Ansalon
            pl->query_guild_name_lay() == "Dragonarmy" ||              // Dragonarmies laymen
//            pl->query_guild_name_race() == "Thanarian human race guild"  ||    /* The evil humans from Thanar */
            pl->query_guild_name_race() == "Drow race guild"  ||  /* The evil Drow elves */
            pl->query_guild_name_race() == "Red Fang Guild"   ||  /* Evil goblin race guild */
            pl->query_guild_name_occ() == "LP of Khiraa"  ||  /* Undead of Khiraa */
            pl->query_guild_name_occ() == "Army of Mordor"  ||
            pl->query_prop(LIVE_I_UNDEAD) >= 1    || // Undead
            pl->query_guild_name_occ() == "BOGUS TEST");
}

public int 
good_guild_test(object pl)
{
    return (pl->query_guild_name_occ() == "Gondorian Rangers Guild"     // Ranger
        || pl->query_guild_name_occ() == "Rangers of the North"
        || pl->query_guild_name_occ() == "Rangers of the Westlands"
        || pl->query_guild_name_occ() == "Army of Gondor"
         || pl->query_guild_name_occ() == "Solamnian Knights"   	// Solamian Knight Occ
         || pl->query_guild_name_lay() == "Solamnian Knights"           // Solamnian Knight Lay
         || pl->query_guild_name_occ() == "Calian warrior's guild"      //Calian Warriors
         || pl->query_guild_name_lay() == "Heralds of the Valar"   // Heralds
         || pl->query_guild_name_occ() == "The Ancient Mystic Order");  // Mystic
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

    if (friend_or_foe = hook_friend_or_foe(pl))
        ;
    else if (evil_guild_test(pl))
        friend_or_foe = -1;
    // We use query_race_name() here to add specific checks for
    // e.g dark elves etc:
    else if (((race = pl->query_race_name()) == "goblin") && 
	     good_guild_test(pl))
        friend_or_foe = 0;
    else if (race == "goblin")
        friend_or_foe = -1;
    else if (pl->query_alignment() < -250)
        friend_or_foe = -1;
    else if (pl->query_alignment() > 750)
        friend_or_foe = 1;
    else if ((race == "elf") || good_guild_test(pl))
        friend_or_foe = 1;
    return friend_or_foe;
}

