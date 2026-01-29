/*
*  Code for general Ranger commands and Ranger-speak.
*
* Rlist command patched by Mercade, 14-09-1993
*/


#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>
#include "titles.h"
#include "/config/sys/local.h"

#define ADUNAIC_DIFF      60

int
is_ranger(object pl)
{
    int rb;

    if (!pl->query_npc())
    {
	return (IS_RANGER(pl) || IS_NRANGER(pl)); 
    }
    else
	return (pl->id("ranger"));
}

int
is_north_ranger(object pl)
{
    if (!pl->query_npc())
    {
	return IS_NRANGER(pl);
    }
    else
	return (pl->id("ranger"));
}

int
understand_adunaic(object pl)
{
    int  langsk = pl->query_skill(SS_LANGUAGE);

    if (is_ranger(pl) && (langsk > 10))
	return 1;
    else if (IS_DUNADAN(pl) && (langsk > 1))
	return 1;
    else if (langsk >= ADUNAIC_DIFF)
	return 1;
    else 
	return 0;
}

int
speak_adunaic(string str)
{
    string   cap_name;
    int      i,
    sobj;
    object  *obj;
    mixed    gag;

    if (!strlen(str)) 
    {
	NFN0("Say what in Adunaic?");
    }

    gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED);
    if (gag)
    {
	if (stringp(gag))
	    TP->catch_msg(gag);
	else if (intp(gag))
	    TP->catch_msg("You are unable to speak right now!\n");
	return 1;
    }

    if (TP->query_invis()) 
	cap_name = "Someone";
    str += " ";
    /*
     * Check take from /std/living/cmdhooks.c:
     * We do not want people to add too many spaces and use the grsay
     * command as a way to generate emotions themselves. However, we do
     * not want to waste this on wizards and we also test whether people
     * haven't used too many spaces. You cannot make an emotion with
     * only a few. This wildmatch is 40% faster than the explode/implode
     * stuff, so as long as people don't use 8 spaces more than 40% of
     * the time, this check pays itself back.
     */
    if (!TP->query_wiz_level() &&
      wildmatch("*       *", str))
    {
	str = implode((explode(str, " ") - ({ "" }) ), " ");
    }
    write("You speak in Adunaic: " + str + "\n");
    obj = all_inventory(environment(TP));
    sobj = sizeof(obj);
    while (i < sobj)
    {
	if ((living(obj[i])) && (obj[i] != TP))
	{
	    if (!understand_adunaic(obj[i]))
	    {
		if (CAN_SEE(obj[i],TP))
		    obj[i]->catch_msg(QCTNAME(TP)
		      + " says something in an unknown language.\n");
		else 
		    obj[i]->catch_msg("Someone says something in an "
		      + "unknown language.\n");
	    }
	    else
	    { 
		if (CAN_SEE(obj[i],TP))
		    obj[i]->catch_msg(QCTNAME(TP)
		      + " speaks in Adunaic: " + str + "\n");
		else
		    obj[i]->catch_msg("Someone speaks in Adunaic: "
		      + str +"\n");
	    }
	}
	i++;
    }
    return 1;
}

int
sort_ranger_rank(object obj1, object obj2)
{
    int     wl1 = SECURITY->query_wiz_rank(obj1->query_real_name()),
    wl2 = SECURITY->query_wiz_rank(obj2->query_real_name());
    int oblvl1, oblvl2;
    string  comp1,
    comp2;

    // Fix wizards first.
    if (wl1 && wl2)
    {
	if (wl1 == wl2)
	    return 0;
	return - ((wl1 > wl2) * 2 - 1);
    }
    else if (wl1)
	return -1;
    else if (wl2)
	return  1;

    FIX_EUID
    oblvl1 = obj1->query_ranger_rank(1);
    oblvl2 = obj2->query_ranger_rank(1);

    return ((oblvl1 > oblvl2) ? -1 : ((oblvl1 == oblvl2) ? 0 : 1));
    return  1;

}

int
list_active_rangers()
{
    int		i,
    cnt = 0;
    object	ring,
    *list;
    string	g_name,
            g_title,
            g_short;

    write("These Rangers of the North are currently in the realms:\n");

    /* select the ranger before you do anything else! */
    list = users();

#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    /* code from /cmd/live/social.c:
     * If there is a room where statues of linkdead people can be found,
     * we add that to the list, but only if the player did not ask to only
     * see the interactive players.
     */
    list += filter((all_inventory(find_object(OWN_STATUE)) - list), 
      &not() @ &->query_npc());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD

    list = filter(list, is_north_ranger);
    list = sort_array(list, "sort_ranger_rank");

    for (i = 0; i < sizeof(list); i++)
    {
	g_name = capitalize(list[i]->query_real_name());
	if (IS_NRANGER(list[i]))
	{
	    /* Don't want a jr's name on the guildlist */
	    if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
		continue;
	    if(!list[i]->query_invis())
	    {
            if (!(g_short = NORTH_MASTER->query_ranger_name(list[i]->query_real_name())))
                g_short = "";
		if (list[i]->query_wiz_level())
		{
		    g_title = list[i]->query_title();
		    if (interactive(list[i]))
		    {
			write("- " + g_name + " " + g_title +
                    (strlen(g_short) ? ", known as " + g_short : ""));
		    }
		    else
		    {
			write("* " + g_name + " " + g_title);
		    }
		}
		else
		{
		    if (list[i]->query_guild_family_name())
			g_name += " "+list[i]->query_guild_title_race();
		    g_title = list[i]->query_ranger_title(1);
		    if (interactive(list[i]) ||
		      list[i]->query_npc())
		    {
			write("- " + g_name + ", " + g_title +
                    (strlen(g_short) ? ", known as " + g_short : ""));
		    }
		    else
		    {
			write("* " + g_name + ", " + g_title +
                    (strlen(g_short) ? ", known as " + g_short : ""));
		    }
		}
		cnt++;
	    }
	    if (list[i]->query_invis() && TP->query_wiz_level())
	    {
		write("- (" + g_name + ")");
		cnt++;
	    }
	    if (list[i]->query_ghost())
		write(" <slain>");
	    if (!list[i]->query_invis() || TP->query_wiz_level())
		write("\n");
	}
    }
    if ( cnt > 1 )
	write("There are now "+cnt+" Rangers within these realms.\n");
    else
	write("There is now only one Ranger of the North on duty.\n");
    return 1;
}

int
ranger_intro_type(string str)
{
    if (!strlen(str))
    {
	write("Currently you introduce yourself with "
	  + ((TP->query_ranger_intro() == 1) ? "your full" : "only short")
	  + " title.\n");
	return 1;
    }
    if (str == "full" || str == "fully")
    {
	write("You will now show your full title.\n");
	TP->set_ranger_intro(1);
	return 1;
    }
    else if (str == "short" || str == "brief" || str == "briefly")
    {
	write("You will now show only the brief title.\n");
	TP->set_ranger_intro(0);
	return 1;
    }
    NF("Show how much of your Ranger-title?\n");
    return 0;
}

