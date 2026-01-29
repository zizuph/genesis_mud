/* This file is seeker_soul.c 
 *
 * Based on the herald_soul from /d/Shire/heralds
 * -- Finwe, February 2006
 */

/*
 * Emote suggestions:

    Toby: <player> suddenly stands utterly still, robes rustling softly around his/her ankles, watching the <target> intently.

    Toby: <player> cleans a fleck of dirt from his/her robe.


 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/std/armour";

#include "defs.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define MORE(x)    this_player()->more(read_file(x, 2))

string
get_soul_id()
{
    return GUILD_NAME;
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

// command : routine_name
    return ([
      "help"        :   "help",
      "serobe"      :   "robe",
      "sesilence"   :   "silence",
      "sestreak"    :   "streak",

    ]);
}

int
help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "seeker":
	    MORE(GUILD_HELP + "help");
	    TP->catch_tell("Please report any problems you may encounter "+
	        "with the " + GUILD_NAME + " to " + 
	        COMPOSITE_WORDS(map(GUILD_MASTER, capitalize)) + ".\n");
	    break;
    case "seeker guild":
	    MORE(GUILD_HELP + "guild");
	    break;
    case "seeker emotes": 
    case "seeker emotions":
	    MORE(GUILD_HELP + "emotes");
	    break;
    case "seeker spells":
	    MORE(GUILD_HELP + "spells");
	    break;
    case "seeker titles":
	    MORE(GUILD_HELP + "titles");
	    break;
    case "seeker news":
	    MORE(GUILD_HELP + "news");
	    break;
    default:
	return 0;
    }
    return 1;
}

int
robe()
{
    object ob, *bodywear;

// Find worn cape or cloak
    bodywear =  this_player()->query_clothing(A_ROBE) ;
 
//if no cape or cloak, let them know
    if (TP->query_clothing(A_ROBE)) 
    {
        write("You must be wearing a robe or cloak first.\n");
        return 1;
    }


    write("Your robe flutters slightly around you.\n");
    say(CAP(QCTNAME(TP)) + " slightly around " + HIM_HER(TP) + ".\n");
    return 1;
}

int
silence(string str)
{

    object *oblist;
    if(!strlen(str) || str=="all" || str=="to all") /* no string supplied */
    {
    write("You motion everyone to be silent.\n");
    all(" motions everyone to be silent.");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist)|| str=="all")
    {
    write("Silence who?\n");
    return 1;
    }

    actor("You motion to",oblist," to be silent.");
    target(" motions you to be silent.", oblist);
    all2act(" motions before", oblist," to be silent.");
    return 1;

}


int
streak()
{
    write("You raise your hands above your head. Streaks of lightning " +
        "shoot from them in random directions.\n");
    say(QCTNAME(TP) + " raises " + HIS_HER(TP)+ " hands above " + 
        HIS_HER(TP) + " head. Streaks of lightning shoot from " + 
        HIS_HER(TP) + " hands in random directions.\n");
    return 1;
}
