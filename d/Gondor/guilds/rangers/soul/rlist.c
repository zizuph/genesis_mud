/*
 * /d/Gondor/guilds/rangers/soul/rlist.c
 *
 * Included in the soul. Ability to list rangers logged in.
 *
 * Originally coded by Elessar in May 1992
 *
 * Modification log:
 *
 * 04 February 2002 Alto: Recode and move.
 * 12 July 2004 Gwyneth: Fixed bugs
 * 27 January 2005 Finwe: allowed Council to see all rangers.
 */

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>
#include "/config/sys/local.h"


int
query_is_ranger_apprentice(object pl)
{
    if (pl->query_ranger_rank() < 3)
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: query_is_ranger_council
 * Description  : Find out whether a particular person is a council member.
 * Arguments    : 
 * Returns      : int 0-6.
 *                0 = not a council member.
 *                1 = sergeant, RoI.
 *                2 = sergeant, RoN.
 *                3 = lieutenant, RoI.
 *                4 = lieutenant, RoN.
 *                5 = captain, RoI.
 *                6 = captain, RoN.
 */
int
query_is_ranger_council(object pl)
{
    string name = pl->query_real_name();

    if (MANAGER->query_council(name) == CAPTAIN_POSITION)    
    {
        if (pl->query_company() == "north")
            {
                return 6;
            }
        return 5;
    }

    if(MANAGER->query_council(name) == LIEUTENANT_POSITION)
    {
        if (pl->query_company() == "north")
            {
            return 4;
            }
        return 3;
    }

    if(MANAGER->query_council(name) == SERGEANT_POSITION)
    {
        if (pl->query_company() == "north")
            {
            return 2;
            }
        return 1;
    }
    return 0;
}

/*
 * Function name: i_am_a_ranger
 * Description  : Find out whether a particular person is a ranger. The
 *                guildmasters of the guild are always recognised, and so are
 *                NPC's with the name 'ranger' added to them.
 * Arguments    : object pl - the living to check.
 * Returns      : int 1/0 - if true, the person is a ranger.
 */
int
i_am_a_ranger(object pl)
{
    if (pl->query_npc())
    {
        return (pl->id("ranger"));
    }
    else
    {
        return ((pl->query_guild_name_occ() == RANGERS_GUILD_NAME) ||
            SECURITY->query_guild_is_master(RANGERS_SHORT_GUILD_NAME,
                pl->query_real_name()));
    }
}


/*
 * Function name: sort_ranger_rank
 * Description  : This sorts all rangers based on rank. The following order is
 *                used: (1) Guildmasters (2) Wizards (3) Full rangers, by rank
 *                and (4) Pupils. Within each category by name.
 * Arguments    : object obj1 - the first person to check.
 *                object obj2 - the second person to check.
 * Returns      : int -1 if first rank is higher.
 *                     0 if first rank is equal.
 *                     1 if first rank is lower.
 */
int
sort_ranger_rank(object obj1, object obj2)
{
    string name1 = obj1->query_real_name();
    string name2 = obj2->query_real_name();
    int level1;
    int level2;

    /* Guildmaster on top. Multiple guildmasters sort by wizard rank and
     * then alphabetically.
     */
    level1 = SECURITY->query_guild_is_master(RANGERS_SHORT_GUILD_NAME, name1);
    level2 = SECURITY->query_guild_is_master(RANGERS_SHORT_GUILD_NAME, name2);
    if (level1 || level2)
    {
        if (level1)
        {
            if (!level2)
                return -1;
        }
        else
        {
            return 1;
        }

        level1 = SECURITY->query_wiz_rank(name1);
        level2 = SECURITY->query_wiz_rank(name2);

        if (level1 > level2)
            return -1;

        if (level1 < level2)
            return 1;

        if (name1 == name2)
            return 0;

        return ((name1 < name2) ? -1 : 1);
    }

    /* Next step, wizards. Within each rank, sort alphabetically. */
    level1 = SECURITY->query_wiz_rank(name1);
    level2 = SECURITY->query_wiz_rank(name2);
    if (level1 || level2)
    {
        if (level1 > level2)
            return -1;

        if (level1 < level2)
            return 1;

        if (name1 == name2)
            return 0;

        return ((name1 < name2) ? -1 : 1);
    }

    /* Next step, council members. */
    level1 = query_is_ranger_council(obj1);
    level2 = query_is_ranger_council(obj2);
    if (level1 || level2)
    {
        if (level1 > level2)
            return -1;

        if (level1 < level2)
            return 1;

        if (name1 == name2)
            return 0;

        return ((name1 < name2) ? -1 : 1);
    }


    /* Ranger rank. Since apprentices can have a higher rank than full rangers,
     * we add 100000 points to every member that is a full ranger.
     * To get all the same company together, we add 50000 points to RoNs.
     * Then we add their virtue * 1000 to ensure they are used as a secondary
     * sort.
     * Max for ranger level is 200.
     */

    level1 = obj1->query_ranger_rank();
    level2 = obj2->query_ranger_rank();

    switch(obj1->query_ranger_level())
    {
    case NORTH_LEVEL:
        level1 += 150000;
        break;
    case ITHILIEN_LEVEL:
        level1 += 100000;
        break;
    case APPROVED_APP_LEVEL:
        level1 += 50000;
        break;
    default:
        break;
    }

    switch(obj2->query_ranger_level())
    {
    case NORTH_LEVEL:
        level2 += 150000;
        break;
    case ITHILIEN_LEVEL:
        level2 += 100000;
        break;
    case APPROVED_APP_LEVEL:
        level2 += 50000;
        break;
    default:
        break;
    }

    level1 += obj1->query_ranger_major_virtue() * 1000;
    level2 += obj2->query_ranger_major_virtue() * 1000;

    if (level1 > level2)
        return -1;

    if (level1 < level2)
        return 2;

    /* Same rank, sort alphabetically. */
    if (name1 == name2)
        return 0;

    return ((name1 < name2) ? -1 : 1);
}

int
list_active_rangers()
{
    int index;
    int size;
    int count;
    object *list;
    string name;
    string text;

    write("Rangers currently in the realms:\n");

    list = users();

#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    /* code from /cmd/live/social.c:
     * If there is a room where statues of linkdead people can be found,
     * we add that to the list, but only if the player did not ask to only
     * see the interactive players.
     */
    list += filter((all_inventory(find_object(OWN_STATUE)) - list), 
        &not() @ &->query_npc());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD

    list = filter(list, i_am_a_ranger);
    list = sort_array(list, "sort_ranger_rank");

    size = sizeof(list);
    index = -1;
    while(++index < size)
    {
        name = capitalize(list[index]->query_real_name());

        /* Don't want a jr's name on the guildlist */
        if ((extract(name, -2) == "jr") &&
            !(TP->query_wiz_level()))
        {
            continue;
        }

        /* Take unknown RoN off the rlist of others */
        /* But let Council members see everyone */
// let all rangers see each other except apprentices
/*
        if ((!list[index]->query_ranger_known()) && 
            (list[index]->query_is_ranger_council(TP)) &&
            (!TP->query_wiz_level()) &&
            (TP->query_ranger_level() != NORTH_LEVEL) &&
            (list[index]->query_ranger_level() == NORTH_LEVEL))
        {
            continue;
        }
*/

        /* Take full rangers off the rlist of untrusted apprentices unless known */
        if ((list[index]->query_ranger_level() >= NORTH_LEVEL) &&
            (!TP->query_wiz_level()) &&
            (TP->query_ranger_level() <= APPRENTICE_LEVEL) &&
            (!list[index]->query_ranger_known()))
        {
            continue;
        }

        /* Hopefully this will get rid of the possessed npc listings */
        if (!IS_PLAYER_OBJECT(list[index]))
        {
            continue;
        }

        if (list[index]->query_wiz_level())
        {
            text = SECURITY->query_wiz_pretitle(list[index]) + " " + name +
                " " + list[index]->query_title();
        }
        else
        {
            text = name;
            if (list[index]->query_guild_family_name())
            {
                text += " " + list[index]->query_guild_title_race();
            }
            text += ", " + list[index]->query_ranger_title(1);
        }

        if (list[index]->query_invis())
        {
            if (!(TP->query_wiz_level()))
            {
                continue;
            }
            text += " <invis>";
        }
        text = ((interactive(list[index]) || list[index]->query_npc()) ?
            "- " : "* ") + text;
        if (list[index]->query_ghost())
        {
            text += " <dead>";
        }
        count++;
        write(text + "\n");
    }

    if (count > 1 )
    {
        write("There are " + LANG_WNUM(count) + " Rangers in the realms.\n");
    }
    else
    {
        write("There is only one Ranger in the realms.\n");
    }
    return 1;
}
