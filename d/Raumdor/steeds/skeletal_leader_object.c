
/*
 *  /d/Raumdor/steeds/skeletal_leader_object.c
 *
 *  This file contains actions/emotes for the leader of a steed
 *  
 *
 *  Based on a file by Deagol,
 *  Nerull 2010.
 */

inherit "/d/Genesis/steed/new/leader_object.c";
inherit "/lib/commands";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define TO               this_object()
#define TP               this_player()
#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())

#define HHELP_LEADER_MESSAGE \
   "\t\tCommands available for a leader of a horse\n \
    \t\t------------------------------------------\n\n \
    \t<hhelp> \tGet this text\n \
    \t<hhelp saddlebag> \tInstructions how to use saddlebags.\n \
    \t<unlead horse> \tRelease a horse and leave it alone\n \
    \t<mount horse> \tRide a horse\n"
    
#define HHELP_BAG_MESSAGE \
   "\t\tHow to use a saddlebag\n \
    \t\t----------------------\n\n \
    \tYou can use  your horse for  carrying your equipment, if you\n \
    \thave a proper saddlebag. Undermentioned commands do not need\n \
    \tcommentary.\n\n \
    \t\t<drape saddlebag on horse> \n \
    \t\t<remove saddlebag from horse> \n \
    \t\t<open saddlebag on horse>\n \
    \t\t<close saddlebag on horse>\n \
    \t\t<fill saddlebag on horse>\n \
    \t\t<empty saddlebag on horse>\n\n"


int hhelp(string str);
object Steed;

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (!living(ob))
    {
        return;
    }
    
    add_action(hhelp, "hhelp");
}

void
destruct_horse()
{
    Steed = TO->query_steed();
    Steed->remove_object();
}

int
hhelp(string str)
{
    if (str == "saddlebag")
    {
        write(HHELP_BAG_MESSAGE);     /* defined in mm_stables.h */
        return 1;
    }
    write(HHELP_LEADER_MESSAGE);        /* defined in mm_stables.h */
    return 1;
}
