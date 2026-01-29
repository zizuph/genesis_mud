/*
 * /d/Gondor/guilds/rangers/soul/consider.c
 *
 * Included in the soul. The Ranger ability to consider the taint on 
 * the soul of another being. 
 *
 * Originally coded by Elessar 
 * (I think, but there were no credits on original.)
 *
 * Modification log:
 * 07 February 2002 Alto: General cleanup and move.
 * 01 April 2002 Gwyneth: Added a smaller breakdown of alignments in
 *                        the neutral area. Removed TP->catch_msg(QTNAME(ob) +
 *                        with write(ob->query_the_name(TP) +
 *                        as it is MUCH more efficient. catch_msg() hardly
 *                        ever needs to be used with TP. Q*NAME(ob) is used
 *                        when there is more than one person the message is
 *                        going to, essentially a macro for query_*_name().
 * 14 Aug 2002 Gwyneth  : Changed consider to only check for banned guilds
 *                        and outlaw/notorious-outlaw status.
 * 18 June 2004 Tigerlily:Changed to check for evil npcs and players as 
 *                        well, since rangers are punished for teaming with
 *                        evil or killing good creatures
 * 12 December 2015 Varian: Allowed for rconsider to check for banned guilds
 *
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>

public int
consider(string str)
{
    int  align;
    object *oblist, ob;
    object tp = this_player();
    string st, pr, nr, tr, typ, order;

    oblist = parse_this(str, "[the] %l");

    str = lower_case(str);
    if (str == "myself" || str == "me" || str == tp->query_real_name())
    {
        write("You consider yourself for a while and suddenly realize " +
            "there are better ways to measure such things.\n");
        return 1;
    }

    if (!oblist || !sizeof(oblist))
    {
        NF("Rconsider whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        NF("You can only consider one being at a time.\n");
        return 0;
    }

    ob = oblist[0];

    if (!ob->query_npc() && MANAGER->query_is_outlaw(ob->query_real_name()))
    {
        write("You recognize " + ob->query_the_name(tp) + 
            " as an outlaw of the Rangers of the Westlands.\n");
        return 1;
    }

    if (!ob->query_npc() && 
      MANAGER->query_notorious_outlaw(ob->query_real_name()))
    {
        write("You recognize " + ob->query_the_name(tp) + 
            " as a notorious outlaw of the Rangers of the Westlands.\n");
        return 1;
    }


    if (member_array(ob->query_guild_name_occ(), BANNED_GUILDS) != -1)
    {
        write("You sense that the Valar do not approve of " +
            "the faction " + ob->query_the_name(tp) + " supports.\n");
        return 1;
    }


    if (!ob->query_npc() && ob->query_alignment() < 0)
    {
        write("You sense that the Valar would be displeased " +
            "if you team with " + ob->query_the_name(tp) +
            ".\n");
        return 1;
    }

    if (ob->query_npc() && ob->query_alignment() < 0)
    {
        write("You sense evil emanating from " + 
            ob->query_the_name(tp) + ".\n");
        return 1;
    }

    if (ob->query_alignment() == 0)
    {
        write("You sense that the Valar have no opinion about " +
            ob->query_the_name(tp) + ".\n");
        return 1;
    }

    if (ob->query_alignment() > 0)
   {
        write("The Valar would be displeased if you harm " +
            ob->query_the_name(tp) + ".\n");
        return 1;
    }

    write("You do not feel that " + ob->query_the_name(tp) + 
        " is a recognized enemy of the Rangers of the Westlands.\n");
    return 1;
}

