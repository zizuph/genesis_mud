/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../guild.h"
#include <macros.h>

/* 
 * Function name: get_soul_id
c
 * Description:   Give a name for this soul. Should be a short single word.
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return GUILD_NAME; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int 
query_cmd_soul() 
{ 
    return 1; 
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
public mapping
query_cmdlist()
{
    return ([
        /* Command name : Function name */
        "eharm"         : "do_ability",
		"eparanoia"     : "do_ability",
        "eregeneration" : "do_ability",
        "eshapeshift"   : "do_ability",
        // Emotes
        "dhelp"         : "dhelp",
        "dflap"         : "dflap"
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "eharm"         : GUILD_SPELLS + "harm",
        "eparanoia"     : GUILD_SPELLS + "paranoia",
        "eregeneration" : GUILD_SPELLS + "regeneration",
        "eshapeshift"   : GUILD_SPELLS + "shapeshift",
    ]);
}

public int
dflap(string str)
{
    if (strlen(str))
    {
        notify_fail("You can't flap your wings at someone.\n");
        return 0;
    }
    if (TP->query_drac_type() == "aurak")
    {
        notify_fail("Being an aurak, you don't have any wings.\n");
        return 0;
    }
    // Flap your wings
    write("You flap your huge leather-like draconian wings. Sand and dust fills "+
	      "the entire area.\n");
    allbb(" flaps " + TP->query_possessive() + " huge leather-like draconians wings."+
	      " Sand and dust fills the entire area.");
    return 1;
}

int
dhelp(string str)
{
	if (str == "draconians" || str == "draconian")
    {
		write("Draconian of Krynn\n");
		write("---------------------------------------\n");
		write("'dhelp history'    Creation of the draconian race.\n");
		write("'dhelp races'      Different draconian races.\n");
		write("'dhelp emotes'     Emotes that the draconians have.\n");
		write("'dhelp skills'     Skills that the draconians have.\n");
		write("'dhelp spells'     Spells that the draconians have.\n");
		return 1;
	}
    if (str == "history")
    {
		write("Draconian history\n");
		write("---------------------------------------\n");

		return 1;
	}
    if (str == "races")
    {
		write("Draconian races\n");
		write("---------------------------------------\n");
		write("Baaz: \n");
		write("Kapak: \n");
		write("Bozak: \n");
		write("Sivak: \n");
		write("Aurak: \n");

		return 1;
	}
    if (str == "emotes")
    {
		write("Draconian emotes\n");
		write("---------------------------------------\n");
		write("'dflap'     Flap your wings.\n");

		return 1;
	}
    if (str == "skills")
    {
		write("Draconian skills\n");
		write("---------------------------------------\n");

		return 1;
	}
    if (str == "spells")
    {
		write("Draconian spells\n");
		write("---------------------------------------\n");

		return 1;
	}
	return 0;
}