
/*
 *  /d/Raumdor/steeds/skeletal_rider_object.c
 *
 *  This file contains actions/emotes for the rider of a steed.
 *  
 *
 *  Based on a file by Deagol, 
 *  Nerull 2010.
 */

inherit "/d/Genesis/steed/new/rider_object";
inherit "/lib/commands";

#include <macros.h>
#include <filter_funs.h>

#define TO               this_object()
#define TP               this_player()
#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())

#include "/d/Gondor/defs.h"

#define HHELP_RIDER_MESSAGE \
   "\t\tCommands available for a rider of a horse\n \
    \t\t-----------------------------------------\n\n \
    \t<hhelp> \tGet this text\n \
    \t<hhelp saddlebag> \tInstructions how to use saddlebags.\n \
    \t<hgallop on> \tMake your horse gallop\n \
    \t<hgallop off> \tMake your horse walk\n \
    \t<automount> \tEnable/disable automount function\n \
    \t<autodismount> \tEnable/disable autodismount function\n \
    \t<dismount> \tDismount a horse\n\n"
    
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
int Hgallop;
int hgallop(string str);


int
hhelp(string str)
{
    if (str == "saddlebag")
    {
        write(HHELP_BAG_MESSAGE);     /* defined in mm_stables.h */
        return 1;
    }
    
    write(HHELP_RIDER_MESSAGE);         /* defined in mm_stables.h */
    return 1;
}




int
hgallop(string str)
{
    return query_steed()->hgallop(str);
}

void
init()
{
    ::init();
    
    add_action(hhelp, "hhelp");
    add_action(hgallop, "hgallop");
}
