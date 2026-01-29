/* /d/Gondor/guilds/defenders/shadows/guild_sh_occ.c
 *
 * Defenders guildshadow.
 *
 * Nerull 2016
 */


inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include <formulas.h>
#include <options.h>
#include "/std/combat/combat.h"
#include "../guild.h"

#define SW    shadow_who

public int      query_guild_not_allow_join_occ(object player, 
	            string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_occ_shadow(string str);


static string *titles_rank = ({ "Fresh Initiate",
    "Sentry",
	"Dark Sentry",
	"Erudite Sentry",
	"Forboding Sentry",
	"Emerging Sentry",
});


int
query_guild_level_occ()
{
	return MIN(DEF_MAX_GUILD_RANK_MEMBER, 
	query_shadow_who()->query_stat(SS_OCCUP) / 10);
}


string
query_guild_title_occ()
{
    return titles_rank[query_guild_level_occ()]+" of the Westlands";
}


public string
query_guild_name_occ()
{
    return GUILDNAME_OCC;
}


public string
query_guild_style_occ()
{
    return TYPE_OCC;
}


public int
query_guild_tax_occ()
{
    return TAX_OCC;
}


public mixed
query_guild_trainer_occ()
{
    return DEF_GUILDDIR + "rooms/train";
}


string
query_guild_title_occ_on()
{
	return titles_rank[query_guild_level_occ()] + " of the Westlands.";
}


public int
query_guild_not_allow_join_occ(object player, string type, string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public void
add_soul()
{
	setuid();
	seteuid(getuid());

	int i;
	object *member;

	member = users();

	shadow_who->add_cmdsoul(DEF_GUILDDIR + "souls/guild_soul");

	shadow_who->update_hooks();


	for (i = 0; i<sizeof(member); i++)
	{
		if (DEF_MASTER->is_defender(member[i]->query_name()))
		{
			if (member[i] != shadow_who)
			{
				tell_object(member[i], shadow_who->query_name()
					+ " enters the realms.\n");
			}
		}
	}
}


public void
init_occ_shadow(string str)
{
    ::init_occ_shadow();

	set_alarm(0.0, 0.0, add_soul);
}


public void remove_shadow()
{
	shadow_who->remove_cmdsoul(DEF_GUILDDIR + "souls/guild_soul");

	shadow_who->update_hooks();
	::remove_shadow();
}


void
linkdeath_hook(int i)
{
	int j;
	object *member = users();

	for (j = 0; j < sizeof(member); j++)
	{
		if (DEF_MASTER->is_defender(member[j]->query_name()))
		{
			if (member[j] != shadow_who)
			{
				if (i == 1)
				{
					tell_object(member[j], shadow_who->query_name()
						+ " travels to the land of the mist.\n");
				}

				if (i == 0)
				{
					tell_object(member[j], shadow_who->query_name()
						+ " returns from the land of the mist.\n");
				}
			}
		}
	}

	shadow_who->linkdeath_hook(i);
}


void
remove_object()
{
	int i;
	object *obs = users();

	if (calling_function(-1) == "quit")
	{
		for (i = 0; i < sizeof(obs); i++)
		{
			if (DEF_MASTER->is_defender(obs[i]->query_name()))
			{
				tell_object(obs[i], shadow_who->query_name()
					+ " has left the realms.\n");
			}
		}
	}

	shadow_who->remove_object();
}