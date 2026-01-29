/* project.c created by Shiva@Genesis
 * This file contains the code for the "project" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * This command allows a vampire to project a tought to
 * another being in the room.  The target is given a chance
 * to notice who is projecting the message; if the target
 * fails he/she receives the message, but doesn't know
 * from whom it came.
 */

#include "../guild.h"
#include "abilities.h"
#include <tasks.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>

static int project2(object target, string msg);

static mixed
project(string arg)
{
    mixed *oblist;
    string who, msg;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what to whom?\n");
        return CMD_SYNTAX_FAILURE;
    }

    if (!parse_command(arg, all_inventory(environment(this_player())),
        "[to] [the] %l %s", oblist, msg) ||
        (sizeof(oblist = NORMAL_ACCESS(oblist - 
        ({ this_player() }), 0, 0)) != 1))
    {
        if (sscanf(arg, "%s:%s", who, msg) != 2)
        {
            notify_fail(capitalize(query_verb()) + " what to whom?\n");
            return CMD_SYNTAX_FAILURE;
	}
  
    	if (sizeof(oblist = parse_this(who, "[to] [the] %l")) != 1)
    	{
    	    notify_fail(capitalize(query_verb()) + " to whom?\n");
    	    return CMD_SYNTAX_FAILURE;
        }
    }
    else
    {
        who = oblist[0];
    }
  
    if (!levels_test())
    {
        return CMD_FAIL_WITHOUT_COST;
    }
  
    write("You focus your mind.\n");
    
    return &project2(oblist[0], msg);
}

static int
project2(object target, string msg)
{
    if (!target || !present(target, environment(this_player())))
    {
        write("You try to project a thought, but your target is lost.\n");
        return 0;
    }

    if ((this_player()->query_sire() == target->query_real_name()) ||
        (target->query_sire() == this_player()->query_real_name()))
    {
        write("You attempt to project a thought to " +
            target->query_the_name(this_player()) + ", but " +
            target->query_possessive() + " mind seems to be closed " +
            "to you.\n");
        return 0;
    }

    if (!success_test(0, this_player(), "vproject"))
    {
        return 0;
    }

    if (IS_WIZ(target) || IS_MEMBER(target) ||
        target->resolve_task(TASK_FORMIDABLE + 100, 
        ({ TS_WIS,SS_AWARENESS})) > 0)
    {
        target->catch_msg("\nYou sense " +
	    this_player()->query_the_name(target) + " invading your mind, " +
	    "attempting to project a thought to you: " + msg + "\n");
    }                      
    else
    {
        target->catch_msg("\nA thought passes through your mind: " +
	    msg + "\n");
    }
  
    write((this_player()->query_option(OPT_ECHO) ? "You project to " +
	target->query_the_name(this_player()) + ": " + msg : "Ok.") + "\n");
    return 1;
}

public int
break_project(object who)
{
    who->catch_tell("Your concentration is broken.\n");
    return 1;
}
