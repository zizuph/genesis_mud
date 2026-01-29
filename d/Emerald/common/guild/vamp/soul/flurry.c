/* flurry.c created by Shiva@Genesis
 * This file contains the code for the vampire guild "flurry" command.
 * This is part of the vampire guild soul.
 */


#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>

#define LIVE_M_NO_FLURRY  "_live_m_no_flurry"

int flurry(string str)
{
    mixed targets, prop, flurry_info;
    object who;
    string why;
    object *no_attack = ({});
    int i;
  
    NF("Execute a flurry of attacks at whom?\n");
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

        if (!sizeof(targets = COMMAND_DRIVER->parse_this(str, "[at] [the] %l")))
	{
  	    return 0;
    	}
    }
    else
    {
    	if (!(who = this_player()->query_attack()))
    	{
	    return 0;
    	}

	targets = ({ who });
    }
 
    /* 
    if (prop = QP(who, LIVE_M_NO_FLURRY))
    {
        write(stringp(prop) ? prop : "For some reason, you cannot manage " +
            "it.\n");
        return 1;
    }
    */
  
    /* If the attacker is already preparing to flurry, we shouldn't be 
     * able to execute another flurry command unless we're trying to
     * switch targets or hitlocs
     */
    flurry_info = this_player()->query_flurry();
    if (pointerp(flurry_info) &&
        ((sizeof(flurry_info[0]) != sizeof(targets)) ||
	 (sizeof(flurry_info[0] | targets) != sizeof(targets))))
    {
    	NF("You are already preparing for that.\n");
    	return 0;
    }

    if (!this_player()->query_flurry_reset())
    {
        NF("You have not yet recovered from your last flurry of attacks.\n");
	return 0;
    }

    /* Can't flurry while stunned */
    if (QP(this_player(), LIVE_I_STUNNED))
    {
    	write("You can't seem to manage it!\n");
    	return 1;
    }
  
    /* check for things blocking the attack */
    for (i = 0; i < sizeof(targets); i++)
    {
        if (stringp(why = this_player()->c_can_attack(targets[i], "flurry")))
        {
      	    write(why);
            no_attack += ({ targets[i] });
	}
    }

    targets -= no_attack;

    if (!sizeof(targets))
    {
        return 1;
    }
    /*
    if (this_player()->query_attack() != who)
    {  
    	say(QCTNAME(this_player()) + " attacks " + QTNAME(who) + ".\n",
    	    ({ this_player(), who }) );
    	tell_object(who, this_player()->query_The_name(who) + 
            " attacks you!\n");
    }
    */
  
    /* start the attack! */
    this_player()->flurry(targets);
  
    write("You prepare to attack " + COMPOSITE_LIVE(targets) + ".\n");
  
    return 1;
}

