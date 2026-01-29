//taken from the Noldor list, which was stolen ruthlessly from the Rangers' rcomm.h!
#include "halflings.h"
#define JOINROOM (ORCGLD_DIR + "rooms/join")

int list_active_orcs()
{
	string g_name, g_short;
	int i;
	int cnt = 0;
	object *list;
	write("                       _\n" +
		"                     / /\n" +
		"            _______ / /_/--^^^^^^^^ORCS^^^^^^^^^^^^^^^^\\\n" +
		"           {_______| |__>-----------OF------------------>\n"+
		"                    \\ \\ \\------MIDDLE-EARTH------------/\n"+
		"                     \\_\\\n");
	write("O=======================================================================O\n\n");
	list = users();
	
	for (i = 0; i < sizeof(list); i++)
	{
		g_name = capitalize(list[i]->query_real_name());
		if (IS_MEMBER(list[i]))
		{
			/* Don't want a jr's name on the guildlist */
			if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
			continue;
			if(!list[i]->query_invis())
			{
				if (list[i]->query_wiz_level())
				{
					g_short = list[i]->query_guild_title_race();
					write("o " + g_name + " " + g_short);
				}
				else
				{
					g_short = list[i]->query_guild_title_race();
					write("- " + g_name + " " + g_short);
				}
				cnt++;
			}
			if (list[i]->query_invis() && TP->query_wiz_level())
			{
				write("@ (" + g_name + ")");
				cnt++;
			}
			
			else 
			{
				if (list[i]->short())
				write("");
			}
			if (!list[i]->query_invis() || TP->query_wiz_level())
				write("\n");
		}
	}
    write("\nO=======================================================================O\n");

  if(cnt > 1)
  {
   write("There are "+cnt+" orcs wandering the lands.\n");
   return 1;
  }

   write("You're a lone orc in the world.\n");
   return 1;

}
