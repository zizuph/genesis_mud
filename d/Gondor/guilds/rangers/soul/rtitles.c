/*
 * /d/Gondor/guilds/rangers/soul/rtitles.c
 *
 * Included in the soul. Ability to list the Ranger titles.
 *
 * Originally coded by Elessar in May 1992
 *
 * Modification log:
 *
 * 07 February 2002 Alto: Recode and move.
 */

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <std.h>
#include "../titles.h";

int
rtitles(string str)
{
    int     i = 0,
            m,
            n;
    if (!strlen(str))
    {
        write("You can list these different titles:\n"
          + "Apprentices, General, Specialties, and one for each specialty.\n"
          + "  - A Ranger starts out as an Apprentice, before being accepted\n"
          + "    into one of the two Companies, where the general\n"
          + "    titles apply. After some time and experience, the\n"
          + "    Ranger may ask to be assigned a Specialty, which may\n"
          + "    eventually become his or her Master assignment.\n");
        return 1;
    }
    str = lower_case(str);
    if (str == "apprentices" || str == "apprentice")
    {
        n = sizeof(APPRENTICE_TITLES) - 1;
        write("Apprentice Titles, from top to bottom:\n");
        while (i < sizeof(APPRENTICE_TITLES))
        {
            write("  - " + APPRENTICE_TITLES[n - i] + ".\n");
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
