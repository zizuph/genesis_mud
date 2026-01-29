/*
 * Red Robed Wizard of High Sorcery Soul
 *
 * First prototype by Rastlin.
 * Emotes has been suggested by Alustrial, Teth
 * and Jeremiah.
 *
 * Note: When adding commands to the soul, think of the
 * gender of the actor. The appearens might be different.
 */

/*
 * NOTE:
 *  wfinger - doesn't work properly.. Shamus's fingers->Shamus' fingers
 *  wpouch - (see wfinger) Do we need the emote at all?
 *  wsilent - Fix this emote, need to hood the player
 */
#pragma no_clone
#pragma strict_types
#pragma save_binary
#pragma no_shadow

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <const.h>
#include <language.h>
#include "../local.h"
#include "../../local.h"
#include "../obj/common_soul.c"

/*
 * Return a proper name of the soul in order to get a nice printout.
 */
public string 
get_soul_id() 
{ 
    return "Red Robed Mage"; 
}

/* 
 * The type of soul 
 */
public int 
query_cmd_soul()
{ 
    return 1;
}

/*
 * The list of verbs and functions. Please add new in alphabetical order.
 */
public mapping
query_cmdlist()
{
    return ([ "wconcern" : "wconcern",
	        "wcurse" : "wcurse",
                 "wlook" : "wlook", 
	       "wpraise" : "wpraise",
	        "wsmile" : "wsmile",
           ]) + query_common_cmdlist();
}


/*
 * Here follows the actual functions. Please add new in alphabetical order.
 */
public int
wconcern(string str)
{
    object *oblist;

    if (strlen(str))
        return NF("Concerned about what?\n");

    write("You considers the balance of good and evil in the world for a " +
	  "moment.\n");
    all(" considers the balance of good and evil in the world for a " +
	"moment, then looks gravely concerned.");

    return 1;
}

public int
wcurse(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
        return NF("Curse whom?\n");

    target(" curses you in the name of Lunitari!", oblist);
    actor("You curse", oblist, " in the name of Lunitari!");
    all2act(" curses", oblist, " in the name of Lunitari!");

    return 1;
}

public int
wlook(string str)
{
    if (strlen(str))
        return NF("Look at what?\n");

    write("You look upward, into the sky, searching for your master, " +
          "the red moon, Lunitari.\n");
    all(" gazes up into the sky, apparently searching for something.");

    return 1;
}

public int
wpraise(string str)
{
    if (strlen(str))
        return NF("Praise what?\n");

    write("You praise Lunitari for your good fortune.\n");
    all(" sends a praise to Lunitari for " + POSSESSIVE(TP) + " good " +
	"fortune.");
    return 1;
}

public int
wsmile(string str)
{
    if (strlen(str))
        return NF("Smile how?\n");

    write("You smile indifferently regarding the decision at hand.\n");

    all(" smiles indifferently regarding the decision at hand.");
    return 1;
}
