/*
 *  Code for general Ranger commands and Ranger-speak.
 *
 *  Modification Log:
 *    14 December 2002, made possible for wizards to understand, Alto.
 */

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>
#include "titles.h"
#include "/config/sys/local.h"

#define ADUNAIC_DIFF      60

int
rtitles(string str)
{
    int     i = 0,
            m,
            n;
    if (!strlen(str))
    {
        write("You can list these different titles:\n"
          + "Pupils, General, Specialties, and one for each specialty.\n"
          + "  - A Ranger starts out as a Pupil, before being accepted\n"
          + "    into one of the three Companies, where the general\n"
          + "    titles apply. After some time and experience, the\n"
          + "    Ranger may ask to be assigned a Specialty, which may\n"
          + "    eventually become his or her Master assignment.\n");
        return 1;
    }
    str = lower_case(str);
    if (str == "pupils" || str == "pupil")
    {
        n = sizeof(PUPIL_TITLES) - 1;
        write("Pupil Titles, from top to bottom:\n");
        while (i < sizeof(PUPIL_TITLES))
        {
            write("  - " + PUPIL_TITLES[n - i] + ".\n");
            i++;
        }
        return 1;
    }
    else if (str == "general" || str == "normal")
    {
        i = 0;
        n = sizeof(GENERAL_TITLES) - 1;
        write("General titles, from top to bottom:\n");
        write("  - Legend.\n");
        while (i < sizeof(GENERAL_TITLES))
        {
            write("  - " + GENERAL_TITLES[n - i] + ".\n");
            i++;
        }
        return 1;
    }
    else if (str == "specialties" || str == "masters")
    {
        i = 1;
        n = sizeof(MASTER_TITLES);
        write("Specialties:\n");
        while (i < n)
        {
            write("  - " + MASTER_TITLES[i] + ".\n");
            i++;
        }
        return 1;
    }
    else
    {
        m = member_array(CAP(str), MASTER_TITLES);
        if (m == -1)
        {
            NF("That is not a Specialty. Try 'rtitles specialties'.\n");
            return 0;
        }
        n = sizeof(SUB_MASTER_TITLES[m]) - 1;
        i = 0;
        write(CAP(str) + " ranks, from top to bottom:\n");
        write("  - Master " + CAP(str) + ".\n");
        while (i < sizeof(SUB_MASTER_TITLES[m]))
        {
            write("  - " + SUB_MASTER_TITLES[m][n-i] + " " 
              + CAP(str) + ".\n");
            i++;
        }
        return 1;
    }
    write("That's not a valid list. Try 'rtitles' for options.\n");
    return 1;
}

/*
 * Function name: is_ranger
 * Description  : Find out whether a particular person is a ranger. The
 *                guildmasters of the guild are always recognised, and so are
 *                NPC's with the name 'ranger' added to them.
 * Arguments    : object pl - the living to check.
 * Returns      : int 1/0 - if true, the person is a ranger.
 */
int
is_ranger(object pl)
{
    if (pl->query_npc())
    {
        return (pl->id("ranger"));
    }
    else
    {
        return (IS_RANGER(pl) ||
            SECURITY->query_guild_is_master(RANGER_SHORT_GUILDNAME,
                pl->query_real_name()));
    }
}

int
understand_adunaic(object pl)
{
    int  langsk = pl->query_skill(SS_LANGUAGE);

    if (is_ranger(pl) && (langsk > 10))
        return 1;
    else if (IS_DUNADAN(pl) && (langsk > 1))
        return 1;
    else if (pl->query_wiz_level())
        return 1;
    else if (pl->query_guild_name_race() == "Sindar of Lorien" &&
            (langsk > ADUNAIC_DIFF - 25))
        return 1;
    else if (langsk >= ADUNAIC_DIFF)
        return 1;
    else 
        return 0;
}

