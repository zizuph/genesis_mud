/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "guild.h"

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
    return "tutorial_guild"; 
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
              "gyell"   : "guildyell",
              "gwatch"  : "guildwatch",
              "gpunch"  : "guildpunch",
           ]);
}

/*
 * Function name: guildyell
 * Description:   This is the code for the "guildyell" command.
 *                This is a very simple emote, which takes no
 *                arguments.
 * Arguments:     The arguments the player gave to the "guildyell"
 *                command.
 * Returns:       1 / 0 - command succeeded / command failed
 */
int
guildyell(string str)
{
    if (strlen(str))
    {
        /* The player tried to specify an argument for the
         * command.  Return 0 since the command failed.  This
         * Will result in a "What?" message to the player.
	 */
        return 0;
    }

    /* message to the actor */
    write("You raise a mighty shout: For Silverdell!\n");

    /* message to others in the room */
    allbb(" raises a mighty shout: For Silverdell!");

    /* Command successful, so return 1 */
    return 1;
}

/*
 * Function name: guildwatch
 * Description:   This is the code for the "guildwatch" command.
 * Arguments:     The arguments the player gave to the "guildwatch"
 *                command.
 * Returns:       1 / 0 - command succeeded / command failed
 */
int
guildwatch(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Guildwatch whom?\n");
        return 0;
    }

    /* message to the actor.  Use actor() instead of write() when
     * The emote has a target
     */
    actor("You keep a close eye on", oblist, ", making sure nothing is"
      + " out of line here.");

    /* message to the target */
    target(" seems to be keeping an eye on you, wary of your"
      + " actions.", oblist);

    /* message to others present.  Use all2act() or all2actbb()
     * instead of all() or allbb() when the emote has a target. 
     */
    all2actbb(" seems to be keeping an eye on", oblist, ", wary of"
      + " their actions.");

    return 1;
}


/*
 * Function name: guildpunch
 * Description:   This is the code for the "guildpunch" command.
 *                This is a special attack.
 * Arguments:     The arguments the player gave to the "guildpunch"
 *                command.
 * Returns:       1 / 0 - command succeeded / command failed
 */
int
guildpunch(string str)
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
        write("First you will need to train that skill in the guildhall.\n");
        return 1;
    }
 
    /* Is the attacker already busy? */
    if (this_player()->query_punch())
    {
        write("You are already preparing such an attack.\n");
        return 1;
    }
 
    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_occ_special(ob, "punch")))
    {
        write(how);
        return 1;
    }
 
    /* The shadow takes care of the rest */
    this_player()->punch(ob);

    return 1;
}
