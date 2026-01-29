/*
 *  /d/Gondor/clubs/nisse/soul/memberlist.c
 *
 *  Included in the soul. Ability to list Nisse logged in.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>

#include "/config/sys/local.h"
#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Function name: i_am_nisse
 *  Description  : Find out whether a particular person is a Nisse.
 *  Arguments    : object pl - the living to check.
 *  Returns      : int 1/0 - if true, the person is a Nisse.
 */
int
i_am_nisse(object pl)
{
    return (pl->query_nisse_member());
}

/*
 *  Function name: sort_nisse_rank
 *  Description  : This sorts all Nisse based on rank. The following order
 *                 is used: (1) tan (2) light brown (3) brown (4) deep brown
 *                 (5) red (6) gold (7) bronze. Within each category by name.
 *  Arguments    : object obj1 - the first person to check.
 *                 object obj2 - the second person to check.
 *  Returns      : int -1 if first rank is higher.
 *                      0 if first rank is equal.
 *                      1 if first rank is lower.
 */
int
sort_nisse_rank(object obj1, object obj2)
{
    string name1 = obj1->query_real_name();
    string name2 = obj2->query_real_name();
    int level1;
    int level2;

    /* Sort members by rank. */
    level1 = MANAGER->query_nisse_level(name1);
    level2 = MANAGER->query_nisse_level(name2);
    if (level1 || level2)
    {
        if (level1 > level2)
        {
            return -1;
        }
        if (level1 < level2)
        {
            return 1;
        }
        if (name1 == name2)
        {
            return 0;
        }
        return ((name1 < name2) ? -1 : 1);
    }
}

/*
 *  Function name: list_active_nisse
 *  Description  : Give a list of the Nisse in the realms
 *  Returns      : always 1
 */
int
list_active_nisse()
{
    int index;
    int size;
    int count;
    object *list;
    string name;
    string text;

    write("Nisse presently roaming the realms:\n");

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

    list = filter(list, i_am_nisse);
    list = sort_array(list, "sort_nisse_rank");

    size = sizeof(list);
    index = -1;
    while(++index < size)
    {
        name = capitalize(list[index]->query_real_name());

        /* Don't want a jr's name on the list */
        if ((extract(name, -2) == "jr") &&
            !(TP->query_wiz_level()))
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
            text += ", " + CAP(list[index]->query_nisse_rank());
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
        write("There are " + LANG_WNUM(count) + " Nisse roaming " +
              "the realms.\n");
    }
    else if (count == 1)
    {
        write("You are the only one Nisse roaming the realms.\n");
    }
    else if (count == 0)
    {
        write("There is no Nisse roaming the realms.\n");
    }
    return 1;
}
