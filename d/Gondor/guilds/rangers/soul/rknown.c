/*
 * /d/Gondor/guilds/rangers/soul/rknown.c
 *
 * Included in the soul. Ability for Rangers to appear on rlist
 * to apprentices or not.
 *
 * Coded by Gwyneth, 12/04/02
 *
 * Modification log:
 *   12 July 2004, Gwyneth: Syntax changes
 */

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>


int
rknown(string str)
{
    if (TP->query_ranger_level() < NORTH_LEVEL && !TP->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        write("Currently you are"
          + ((TP->query_ranger_known()) ? "" : " not")
          + " visible to apprentices on rlist.\n");
        return 1;
    }

    if (lower_case(str) == "off")
    {
        write("You will not be shown on rlist to apprentices.\n");
        TP->set_ranger_known(0);
        return 1;
    }

    else if (lower_case(str) == "on")
    {
        write("You will now be visible on rlist to apprentices.\n");
        TP->set_ranger_known(1);
        return 1;
    }

    NF("Rknown on/off?\n");
    return 0;
}

