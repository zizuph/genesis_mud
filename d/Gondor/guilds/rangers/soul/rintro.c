/*
 * /d/Gondor/guilds/rangers/soul/rintro.c
 *
 * Included in the soul. Ability for Rangers to change the way
 * they introduce themselves to other players (specifically the title
 * perceived by other players.
 *
 * Original coder unknown, probably Elessar no later than January 1995
 *
 * Modification log:
 * 07 February 2002 Alto: General cleanup and move.
 * 01 April 2002 Alto: Added ability to turn ranger intro off.
 */

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>


int
ranger_intro_type(string str)
{
    int co;
    co = TP->query_ranger_level();
        
    if (!strlen(str))
    {
        write("Currently you introduce yourself with "
          + ((TP->query_ranger_intro() == 1) ? "your full" : "only short")
          + " title.\n");
        return 1;
    }

    if (str == "full" || str == "long")
    {
        if (TP->query_ranger_incognito())
        {
            write("You show your full title and openly proclaim " +
                "your allegience to the Rangers of the Westlands.\n");
            TP->set_ranger_incognito(0);
        }
        else
            write("You will now show your full title.\n");

        TP->set_ranger_intro(1);
        return 1;
    }

    else if (str == "brief" || str == "short")
    {
        if (TP->query_ranger_incognito())
        {
            write("You show your title only briefly, proclaiming " +
                "your allegience to the Rangers of the Westlands.\n");
            TP->set_ranger_incognito(0);
        }
        else
            write("You will now show only the brief title.\n");

        TP->set_ranger_intro(0);
        return 1;
    }

    if (str == "off" || str == "hide")
    {
        /*
         * There's no real reason that apprentices need to show
           everyone that they are a ranger apprentice.
        if (co < 3)
        {
            write("Are you ashamed of your allegience to Gondor?\n");
            return 1;
        }
        */
        write("You will now hide your title and travel incognito.\n");
        TP->set_ranger_incognito(1);
        return 1;
    }

    else if (str == "on" || str == "show")
    {
        /*
         * Allowing apprentices to hide their title.
        if (co < 3)
        {
            write("You already show your Ranger-title.\n");
            return 1;
        }
        */
        write("You no longer hide your title and openly proclaim your "
            + "allegience to the Rangers of the Westlands.\n");
        TP->set_ranger_incognito(0);
        return 1;
    }

    NF("Show how much of your Ranger-title?\n");
    return 0;
}

