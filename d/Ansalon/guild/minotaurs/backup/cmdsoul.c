/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.c"


string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}


int 
query_cmd_soul() 
{ 
    return 1; 
}


mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */

      "gore"  :  "guildgore",

    ]) +emote_cmdlist();
}

int
guildgore(string str)
{
    object ob, *obj, *oblist;
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
    if(TP->query_gore())
    {
	write("Patience! You have not yet recovered from your " +
	  "last attack!\n");
	return 1;
    }


    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_lay_special(ob, "gore")))
    {
	write(how);
	return 1;
    }

    if(!TP->query_attack())
    {
        write("You raise your horned head and roar loudly to the heavens, eagerly " +
          "charging into glorious battle!\n");
        say(QCTNAME(TP)+ " raises " +HIS(TP)+ " horned head and roars to " +
          "the heavens, and charges into battle!\n");
    }

    if ( TP->query_prop(LIVE_O_LAST_KILL) != ob )
        TP->add_prop(LIVE_O_LAST_KILL, ob);
        
    /* The shadow takes care of the rest */
    this_player()->gore(ob);

    return 1;
}

