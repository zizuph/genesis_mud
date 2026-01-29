/*
 *    /d/Gondor/guilds/morgulmage/soul/support.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    It contains the support functions needed by the various
 *    other commands.
 *
 *    Created by Eowul, Apr 30, 2009, split from the other various
 *    command soul files.
 *
 */

#include "/d/Gondor/defs.h"
#include <std.h>

/*
 * Function name: special_wizard_filter
 * Description  : A special wizard is a wizard of the domain Gondor and a
 *                member of the administration.
 * Arguments    : object obj - the wizard to check.
 * Returns      : int 1/0 - passed/failed.
 */
int
special_wizard_filter(object obj)
{
    string name = obj->query_real_name();

    return ((SECURITY->query_wiz_dom(name) == "Gondor") ||
        (SECURITY->query_wiz_rank(name) >= WIZ_ARCH));
}

int
f_higher_dis(object x, int dis)
{
    return ((x->query_stat(SS_DIS)) > ((dis * 110) / 100));
}

int
f_lower_dis(object x, int dis)
{
    return ((x->query_stat(SS_DIS)) < ((dis *  90) / 100));
}

int
higher_rank(object x)
{
    return ( (x->query_morgul_level(-1) > this_player()->query_morgul_level(-1)) ||
             special_wizard_filter(x) );
}

int
member_filter(object x)
{
    return (IS_MEMBER(x));
}

int
member_player_filter(object x)
{
    return (IS_MEMBER(x) && interactive(x));
}


int
good_align(object x)
{
    return (x->query_alignment() > 0);
}

int
elf_filter(object x)
{
    return (x->query_race() == "elf");
}

int
mcall_succumb_filter(object x)
{
    return (!elf_filter(x) && !IS_MORGUL_MAGE(x) && !IS_RANGER(x));
}

int tell_next_room_with_dir( object this_room, string text )
{
 object room;
 mixed *exits, *oexits;
 string dir;
 int  n, i, s, j;

    if (!objectp( this_room ))
    {
        return 0;
    }
    exits = this_room->query_exit();

    j = sizeof( exits );
    for (i=0;i<j;i+=3)
    {
        if (strlen( exits[i] ))
        {
            if (find_object( exits[i] )) 
            {
                if ((n = member_array( MASTER_OB( this_room ), 
                    (oexits = exits[i]->query_exit()))) >= 0)
                {
                    dir = " the "+ oexits[n+1];
                }
                else
                {
                    dir = " somewhere nearby";
                }
                tell_room( exits[i], text+ dir+ ".\n" );
            }
        }
    }

    return 1;
}

varargs void
all2act_split(string str, object *oblist, object *nowatcher, string str1, 
    string adverb = "", string gmcp_verb = 0)
{
    object *livings;
    object *npcs;
    int    size;

    livings = FILTER_OTHER_LIVE(all_inventory(environment(this_player())) -
        oblist) - nowatcher;
    npcs = livings - FILTER_PLAYERS(livings);
    if (sizeof(npcs))
    {
        npcs->emote_hook_onlooker(query_verb(), this_player(), adverb, oblist);
    }

    /* Only bother if there are interactive players in the room left. */
    livings -= npcs;
    size = sizeof(livings);
    if (!size)
    {
        return;
    }

    str1 = (strlen(str1) ? str1 : ".");
    if (living(oblist[0]))
    {
        while(--size >= 0)
        {
            string text = this_player()->query_The_name(livings[size]) + " " + str +
                " " + COMPOSITE_WORDS(map(oblist,
                &->query_the_name(livings[size]))) + str1;
            livings[size]->catch_msg(text + "\n");
            if (stringp(gmcp_verb)) {
                livings[size]->gmcp_comms(gmcp_verb, 
                    this_player()->query_The_name(livings[size]), text);
            }
        }
    }
    else
    {
        while(--size >= 0)
        {
            livings[size]->catch_msg(
                this_player()->query_The_name(livings[size]) + " " + str +
                " " + FO_COMPOSITE_DEAD(oblist, livings[size]) + str1);
        }
    }
}

