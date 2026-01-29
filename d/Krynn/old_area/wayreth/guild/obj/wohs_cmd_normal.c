/*
 * The normal command soul.
 *
 * It holds all the commands a normal Wizard of High Sorcery gets.
 */

/*
 * TODO:
 */

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <language.h>
#include <std.h>
#include <composite.h>
#include "../local.h"
#include "../../local.h"

#define GET_LEVEL(x)  ((x->query_wiz_level()) ? \
		       1000 + SECURITY->query_wiz_level(x->query_real_name()) \
		       : x->query_wohs_order_level())

#define MAX_KNOWN_DESTS  this_player()->query_wohs_level()

/*
 * The name of the soul.
 */
public string 
get_soul_id() { return "Commands of WoHS"; }

/*
 * It is a command soul.
 */
public int 
query_cmd_soul() 
{ 
    setuid();
    seteuid(getuid());

    return 1; 
}

/*
 * The list of verbs and functions. Please add new in alfabetical order.
 */
public mapping
query_cmdlist()
{
    return ([
	     "wdestination" : "wdestination",
	     "winvite" : "winvite",
	     "wlist" : "wlist",
	     ]);
}

/*
 * Here follows the actual functions. Please add new in alphabetical order.
 */
static int
sort_level(object a, object b)
{
    int lv1, lv2;

    lv1 = GET_LEVEL(a);
    lv2 = GET_LEVEL(b);

    if (lv1 == lv2)
    {
        if (a->query_real_name() > b->query_real_name())
	    return 1;
	else
	    if (a->query_real_name() == b->query_real_name())
	        return 0;
    }
    else
      if (lv1 > lv2)
	  return 1;

    return -1;
}

public int
wdestination(string str)
{
    string *dests = ADMIN->query_wohs_destinations(TP);
    int remove;
    string type = ADMIN->query_member_order(RNAME(TP));

    if (ADMIN->query_member_type(TP) == TYPE_APPRENTICE)
        return 0;

    if (!str || !strlen(str))
    {
	if (!sizeof(dests))
	{
	    write("You haven't memorized any destinations.\n");
	    return 1;
	}

        write("Remembered destinations:\n");
	write(COMPOSITE_WORDS(dests) + ".\n");
	return 1;
    }

    if (sscanf(str, "-%s", str))
        remove = 1;

    if (remove)
    {
        if (member_array(str, dests) == -1)
	    write("Unknown destination \"" + str + "\".\n");
	else
	{
	    ADMIN->remove_wohs_destination(TP, str);
	    write("Destination \"" + str + "\" has been forgotten.\n");
	}

	return 1;
    }

    if (sizeof(dests) == MAX_KNOWN_DESTS)
    {
        write("You can only memorise " + LANG_WNUM(MAX_KNOWN_DESTS) +
	      " destinations.\n");
	return 1;
    }

    if (E(TP)->query_prop(ROOM_I_NO_TELEPORT))
    {
        write("This area contains a magical instability that will not " +
	      "allow you to teleport here.\n");
	return 1;
    }

    ADMIN->add_wohs_destination(TP, str);
    write("Location memorised as \"" + str + "\".\n");

    return 1;
}

public int
winvite(string str)
{
    object *oblist, charm;

    if (!str || !strlen(str))
        return NF("Invite whom?\n");

    if (!THIS_GUILD(TP))
        return NF("Invite is for true members only.\n");

    if (ADMIN->query_member_type(TP) == TYPE_APPRENTICE)
        return NF("An apprentice is not trusted to handle such " +
		  "kind of magic.\n");

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
	return NF("Invite whom?\n");

    if (sizeof(oblist) > 1)
        return NF("Be a little more specific of whom you want to invite.\n");

    if (ADMIN->check_banned(oblist[0]))
        return NF("Somehow you get the feeling that your magic wouldn't " +
		  "work here.\n");

    if (THIS_GUILD(oblist[0]))
        return NF("That would be a waste of your magical power.\n");

    if (oblist[0]->query_prop(LIVE_I_AM_INVITED))
        return NF("Why invite someone that is already invited.\n");

    target(" presses " + POSSESSIVE(TP) + " lips against your " +
	   "forehead, giving you the charm that will allow you to " +
	   "reach the Tower of Wayreth.", oblist);

    write("You press your lips against " + POSSESSIVE(oblist[0]) + 
	  " forehead, giving " + OBJECTIVE(oblist[0]) + " the charm " +
	  "to enter the Tower.\n");

    all2act(" presses " + POSSESSIVE(TP) + " lips against", oblist,
	    "'s forehead.");

    setuid();
    seteuid(getuid());

    charm = clone_object(WOHS_CHARM);
    charm->set_duration(900);
    charm->move_spell(TP, oblist[0]);

    return 1;
}

public int
wlist()
{
    int size, cnt = 0;
    string str, name, list = "";
    object *mages = filter(users(), &->query_is_wohs());

    mages = sort_array(mages, sort_level);

    size = sizeof(mages);

    while (size--)
    {
        name = mages[size]->query_real_name();

	if (mages[size]->query_invis())
	{
	    if (TP->query_wiz_level())
	    {
	        list += "(" + C(name) + ")\n";
		cnt++;
	    }
	}
	else
        {
	    if (mages[size]->query_wiz_level())
	    {
	        list += SECURITY->query_wiz_pretitle(name) + " " + C(name) +
		        (strlen(str = mages[size]->query_title()) ? " " + 
			 str : "") + "\n";
	    }
	    else
	        list += (strlen(str = mages[size]->query_wohs_pretitle()) ?
			 str + " " : "") + C(name) + 
		        " the " + mages[size]->query_wohs_title() + "\n";
	    cnt++;
	}
    }

    if (cnt == 1)
        list = "There is presently only one Wizard of High Sorcery " +
	  "playing.\n" + list;
    else 
        list = "There are now " + LANG_WNUM(cnt) +
	  " Wizards of High Sorcery playing.\n" + list;

    write(list);
    return 1;
}






