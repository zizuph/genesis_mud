#pragma no_shadow
#pragma strict_types
/*
 * - /d/Avenir/union/elder_soul.c
 *
 *  The Union Elder Soul
 *
 * Revisions:
 *   Lucius, Oct 2005: Updated the uadverb code, moved into adverbs.c
 *   Lucius, Jul 2011: Modified logging bits.
 *   Lucius, May 2016: Beefed up 'uassign' command.
 */
#include "defs.h"
#include <adverbs.h>

inherit "/cmd/std/command_driver";

private static mapping spheres = SPHERES;

/* Commands */
public mapping
query_cmdlist(void)
{
    return ([
	     "help" : "help",
	  "uassign" : "uassign",
	  "uadverb" : "uadverb",
    ]);
}

/* Id and autoload */
public string
get_soul_id(void)	{ return "Union_Elder"; }

/* It is a real command soul */
public int
query_cmd_soul(void)	{ return 1; }

private void
elderlog(string str)	{ LOG_COUNC(str); }

private void
uassign_help(void)
{
    write("You may assign the following Sphere to a Member of the Union:\n");

    foreach(string sph: sort_array(m_indexes(spheres)))
	write(sprintf("%20s : %s\n", CAP(sph), "Sphere of " + spheres[sph]));

    write("\nSyntax: uassign <sphere> [to] <whom> [offline]\n"+
	" ** Specify 'offline' to have the change take effect next login.\n");
}

private void
elders_help(void)
{
    write("Elder commands:\n");
    write("help     - Help <uassign|sphere|spheres|elders>.\n");
    write("uassign  - Reassign someones sphere.\n");
    write("uadverb  - Add/Remove Union specific adverbs.\n");
    write("\n");
}

public int
help(string str)
{
    if (str == "uassign" || str == "spheres" || str == "sphere")
    {
        uassign_help();
        return 1;
    }

    if (str == "elder" || str == "elders")
    {
	elders_help();
	return 1;
    }

    return 0;
}

public int
uassign(string str)
{
    int flag;
    object who;
    string *strs;

    notify_fail("Assign which sphere to whom?  See also: <uassign help>\n");

    if (!strlen(str))
	return 0;

    str = lower_case(str);

    if (str == "help")
    {
	uassign_help();
	return 1;
    }

    strs = explode(str, " ") - ({ "to" });

    if ((flag = sizeof(strs)) < 2)
	return 0;

    if (!spheres[strs[0]])
    {
	if (!spheres[strs[1]])
	    return 0;

	/* Reversed order, be kind and reorder. */
	str = strs[1];
	strs[1] = strs[0];
	strs[0] = str;
    }

    if (strs[1] == "me" || strs[1] == "myself")
    {
	who = this_player();
	strs[1] = who->query_real_name();
    }
    else if (!LIST->query_is_member(strs[1]))
    {
	if (sizeof(LIST->query_expelled(strs[1])))
	    write(CAP(strs[1]) +" is marked for expulsion from the Union.\n");
	else
	    write(CAP(strs[1]) +" is not a member of the Union.\n");

	return 1;
    }
    else who = find_player(strs[1]);

    if (flag == 3 && strs[2] == "offline")
	flag = 0;

    if (objectp(who) && flag)
    {
	string soul, old = who->query_union_sphere();

	if (old == strs[0])
	{
	    write("They already belong to that Sphere!\n");
	    return 1;
	}

	/* Make sure the new soul exists. */
	soul = UNION + "spheres/"+ strs[0] + "_soul";
	if (file_size(soul + ".c") == -1)
	{
	    write("There is an error with that Sphere. "+
		"Leave a bug report.\n");
	    return 1;
	}

	/* Change the sphere. */
	if (!who->set_union_sphere(strs[0]))
	{
	    write("There was an error assigning that Sphere.\n");
	    return 1;
	}

	/* Add the new soul. */
	who->add_cmdsoul(soul);
	/* Remove the old soul */
	soul = UNION +"spheres/"+ old + "_soul";
	who->remove_cmdsoul(soul);
	/* Now update the souls */
	who->update_hooks();
    }
    else
    {
	string old = LIST->query_union_sphere(strs[1]);

	if (old == strs[0])
	{
	    write("They already belong to that Sphere!\n");
	    return 1;
	}

	if (!LIST->set_union_sphere(strs[1], strs[0]))
	{
	    write("There was an error assigning that Sphere.\n");
	    return 1;
	}
    }

    elderlog(NM(TP) + " reassigned " + CAP(strs[1]) + " to Sphere: " +
	CAP(spheres[strs[0]]));

    write(CAP(strs[1]) +" is now of the Sphere: "+ spheres[strs[0]] +"\n");
    return 1;
}

public nomask int
uadverb(string str)
{
    string *arr;
    int bad = 1;

    if (!strlen(str) || !sizeof(arr = explode(str, " ")))
    {
	NF("Syntax: uadverb a[dd] | d[elete] | l[ist] | u[pdate] <adverb>\n"+
	   "                ar <adverb> <replacement> | dr <adverb>\n");
        return 0;
    }
    
    if (arr[0][0] == '-')
	arr[0] = arr[0][1..];

    switch(arr[0])
    {
    case "a": case "add":
	if (sizeof(arr) != 2)
	    break;

	if (UADVERBS_FILE->update_adverbs(1, arr[1]))
	{
	    write("Added adverb '"+ arr[1] +"' to the master list.\n");
	    elderlog(NM(TP) + " added new adverb: "+ arr[1]);
	} else {
            write("The adverb '"+ arr[1] +"' already exists.\n");
	}

	--bad;
	break;

    case "ar":
	if (sizeof(arr) < 3)
	    break;

	if (UADVERBS_FILE->update_adverbs(2, arr[1], arr[2..]))
	{
	    write("Added replacement '"+ arr[1] +"' to the master list.\n");
	    elderlog(NM(TP) + " added replacement adverb: "+
		arr[1] +" -> "+ implode(arr[2..], " "));
	} else {
            write("The replacement '"+ arr[1] +"' already exists.\n");
	}

	--bad;
	break;

    case "d": case "delete":
	if (sizeof(arr) != 2)
	    break;

	if (UADVERBS_FILE->update_adverbs(3, arr[1]))
	{
	    write("Removed adverb '"+ arr[1] +"' from the master list.\n");
	    elderlog(NM(TP) + " removed adverb: "+ arr[1]);
	} else {
            write("The adverb '"+ arr[1] +"' doesn't exist.\n");
	}

	--bad;
	break;

    case "dr":
	if (sizeof(arr) != 2)
	    break;

	if (UADVERBS_FILE->update_adverbs(4, arr[1]))
	{
	    write("Removed replacement '"+ arr[1] +"' from the master list.\n");
	    elderlog(NM(TP) + " removed replacement adverb: "+ arr[1]);
	} else {
            write("The replacement '"+ arr[1] +"' doesn't exist.\n");
	}

	--bad;
	break;

    case "l": case "list":
	if (sizeof(arr) != 2)
	    str = "all";
    	else
	    str = arr[1];

	write(UADVERBS_FILE->show_adverbs(str, 1));
	--bad;
	break;

    case "u": case "update":
	UADVERBS_FILE->update_adverbs();
        write("The adverbs listings have been syncronized.\n");
	elderlog(NM(TP) + " syncronized the uadverbs list.");
	--bad;
	break;
    default:
	break;
    }

    if (bad)
    {
	NF("Syntax: uadverb a[dd] | d[elete] | l[ist] | u[pdate] <adverb>\n"+
	   "                ar <adverb> <replacement> | dr <adverb>\n");
        return 0;
    }

    return 1;
}
