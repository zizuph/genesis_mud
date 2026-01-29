#include "trickster.h"
#include "titles.h"
#include "/d/Shire/sys/defs.h"
//Stolen ruthlessly from the Rangers' rcomm.h!

int
sort_list(object a, object b)
{
    if (a->query_trickster_level() < b->query_trickster_level())
	return 1;
    if (a->query_trickster_level() > b->query_trickster_level())
	return -1;

    return (a->query_real_name() < b->query_real_name() ? -1 : 1);
}

int
list_active_tricksters()
{
    string g_name, g_short;
    int i;
    int level;
    int guild_stat, average_stat;
    int cnt = 0;
    object *list;

    write("These Tricksters are around somewhere:\n");
    list = filter(users(), &operator(==)(TRICKSTER_GUILD_NAME) @
      &->query_guild_name_lay());
    list = sort_array(list, "sort_list");

    for (i = 0; i < sizeof(list); i++)
    {
	g_name = capitalize(list[i]->query_real_name());
	/* Don't want a jr's name on the guildlist */
	if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
	    continue;
	if(!list[i]->query_invis())
	{
	    if (list[i]->query_wiz_level())
	    {
		g_short = list[i]->query_title();
		write("@ " + g_name + " " + g_short);
	    }
	    else
	    {
		level = list[i]->query_trickster_level();
		g_short = "the "+ TITLES[level] +" Trickster";
		guild_stat = list[i]->query_stat(SS_LAYMAN);
		average_stat = list[i]->query_average_stat();
		write(sprintf("% -40s", "- " + g_name + " " + g_short));
		if (TP->query_wiz_level())
		    write("G_STAT "+(sprintf("% -5s", "("+guild_stat+")")) +
		      " AVG_STAT ("+average_stat+")");
	    }
	    cnt++;
	}
	if (list[i]->query_invis() && TP->query_wiz_level())
	{
	    write("@ (" + g_name + ")");
	    cnt++;
	}
	if (!list[i]->query_invis() || TP->query_wiz_level())
	    write("\n");
    }

    if(cnt > 1)
    {
	write("There are now "+cnt+" Tricksters hanging around and being "+
	  "tricky.\n");
	return 1;
    }

    write("You are the Trickiest Trickster alive.\n");
    return 1;
}

mapping
query_trickster_list_verbs()
{
    return ([
      "tricklist" : "list_active_tricksters",
      "tlist" : "list_active_tricksters"
    ]);
}
