/*
 * File Name        : pirate_soul.c
 * By               : Elmore.
 * Inspiration from : The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : Contains the soul for the pirate guild, the emotes
 *                    and help files.
 * 
 */ 

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "../local.h"
#include <composite.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
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
mapping
query_cmdlist()
{
    return ([
            /* Command name : Function name */
              "help"        : "help",
              "pgrip"       : "pgrip",
              "ptale"       : "ptale",
              "pstand"      : "pstand",
              "pstare"      : "pstare",
              "plaugh"      : "plaugh",
              "psmell"      : "psmell",
              "plook"       : "plook",
              "pgroan"      : "pgroan",
              "stab"        : "stab",
           ]);
}

/*
 * Function name: stab
 * Description:   This is the code for the "stab" command.
 *                This is a special attack.
 * Arguments:     The arguments the player gave to the "stab"
 *                command.
 * Returns:       1 / 0 - command succeeded / command failed
 */
int
stab(string str)
{
    object ob, *obj;
    string how;
 
    /* What are we attacking anyway? */
    if (strlen(str))
    {
        if (!sizeof(obj = parse_this(str, "[the] %l")))
        {
            notify_fail("Choose a more appropriate target.\n");
            return 0;
        }

        ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = this_player()->query_attack()))
    {
        notify_fail("But you aren't in battle with anyone!\n");
        return 0;
    }

    /* Does attacker have the skill? */
    if (!(this_player()->query_skill(SS_GUILD_SPECIAL_SKILL)))
    {
        write("First you should learn how.\n");
        return 1;
    }
 
    /* Is the attacker already busy? */
    if (this_player()->query_stab())
    {
        write("You are already preparing such an attack.\n");
        return 1;
    }
 
    /* Are we even allowed to attack it?  Use can_attack_with_lay_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_lay_special(ob, "stab")))
    {
        write(how);
        return 1;
    }
 
    /* The shadow takes care of the rest */
    this_player()->stab(ob);

    return 1;
}

int
help(string str)
{
    if (str == "sash")
    {
        write("The sash of the Pirates of the Bloodsea can do this:\n" +
        "------------------------------------------------------\n" +
        "- pstare         - <name> stares out to sea, searching for a rich ship \n"+
        "                    to plunder.\n" +
        "- plaugh         - <name> laughs coarsely like an old seadog.\n" +
        "- psmell         - <name> takes a deep breath, enjoying the salty sea \n"+
        "                    air.\n" +
        "- plook          - <name> thoughtfully looks up at the rigging.\n" +
        "- pgroan         - <name> groans loudly, disappointed at the loss of an \n"+
        "                    opportunity to loot and plunder.\n" +
        "- pstand         - <name> stands tall before you, confident upon the \n"+
        "                    deck of a ship in rough seas.\n" +
        "- ptale <target> - <name> turns to <target> and begins to spin a heroic \n"+
        "                    tale about the Bloodsea storms <he> has sailed through.\n" +
        "- pgrip          - <name> grips <his> weapon tightly, eager to plunder and \n"+
        "                    the smell of blood.\n" +
        "------------------------------------------------------\n" +
        "You can also wear and remove the sash.\n"+
        "Not much ey? Any ideas for emotes should be mailed "+
        "to Elmore.\n");
	return 1;
    }
    return 0;
}

int
pgrip(string str)
{
    if (str)
    {
       write("Just use 'pgrip' without any arguments\n");
    }
    if (!str)
    {
	write("You grip your weapon tightly, eager to plunder and the smell "+
              "of blood.\n");
	say(QCTNAME(TP) + " grips "+POSSESSIVE(TP)+" weapon tightly, eager "+
            "to plunder and the smell of blood.\n");
    }
    return 1;
}

int
ptale(string str)
{
    object *pers;
    if (!str)
    {
	write("Ptale at who?\n");
	return 1;
    }
    pers = parse_this(str, "[at] %l");
    NF("Psmile at who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " turns to you and begins to spin "+
	      " a heroic tale about the Bloodsea storms " +PRONOUN(TP)+
              "has sailed through.\n", pers + ({TP}));
    TP->catch_msg("You turn to " + QCOMPLIVE + " and begin to spin a heroic tale "+
              "about the Bloodsea storms "+PRONOUN(TP)+
              " has sailed through.\n");
    pers->catch_msg(QCTNAME(TP) + " turns to you and begins to spin a "+
            "heroic tale about the Bloodsea storms " +PRONOUN(TP)+
            "has sailed through.\n");
    return 1;
}

int
pstand(string str)
{
    object *pers;
    if (!str)
    {
	write("You stand tall, confident upon the deck of a ship in "+
              "rough seas.\n");
	say(QCTNAME(TP) + " stands tall before you, confident "+
            "upon the deck of a ship in rough seas.\n");
	return 1;
    }
    pers = parse_this(str, "[at] %l");
    NF("Pstand at who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " stands tall before you, confident "+
            "upon the deck of a ship in rough seas.\n", pers + ({TP}));
    TP->catch_msg("You stand tall, confident upon the deck of a ship in "+
              "rough seas.\n");
    pers->catch_msg(QCTNAME(TP) + " stands tall before you, confident "+
            "upon the deck of a ship in rough seas.\n");
    return 1;
}

int
pstare(string str)
{
    if (str)
    {
       write("Just use 'pstare' without any arguments.\n");
    }
    if (!str)
    {
	write("You stare out over the sea, searching for a rich ship to plunder.\n");
	say(QCTNAME(TP) + " stares out to sea, searching for a rich ship to "+
           "plunder.\n");
    }
    return 1;
}

int
plaugh(string str)
{
    if (str)
    {
       write("You only have to use 'plaugh' without any arguments.\n");
    }
    if (!str)
    {
	write("You laugh coarsely like an old seadog.\n");
	say(QCTNAME(TP) + " laughs coarsely like an old seadog.\n");
	return 1;
    }
    return 1;
}

int
psmell(string str)
{
    if (str)
    {
       write("You only have to use 'psmell' without any arguments.\n");
    }
    if (!str)
    {
	write("You take a deep breath, enjoying the salty sea air.\n");
	say(QCTNAME(TP) + " takes a deep breath, enjoying the salty sea air.\n");
	return 1;
    }
    return 1;
}

int
plook(string str)
{
    if (str)
    {
       write("You only have to use 'plook' without any arguments.\n");
    }
    if (!str)
    {
	write("You thoughtfully look up at the rigging..\n");
	say(QCTNAME(TP) + " thoughtfully looks up at the rigging.\n");
	return 1;
    }
    return 1;
}


int
pgroan(string str)
{
    if (str)
    {
       write("You only have to use 'pgroan' without any arguments.\n");
    }
    if (!str)
    {
	write("You groan loudly, disappointed at the loss of an "+
              "opportunity to loot and plunder.\n");
	say(QCTNAME(TP) + " groans loudly, disappointed at the loss "+
            "of an opportunity to loot and plunder.\n");
	return 1;
    }
    return 1;
}
