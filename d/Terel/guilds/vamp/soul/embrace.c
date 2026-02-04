/* embrace.c created by Shiva@Genesis
 * This file contians the code for the "embrace" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * Create a new vampire.
 */

#include "../guild.h"

inherit "/lib/commands";

int
embrace(string str)
{
    object embrace_sh, yn_ob;
    object *arg;
  
    if (!strlen(str) || (sizeof(arg = parse_this(str, "[the] %l")) != 1))
    {
        notify_fail("Embrace whom?\n");
        return 0;
    }
  
    if (!IS_VAMP(TP))
    {
        write("You are not a true vampire.\n");
        return 1;
    }
  
    if (!IS_BG(arg[0]))
    {
        write(arg[0]->query_The_name(TP) + 
            " is not a Bloodguard!\n");
        return 1;
    }

    if (arg[0]->query_master()!=TP->query_real_name())
    {
        write(arg[0]->query_The_name(TP) + 
            " is not your Bloodguard!\n");
        return 1;
    }
/* Restriction on age removed per CovenMaster Bofur on 8 Feb 2009
    //Must have been in the guild 5 days
    if (arg[0]->query_vamp_age()<3600*120 && !IS_JR(arg[0]))
    {
        write(arg[0]->query_The_name(TP) +
            " has not yet been a Bloodguard long enough "+
            "to embrace.\n");
        return 1;
    }
    //And at least 25 RL days
    if (arg[0]->query_vamp_time()<3600*600 && !IS_JR(arg[0]))
    {
        write(arg[0]->query_The_name(TP) +
            " has not yet been a Bloodguard long enough "+
            "to embrace.\n");
        return 1;
    }
*/
  
    actor("You offer your dark gift to", arg, ".");
    target(" offers you " + POSS(TP) + " dark gift, asking you " +
	"to give up your mortal life for the everlasting existence " +
	"of a vampire.\nDo you accept or refuse?\n", arg);
    all2actbb(" takes", arg, " to the side and asks " + 
	OBJ(arg[0]) + " something.\n");
  
    setuid();
    seteuid(getuid());
  
    if (embrace_sh = clone_object(SHADOW_DIR+"embrace_sh"))
    {
    	if (yn_ob = clone_object(YES_NO_OBJECT))
    	{
	    if (yn_ob->get_answer(arg[0], 
		&embrace_sh->response(, arg[0], TP), 20.0))
	    {
	        return 1;
	    }
	    else
	    {
	        yn_ob->remove_object();
	        embrace_sh->remove_embrace_sh();
	    }
    	}
    	else
    	{
  	    embrace_sh->remove_embrace_sh();
    	}
    }
  
    actor("For some reason, you can't bring yourself to embrace", arg, ".");
    return 1;
}
