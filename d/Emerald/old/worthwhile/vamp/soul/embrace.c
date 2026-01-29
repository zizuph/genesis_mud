/* embrace.c created by Shiva@Genesis
 * This file contians the code for the "embrace" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * Create a new vampire.
 */

#include "../guild.h"

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
  
    if (!IS_MEMBER(this_player()))
    {
        write("You are not a true vampire.\n");
        return 1;
    }
  
    if (IS_MEMBER(arg[0]))
    {
        write(arg[0]->query_The_name(this_player()) + 
            " is already a vampire!\n");
        return 1;
    }
  
    if (this_player()->thirst() > 10)
    {
        write("You cannot create another until you have fed.\n");
        return 1;
    }
  
    actor("You offer your dark gift to", arg, ".");
    target(" offers you " + POS(this_player()) + " dark gift, asking you " +
	"to give up your mortal life for the everlasting existence " +
	"of a vampire.\nDo you accept? (Yes/No)\n", arg);
    all2actbb(" takes", arg, " to the side and asks " + 
	OBJ(arg[0]) + " something.\n");
  
    setuid();
    seteuid(getuid());
  
    if (embrace_sh = clone_object(EMBRACE_SHADOW))
    {
    	if (yn_ob = clone_object(YES_NO_OBJECT))
    	{
	    if (yn_ob->get_answer(arg[0], 
		&embrace_sh->response(, arg[0], this_player()), 20.0))
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
