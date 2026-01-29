/* telepath.c created by Shiva@Genesis
 * This file contains the code for the "telepath" command, the guild tell
 * line.
 * This file is a subpart of the vampire guild soul
 */

#include "../guild.h"
#include "abilities.h"
#include <options.h>

private static mapping messages = ([]);

static int can_hear(object ob1, object ob2);
static void telepath2(object *targets, string message);

static mixed 
telepath(string str)
{
    string who, message;
    object target;

    if (str == "remember")
    {
        mixed *msgs = messages[this_player()->query_real_name()];
        int i, scrw, maxname;

        if (!sizeof(msgs))
	{
            write("You can't remember having received any telepathic " +
                  "messages recently.\n");
            return 1;
	}

        if (sizeof(msgs) == 1)
	{
            write("You search your memory and recall having received one " +
                "telepathic message from " + msgs[0][0] + ": " + msgs[0][1] +
                "\n");
            return 1;
	}

        maxname = applyv(max, map(msgs, strlen @ &operator([])(, 0)));
        scrw = max(this_player()->query_option(OPT_SCREEN_WIDTH), 40);

        write("You search your memory and recall having received several " +
            "telepathic messages:\n");

        for (i = 0; i < sizeof(msgs); i++)
	{
            write(sprintf("From %-" + (maxname + 1) + "s %-=" +
                (scrw - maxname - 7) + "s\n", msgs[i][0] + ":", msgs[i][1]));
	}

        return 1;
    }        

    if (!strlen(str) || (sscanf(str, "%s %s", who, message) != 2))
    {
        notify_fail("Telepath <target> <message>\n");
        return CMD_SYNTAX_FAILURE;
    }
  
    who = lower_case(who);
   
    if (who == this_player()->query_real_name())
    {  
        write("You cannot telepath to yourself!\n");
        return CMD_FAIL_WITHOUT_COST;
    }
  
    if (this_player()->vamp_busy())
    {  
        write("Your mind is blocked from communication with other " +
            "vampires.\n");
        return CMD_FAIL_WITHOUT_COST;
    }
  
    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }
  
    if ((this_player()->query_vamp_stat() <= 30) && !success_test())
    {
        return CMD_FAIL_WITH_COST;
    }
  
    target = find_player(who);
  
    if (!target && (who == "all") && IS_WIZ(this_player()))
    {
        return &telepath2(VAMPS(users()) - ({ this_player() }), message);
    }
  
    if (!can_hear(this_player(), target))
    {
        write("You can't seem to communicate with " + capitalize(who) + ".\n");
        return CMD_FAIL_WITH_COST;
    }

    return &telepath2(({ target }), message);
}

static int
telepath2(object *targets, string message)
{
    int i;
    mixed *msgs;

    if (!sizeof(targets -= ({ 0 })))
    {
        write("You communicated with no-one.\n");
        return 0;
    }

    targets->catch_tell(METNAME + 
        " communicates telepathically: " + message + "\n");

    write((this_player()->query_option(OPT_ECHO) ? 
        "You communicate telepathically: " + message + "\n" : "Ok.\n"));

    for (i = 0; i < sizeof(targets); i++)
    {
        msgs = messages[targets[i]->query_real_name()];
        if (!sizeof(msgs))
        {
  	    msgs = ({ ({ METNAME, message }) });
	}
	else
	{
            if (sizeof(msgs) > 9)
	    {
                msgs = msgs[-9..];
            }

            msgs += ({ ({ METNAME, message }) });
	}

        messages[targets[i]->query_real_name()] = msgs;
    }

    return 1;
}

static int can_hear(object ob1, object ob2)
{
    int stat;
  
    if (!ob2 || !interactive(ob2))
    {
        return 0;
    }
  
    if (ob1->query_wiz_level())
    {
        return 1;
    }
  
    if (!IS_MEMBER(ob2))
    {
        return 0;
    }
  
    if (ob2->query_wiz_level())
    {
    	if (ob2->query_invis())
    	{
    	    return 0;
    	}
    
    	return 1;
    }
  
    if (ob2->thirst() > 100)
    {
        return 0;
    }
  
    if (ob2->vamp_busy())
    {
        return 0;
    }
  
    if ((ob2->query_sire() == ob1->query_real_name()) ||
        (ob1->query_sire() == ob2->query_real_name()))
    {
        return 0;
    }
  
    stat = ob2->query_vamp_stat();
  
    if ((stat > 20) || ((stat > 5) && (ob2->power_check(10) > 0)))
    {
        return 1;
    }
  
    return 0;
}

int vbusy(mixed arg)
{  
    return 0;
}
