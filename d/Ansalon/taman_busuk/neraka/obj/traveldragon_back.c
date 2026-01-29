/*
 * This is back of the dragonsteed in dragonarmies
 */
#pragma strict_types

inherit "/d/Ansalon/guild/dragonarmy/dragons/dragon_back";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <config.h>
#include <composite.h>

/*
 * Same as original, but let anyone list destinations, and not all
 * destinations should be available; only those that land in a restricted
 * dragon tower. Sanction, Neraka and Flotsam, as far as I know.
 */
int
destinations(string str)
{
    if(str)
    {
	    NF("What?\n");
	    return 0;
    }

    write("   --===Destinations===--\n\n"+
	    "          Sanction\n"+
	    "          Neraka\n" +
	    "          Flotsam\n"+
	    "\n");
    return 1;
}

/*
 * Changed from original: Dismounts everyone, not just everyone except
 * the summoner
 */
public void
dismount_all()
{
    int i;

    object *all = all_inventory(TO);
    for (i = 0; i < sizeof(all); i++)
    {
	    if (!living(all[i]))
    	    continue;

	    if (interactive(all[i]) || all[i]->query_npc())
	    {
	        all[i]->command("dismount dragon");
	        continue;
	    }

	    all[i]->move_living("M", OWN_STATUE, 1);
	    OWN_STATUE->set_revive_dest(all[i], file_name(E(dragon)));
    }
}

/*
 * Addition: removes the dragon as soon as it lands.
 */
public void
arrive(mixed dest)
{
    ::arrive(dest);

    tell_room(dest, "No sooner has the dragon landed, than it " +
        "leaps back into the air, flying away.\n");

    dragon->remove_object();
}

/*
 * Change: limit the destinations to "neraka" and "sanction"
 */

public int
fly(string instr)
{
    string str;

    NF(C(query_verb()) + " to where?\n");
    if(instr != "back" && !sscanf(instr, "to %s", str))
	    return 0;

    str = lower_case(str);
    if (str == "neraka" ||
        str == "sanction")
    {
        return ::fly(instr);
    }
    else
    {
        return 0;
    }
}
