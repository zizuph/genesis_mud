/*
 *	/d/Gondor/rohan/friend_foe.c
 *
 *	Olorin, December 1995
 *
 *      Last modification: Elessar, 2-Aug-1999
 *
 *      This version:
 *      Copyright (c) 1996 by Christian Markus
 *
 *  2019-08-22: Modified by Shanoga
 *    - query_friend now uses query_race_name instead of query_race
 *      because NPCs should see subrace (ogre, minotaur, kender, etc)
 *      and not the player's true race
 */
#pragma strict_types
#include "/d/Gondor/defs.h"

/*
 * Function name: evil_guild_test
 * Description:   Tests for guilds allied with the Dark Lord.
 *                Recognizes only occupational guilds.
 * Argument:      pl - object pointer to player object
 * Returns:       1 for allies, 0 for others.
 */
public int
evil_guild_test(object pl = this_player())
{
    string  guild_name = pl->query_guild_name_occ();

    if (strlen(guild_name) && (
	(guild_name == "Morgul Mages")  ||    /* Morgul Mage   */
	(guild_name == "Vampires of Emerald")   ||
	(guild_name == "Dragonarmy")))      /* Dragonarmies of Krynn */
	return 1;
    else if (strlen(guild_name = pl->query_guild_name_lay()) && (
	(guild_name == "Angmar Army")  ||   /* Lay Angmar's Army */
	(guild_name == "Bloodguard guild")))
	return 1;
    else if (strlen(guild_name = pl->query_guild_name_race()) && (
	(guild_name == "Thanarion human race guild") ||
	(guild_name == "Drow race guild") ||
	(guild_name == "Red Fang Guild")))
	return 1;
    return 0;
}

/*
 * Function name: good_guild_test
 * Description:   Tests for guilds that are considered to be enemies of 
 *                the Dark Lord.
 * Argument:      pl - object pointer to player object
 * Returns:       1 for enemies, 0 for others.
 */
public int 
good_guild_test(object pl = this_player())
{
    string  guild_name = pl->query_guild_name_occ();

    if (strlen(guild_name) & (
	(guild_name == "Gondorian Rangers Guild") ||   // Ranger
	(guild_name == "Rangers of the North") ||      // Ranger
	(guild_name == "Solamnian Knights")       ||   // Solamian Knight Occ
	(guild_name == "Calian warrior's guild")  ||   // Calian Warriors
	(guild_name == "The Ancient Mystic Order")))   // Mystic
	return 1;
    return 0;
}

/*
 * varargs int query_feeling(mixed pl)
 * returns: -2 = goblins, morgul mages, angmarim, ohtari
 *          -1 = elves, humans of align < -250
 *           0 = others
 *           1 = humans align > 250, 
 *               dwarves, elves, hobbits, gnomes align > 750
 *           2 = rangers, knights, humans of align > 750
 */
public int
query_friend(mixed pl = this_player())
{
    int    susp = 0;
    string race;

    if (stringp(pl))
	pl = find_living(pl);
    if (!objectp(pl))
	return 0;

    race = pl->query_race_name();

    if (evil_guild_test(pl))
	susp =  -2;
    else if (good_guild_test(pl))
	susp =   2;
    if (pl->query_prop(LIVE_I_KILLED_ROHIRRIM))
	susp -=  4;

    switch (pl->query_alignment())
    {
    case -2000 ..  -751:
	susp += -2;
	break;
    case  -750 ..  -251:
	susp += -1;
	break;
    case  -250 ..   250:
    default:
	break;
    case   251 ..   750:
	susp +=  1;
	break;
    case   751 ..  2000:
	susp +=  2;
	break;
    }

    switch (race)
    {
    case "human":
	susp +=  1;
	break;
    case "elf":
	susp -= 1;
	break;
    case "hobbit":
	susp += 1;
	break;
    case "goblin":
	susp -=  2;
	break;
    default:
	break;
    }

    return susp;
}

varargs int
query_friend_or_foe(mixed pl)
{
    return query_friend(pl);
}
