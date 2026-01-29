/* ambush.c created by Shiva@Genesis August 18, 2001
 * This file contains the code for the vampire guild "slash" command.
 * This is part of the vampire guild soul.
 */

#include <macros.h>

public int
prepare(string str)
{
    mixed m;
    if (!strlen(str) ||
        !parse_command(str, ({}), "[to] [for] [an] [a] 'vambush' / 'ambush'"))
    {
        notify_fail("Prepare what?\n");
        return 0;
    }

    m = this_player()->prepare_ambush();
    if (!intp(m) || (m != 1))
    {
        write(stringp(m) ?
              m : "You are unable to set up an ambush right now.\n");
    }
    else
    {
        write("You begin to set up your ambush.\n");
    }

    return 1;    
}

public int
ambush(string str)
{
    object *oblist;
    object who;
    mixed why;

    if (strlen(str))
    {
        if (!sizeof(oblist = parse_this(str, "[the] %l")))
        {
            notify_fail("Ambush whom?\n");
            return 0;
        }

        if (sizeof(oblist) > 1)
        {
            notify_fail("You can only ambush one target at a time.\n");
            return 0;
        }

        who = oblist[0];
    }
    else
    {
        if (!(who = this_player()->query_attack()))
        {
            notify_fail("Ambush whom?\n");
            return 0;
        }
    }

    if (!this_player()->query_ambush_prepared())
    {
        write("You haven't properly prepared for an ambush.\n");
        return 1;
    }

    /* Can't slash while stunned */
    if (this_player()->query_prop(LIVE_I_STUNNED))
    {
    	write("You can't seem to manage it!\n");
    	return 1;
    }

    /* I guess someone might try this to block all special attacks...
     * I'll check just in case.
     */
    if (who->query_not_attack_me(this_player(), -1))
    {
    	write("You can't bring yourself to ambush " +
	    who->query_the_name(this_player()) + ".\n");
    	return 1;
    }

    /* check for other general things blocking the attack */
    if (stringp(why = this_player()->c_can_attack(who, "ambush")))
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

    this_player()->execute_ambush(who);
    return 1;
}
