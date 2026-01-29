/*
 * memberlist.c
 *
 * Included in the soul. Ability to list Anghoth logged in.
 *
 * Alto 11 June 2002
 *
 */

#include "/d/Gondor/defs.h"
#include "../anghoth_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>
#include "/config/sys/local.h"


/*
 * Function name: i_am_anghoth
 * Description  : Find out whether a particular person is an anghoth. The
 *                guildmasters of the guild are always recognised, and so are
 *                NPC's with the name 'ranger' added to them.
 * Arguments    : object pl - the living to check.
 * Returns      : int 1/0 - if true, the person is a ranger.
 */
int
i_am_anghoth(object pl)
{
    return (ANGHOTH_MEMBER(pl));
}


/*
 * Function name: sort_anghoth_rank
 * Description  : This sorts all anghoth based on rank. The following order is
 *                used: (1) Durub (2) Dath (3) Korrak
 *                and (4) Kriechek. Within each category by name.
 * Arguments    : object obj1 - the first person to check.
 *                object obj2 - the second person to check.
 * Returns      : int -1 if first rank is higher.
 *                     0 if first rank is equal.
 *                     1 if first rank is lower.
 */
int
sort_anghoth_rank(object obj1, object obj2)
{
    string name1 = obj1->query_real_name();
    string name2 = obj2->query_real_name();
    int level1;
    int level2;

    /* Sort members by rank. */
    level1 = MANAGER->query_anghoth_level(name1);
    level2 = MANAGER->query_anghoth_level(name2);
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

int
list_active_anghoth()
{
    int index;
    int size;
    int count;
    object *list;
    string name;
    string text;

    write("Anghoth presently marching for Minas Morgul:\n");

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

    list = filter(list, i_am_anghoth);
    list = sort_array(list, "sort_anghoth_rank");

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
            text += ", " + CAP(list[index]->query_anghoth_rank());
        }

        if (list[index]->query_invis())
        {
            if (!(TP->query_wiz_level()))
            {
                continue;
            }
            text += " <invis>";
        }

        if (list[index]->query_ashuk())
        {
            text += " << Ashuk >>";
        }

        text = ((interactive(list[index]) || list[index]->query_npc()) ?
            "- " : "* ") + text;
        if (list[index]->query_ghost())
        {
            text += " <dead>";
        }

        switch (list[index]->query_ashuk())
        {
            case 0:
                text += ", Shield of " + MANAGER->query_anghoth_sponsor(name);
                count++;
                write(text + "\n");
                break;
            case 1:
                text += ", Alone";
                count++;
                write(text + "\n");
                break;
            default:
                break;
        }
    }

    if (count > 1 )
    {
        write("There are " + LANG_WNUM(count) + " Anghoth marching "
            + "in the realms.\n");
    }
    else
    {
        write("There is only one Anghoth stationed in the realms.\n");
    }
    return 1;
}