int
speak_adunaic(string str)
{
    string   cap_name;
    int      i,
             sobj;
    object  *obj;
    mixed    gag;
   
    if (!strlen(str)) 
    {
        NF0("Say what in Adunaic?\n");
    }

    gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED);
    if (gag)
    {
        if (stringp(gag))
            TP->catch_msg(gag);
        else if (intp(gag))
            TP->catch_msg("You are unable to speak right now!\n");
        return 1;
    }

    if (TP->query_invis()) 
        cap_name = "Someone";
    str += " ";
    /*
     * Check take from /std/living/cmdhooks.c:
     * We do not want people to add too many spaces and use the grsay
     * command as a way to generate emotions themselves. However, we do
     * not want to waste this on wizards and we also test whether people
     * haven't used too many spaces. You cannot make an emotion with
     * only a few. This wildmatch is 40% faster than the explode/implode
     * stuff, so as long as people don't use 8 spaces more than 40% of
     * the time, this check pays itself back.
     */
    if (!TP->query_wiz_level() &&
        wildmatch("*       *", str))
    {
        str = implode((explode(str, " ") - ({ "" }) ), " ");
    }
    write("You speak in Adunaic: " + str + "\n");
    obj = all_inventory(environment(TP));
    sobj = sizeof(obj);
    while (i < sobj)
    {
        if ((living(obj[i])) && (obj[i] != TP))
        {
             if (!understand_adunaic(obj[i]))
             {
                 if (CAN_SEE(obj[i],TP))
                     obj[i]->catch_msg(QCTNAME(TP)
                       + " says something in an unknown language.\n");
                 else 
                     obj[i]->catch_msg("Someone says something in an "
                       + "unknown language.\n");
            }
            else
            { 
                if (CAN_SEE(obj[i],TP))
                    obj[i]->catch_msg(QCTNAME(TP)
                          + " speaks in Adunaic: " + str + "\n");
                else
                    obj[i]->catch_msg("Someone speaks in Adunaic: "
                          + str +"\n");
            }
        }
        i++;
    }
    return 1;
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
    level1 = SECURITY->query_guild_is_master(RANGER_SHORT_GUILDNAME, name1);
    level2 = SECURITY->query_guild_is_master(RANGER_SHORT_GUILDNAME, name2);
    if (level1 || level2)
    {
        if (level1)
        {
            if (!level2)
            {
                return -1;
            }
        }
        else
        {
            return 1;
        }

        level1 = SECURITY->query_wiz_rank(name1);
        level2 = SECURITY->query_wiz_rank(name2);
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

    /* Next step, wizards. Within each rank, sort alphabetically. */
    level1 = SECURITY->query_wiz_rank(name1);
    level2 = SECURITY->query_wiz_rank(name2);
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

    /* Ranger rank. Since pupils can have a higher rank than full rangers,
     * we add 1000 points to every member that is a full ranger.
     */
    level1 = obj1->query_ranger_rank(1) +
        ((obj1->query_is_ranger_pupil()) ? 0: 1000);
    level2 = obj2->query_ranger_rank(1) +
        ((obj2->query_is_ranger_pupil()) ? 0: 1000);
    if (level1 > level2)
    {
        return -1;
    }
    if (level1 < level2)
    {
        return 2;
    }

    /* Same rank, sort alphabetically. */
    if (name1 == name2)
    {
        return 0;
    }
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

    list = filter(list, is_ranger);
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

int
ranger_intro_type(string str)
{
    if (!strlen(str))
    {
        write("Currently you introduce yourself with "
          + ((TP->query_ranger_intro() == 1) ? "your full" : "only short")
          + " title.\n");
        return 1;
    }
    if (str == "full" || str == "fully")
    {
        write("You will now show your full title.\n");
        TP->set_ranger_intro(1);
        return 1;
    }
    else if (str == "short" || str == "brief" || str == "briefly")
    {
        write("You will now show only the brief title.\n");
        TP->set_ranger_intro(0);
        return 1;
    }
    NF("Show how much of your Ranger-title?\n");
    return 0;
}

