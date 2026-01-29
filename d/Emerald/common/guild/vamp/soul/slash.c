/* slash.c created by Shiva@Genesis
 * This file contains the code for the vampire guild "slash" command.
 * This is part of the vampire guild soul.
 */

/* Description
 * ===========
 * 
 * Slash is a fairly standard special attack, which simply does
 * slashing damage.  The attacker can specify a specific hitloc
 * to slash at, which is particularly important since slash is
 * very weak against heavier armours (ac above 15).  
 */

#include "../guild.h"
#include <macros.h>
#include <cmdparse.h>
#include "/std/combat/combat.h"
#include <wa_types.h>

#define LIVE_M_NO_SLASH  "_live_m_no_slash"
#define VAMP_I_SLASH_LOC "_vamp_i_slash_loc"
#define TARGET   0
#define ALARM_ID 1

int slash(string str)
{
    mixed *oblist, prop, slash_info;
    object who, combat_ob;
    string *hitloc_descs, who_str, where, why;
    int *hitloc_ids, hitloc, i;
  
    NF("Slash at whom?\n");
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        return 0;
    }
  
    if (strlen(str))
    {
	/* Nasty little bit of code to parse the input string.
	 * We accept the following:
	 * [at] [the] <hitloc> of [the] <target>
	 * [at] [the] <target>'s <hitloc>
	 * [at] [the] <hitloc>
	 * [at] [the] <target>
	 */

    	if (!parse_command(str, all_inventory(environment(this_player())),
	    "[at] [the] %s 'of' [the] %l", where, oblist) || 
	    !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0) - 
	    ({ this_player(), 0 })))
    	{
	    if (sscanf(str, "%s's %s", who_str, where) != 2)
	    {
	    	if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
	    	{
		    if (!(who = this_player()->query_attack()) ||
			!parse_command(str, ({ }), "[at] [the] %s", where))
		    {
		        return 0;
		    }
	    	}
	    	else
	    	{
		    who = oblist[0];
	    	}

		/*	      
	    	if (!parse_command(str, ({ }), "[at] [the] %s", where))
	    	{
		    return 0;
	    	}
		*/
	    }
	    else
	    {
	    	if (!parse_command(who_str, all_inventory(environment(this_player())),
		    "[at] [the] %l", oblist) || !sizeof(oblist = 
		    NORMAL_ACCESS(oblist - ({ this_player() }), 0, 0)))
	    	{
		    return 0;
	    	}
      	
	    	who = oblist[0];
	    }
    	}
    	else
    	{
  	    who = oblist[0];
    	}
    }
    else
    {
    	if (!(who = this_player()->query_attack()))
    	{
	    return 0;
    	}
    }
  
    if (prop = QP(who, LIVE_M_NO_SLASH))
    {
        write(stringp(prop) ? prop : "For some reason, you cannot manage " +
            "it.\n");
        return 1;
    }
  
    /* We've figured out whom to hit and where to hit...now make sure
     * that the place we want to hit is a valid hitloc on the target.
     */
  
    combat_ob = who->query_combat_object();
    hitloc_ids = combat_ob->query_hitloc_id();
    hitloc_descs = map(hitloc_ids, 
	&operator([])(, HIT_DESC) @ &combat_ob->query_hitloc());
  
    if (!sizeof(hitloc_ids))
    {
    	notify_fail("There is no place to slash!\n");
    	return 0;
    }
  
    if (strlen(where))
    {
    	int index = -1;

    	for (i = sizeof(hitloc_descs); i--;)
    	{
	    if (where == hitloc_descs[i])
	    {
	    	/* We've found an exact match, so we can stop looking */
	    	index = i;
	    	break;
	    }
      
	    if (strlen(hitloc_descs[i]) &&
		wildmatch(hitloc_descs[i], "*" + where + "*"))
	    {
	    	/* matched a hitloc, but it's not an exact match.  Keep
	    	 * looking in case there's a better match.
	    	 */
	    	index = i;
	    }
    	}
	  
    	if (index < 0)
    	{
	    notify_fail("You can't slash " + who->query_the_name(this_player()) +
		" there.\n");
	    return 0;
    	}

        hitloc = hitloc_ids[index];
    }
    else
    {
        /* No hitloc was specified, so check to see if our default one
         * is valid.
         */

        hitloc = this_player()->query_prop(VAMP_I_SLASH_LOC);

        if (member_array(hitloc, hitloc_ids) < 0)
        {
	    /* Our default hitloc is invalid, so choose one at random */
    	    hitloc = hitloc_ids[random(sizeof(hitloc_ids))];
	}
    }
  
    /* Okay...we've found a valid hitloc.  Now we need to check to
     * be sure that we're allowed to perform this attack.
     */
  
  
    /* If the attacker is already preparing to slash, we shouldn't be 
     * able to execute another slash command unless we're trying to
     * switch targets or hitlocs
     */
    slash_info = this_player()->query_slash();
    if (pointerp(slash_info) && 
	(slash_info[0] == who) && 
	(slash_info[1] == hitloc))
    {
    	NF("You are already preparing for that.\n");
    	return 0;
    }
  
    /* Can't slash while stunned */
    if (QP(this_player(), LIVE_I_STUNNED))
    {
    	write("You can't seem to manage it!\n");
    	return 1;
    }
  
    /* Can't slash unless there is a free hand */
    if (this_player()->query_tool(W_RIGHT) &&
        this_player()->query_tool(W_LEFT))
    {
    	write("You have too many things in your hands for that!\n");
    	return 1;
    }
  
    /* I guess someone might try this to block all special attacks...
     * I'll check just in case.
     */
    if (who->query_not_attack_me(this_player(), -1))
    {
    	write("You can't bring yourself to slash at " + 
	    who->query_the_name(this_player()) + ".\n");
    	return 1;
    }
  
    /* check for things blocking the attack */
    if (stringp(why = this_player()->c_can_attack(who, "slash")))
    {
    	write(why);
    	return 1;
    }

    if (this_player()->query_attack() != who)
    {  
    	say(QCTNAME(this_player()) + " attacks " + QTNAME(who) + ".\n",
    	    ({ this_player(), who }) );
    	tell_object(who, this_player()->query_The_name(who) + 
            " attacks you!\n");
    }
  
    /* start the attack! */
    this_player()->slash(who, hitloc);
  
    /* store the hitloc as a prop on the attacker.  This will be used later
     * as a default hitloc, which saves some typing if the attacker tends
     * to use the same hitloc often.
     */
    AP(this_player(), VAMP_I_SLASH_LOC, hitloc);
  
    write("You prepare to slash at " + who->query_the_name(this_player()) +
	".\n"); 
  
    return 1;
}

