//taken from the Noldor list, which was stolen ruthlessly from the Rangers' rcomm.h!
#include "uruk.h"

int list_active_uruks()
{
	string g_name, g_short;
	int i;
	int cnt = 0;
	object *list;
	write("Uruks of the Red Eye\n");
	write("O=======================================================================O\n\n");
	list = users();
	
	for(i = 0; i < sizeof(list); i++)
	{
		g_name = capitalize(list[i]->query_real_name());
		if(IS_MEMBER(list[i]) && list[i]->query_prop(M_URUK))
		{
			/* Don't want a jr's name on the guildlist */
			//if((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
			//continue;
			if(!list[i]->query_invis())
			{
				if(list[i]->query_wiz_level())
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
			
			if(list[i]->query_invis() && TP->query_wiz_level())
			{
				write("@ (" + g_name + ")");
				cnt++;
			}
			
			else 
			{
				if(list[i]->short())
				write("");
			}
			
			if(!list[i]->query_invis() || TP->query_wiz_level())
				write("\n");
		}
	}
	
	write("\n\nUruks of the White Hand\n");
	write("O=======================================================================O\n");
	
	list = users();
	
	for(i = 0; i < sizeof(list); i++)
	{
		g_name = capitalize(list[i]->query_real_name());
		if(IS_MEMBER(list[i]) && list[i]->query_prop(I_URUK))
		{
			/* Don't want a jr's name on the guildlist */
			//if((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
			//continue;
			if(!list[i]->query_invis())
			{
				if(list[i]->query_wiz_level())
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
			
			if(list[i]->query_invis() && TP->query_wiz_level())
			{
				write("@ (" + g_name + ")");
				cnt++;
			}
			
			else 
			{
				if(list[i]->short())
				write("");
			}
			
			if(!list[i]->query_invis() || TP->query_wiz_level())
				write("\n");
		}
	}
	
	if(cnt > 1)
	{
		write("\n**There are "+cnt+" uruks wandering the lands.\n");
		return 1;
	}

	write("\n**You are a lone uruk in the world.\n");
	return 1;
}
