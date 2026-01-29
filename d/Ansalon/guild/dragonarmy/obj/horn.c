/*
 * Created by Milan
 *
 * Modified 22.8.2000 by Milan
 * Dragonsteed summon costs 200 mana and 0 fatigue (was 250/30)
 * Still at least 30 fatigue points are required for success.
 * Also changed message timing (but overall summoning time left at 34 seconds)
 *
 * Navarre: September 16th 2006, Added check to allow dragonlanding when a mouse etc
 *                               is around. Only disallow for other players now.
 */


inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

public void
remove_dragonarmy_object()
{
    remove_object();
}

public void
create_object()
{
    set_name("horn");
    add_name("warhorn");
    add_name("_dragonarmy_horn");
    set_adj("brass");
    add_adj("dragonarmy");
    set_short("brass warhorn");
    set_long("This is a brass warhorn shaped into the " +
      "form of a cruel dragon, its wide-open maw bellowing " +
      "to the heavens." +
      " Along the length of it has been carved 'help dragonarmy'."+
      "\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 1750);
    add_prop(OBJ_I_VOLUME, 2000);
    remove_prop(OBJ_I_VALUE);
}

public int
blow(string str)
{
    int i;
    object *ob, *r1, *r2, *r3;
    string how, *adj;
    string *listhow = ({"long","deep","high","harsh","hollow",
			"vibrating","shrill","braying","ringing","threatening",
			"blaring","brassy","pealing","resonant" });

    if (!strlen(str) ||
      !parse_command(str, all_inventory(TP), "[the] %i %s", ob, how) ||
      !sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }
    if (sizeof(ob) > 1)
    {
	NF(C(query_verb()) + " what?  Be more specific.\n");
	return 0;
    }
    if(ob[0] != TO)
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }

    if(!strlen(how))
    {
	how = "deep";
    }
    adj = explode(how, " ") - ({""});
    for (i=0; i<sizeof(adj); i++)
	if(member_array(adj[i], listhow) < 0)
	{
	    NF(C(query_verb())+" "+short()+" how?\n");
	    return 0;
	}
    how = implode(adj, " ");
    write("You raise your brass warhorn to your " +
	"lips, and blow mightily into it. Its "+how+" wail echoes into " +
	"the distance.\n");
    say(QCTNAME(TP)+" raises "+HIS(TP)+" brass warhorn to "+
	HIS(TP)+" lips, and blows mightily into it. The warhorn's "+how+
	" wail echoes into the distance.\n");

    setuid();
    seteuid(getuid());
    r1 = FIND_NEIGHBOURS(E(TP), 2);
    r1 = r1 - ({E(TP)});
    r2 = FIND_NEIGHBOURS(r1, 2);
    r2 = r2 - r1 - ({E(TP)});
    r3 = FIND_NEIGHBOURS(r2, 4);
    r3 = r3 - r2 - r1 - ({E(TP)});
    for(i=0; i<sizeof(r1); i++)
	FILTER_PLAYERS(all_inventory(r1[i]))->catch_tell(
	    "The "+how+" wail of a warhorn echoes to you from nearby.\n");
    for(i=0; i<sizeof(r2); i++)
	FILTER_PLAYERS(all_inventory(r2[i]))->catch_tell(
	    "The "+how+" wail of a warhorn echoes throughout "+
	    "the lands around you.\n");
    for(i=0; i<sizeof(r3); i++)
	FILTER_PLAYERS(all_inventory(r3[i]))->catch_tell(
	    "The faint "+how+" wail of a warhorn echoes to you, calling "+
	    "it sounds from a distance.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(blow, "blow");
}

