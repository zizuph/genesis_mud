/*
 *	/d/Gondor/morgul/feeling.c
 *
 *	Olorin, December 1995
 *
 *      Modification log:
 *      30-Jul-1997, Olorin: The King of Minas Morgul can declare
 *                           someone to be friend or foe.
 */
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

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

    if (strlen(guild_name))
        return ((guild_name == "Morgul Mages")  ||    /* Morgul Mage   */
                (guild_name == "Angmar Army"));       /* Angmar's Army */
    return 0;
}

/*
 * Function name: good_guild_test
 * Description:   Tests for guilds that are considered to be enemies of the Dark Lord.
 * Argument:      pl - object pointer to player object
 * Returns:       1 for enemies, 0 for others.
 */
public int 
good_guild_test(object pl)
{
    string  guild_name = pl->query_guild_name_occ();

    if (strlen(guild_name))
        return ((guild_name == "Rangers of the Westlands") ||   // Ranger
                (guild_name == "Solamnian Knights")       ||   // Solamian Knight Occ
                (pl->query_guild_name_lay() == "Sentries of Solamnia") || // Solamnian Knight Lay
                (guild_name == "Calian warrior's guild")  ||   // Calian Warriors
//                (guild_name == "The Smiths Guild")        ||   // Smiths of Bree
                (guild_name == "The Ancient Mystic Order"));   // Mystic
    return 0;
}

/*
 * varargs int query_feeling(mixed pl)
 * returns: -1 = goblins, morgul mages, angmarim, align < -250
 *           0 = others
 *           1 = elves, rangers, knights, align > 750
 */
public varargs int
query_feeling(mixed pl)
{
    int feeling;

    if (stringp(pl))
        pl = find_living(pl);
    if (!objectp(pl))
        pl = this_player();
    if (!objectp(pl))
        return 0;

    feeling = 0;
    if (feeling = MORGUL_MASTER->query_friend_or_foe(pl))
        return feeling;
    if (evil_guild_test(pl))
        feeling = -1;
    else if ((pl->query_race_name() == "elf") || good_guild_test(pl))
        feeling = 1;
    else if ((pl->query_race_name() == "half-elf"))
        feeling = 1;
    else if ((pl->query_race_name() == "goblin"))
    {
        if (pl->query_alignment() < 0)
            feeling = -1;
        else if (pl->query_alignment() > 500)
            feeling = 1;
    }
    else if (pl->query_alignment() < -250)
        feeling = -1;
    else if (pl->query_alignment() > 750)
        feeling = 1;
    return feeling;
}

varargs int
query_friend_or_foe(mixed pl)
{
    return query_feeling(pl);
}

