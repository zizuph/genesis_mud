/**********************************************************************
 * - shadow.c                                                       - *
 * - Eil-Galaith, elven race guild shadow                           - *
 * - Original code Created by Lucius                                - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Allowed humans and elves to join (Gorboth, July 2011)          - *
 **********************************************************************/
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";

#include "guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <alignment.h>

static private mixed data;
static private int   death_res;

public int
query_guild_tax_race()		{ return GUILD_TAX; }

public string
query_guild_style_race()	{ return GUILD_STYLE; }

public string
query_guild_name_race()		{ return GUILD_NAME; }

public string *
query_guild_trainer_race()
{
	return ({ (ROOM + "train"), (ROOM + "garden") });
}

public int
query_guild_family_name()	{ return 1; }

public string
query_guild_title_race()
{
	if (!sizeof(data))
	return "";
	return data[SNAME] + (data[HNAME] ?
	" from the House of " + data[HNAME] : "");
}

public int
leave_guild_race()
{
	int tmp;
	object ob;
	
	shadow_who->catch_tell("You are no longer a member of "+
	"the " + GUILD_NAME + ".\n");
	
	shadow_who->remove_cmdsoul(SOUL);
	shadow_who->update_hooks();
	shadow_who->clear_guild_stat(SS_RACE);
	shadow_who->setup_skill_decay();
	shadow_who->remove_subloc(GUILD_SUBLOC);
	
	while(ob = present(OBJECT_ID, shadow_who))
	ob->remove_object();
	
	if (shadow_who->query_default_start_location() == STARTLOC)
	shadow_who->set_default_start_location(shadow_who->query_def_start());
	
	if (sizeof(data) && data[MRACE])
	shadow_who->set_race_name("elf");
	SERVER->remove_member(shadow_who->query_real_name());
	
	SCROLLING_LOG(LOG + "leave",
	capitalize(shadow_who->query_real_name()) +
	" left the " + GUILD_NAME + ". <--");
	
	return remove_guild_race();
}

private mixed
acceptable_member(object who)
{
        if (!IN_ARRAY( who->query_race(), ({ "elf", "human" }) ))
	{
		return "Only elves or humans may join the " + GUILD_NAME + "!\n";
	}
	
	if (who->query_alignment() <= GUILD_MIN_ALIGN)
	{
		return "The " + GUILD_NAME + " seeks souls of purity "+
		"and finds your heart unworthy.\n";
	}
	
	if (who->query_prop() == LIVE_I_UNDEAD)
	{
		return "The " + GUILD_NAME + " appreciates life, "+
		"not death.\nCorpses need not apply.\n";
	}
	return 1;
}

public int
query_guild_keep_player(object ob)
{
	mixed why;
	
	if (stringp(why = acceptable_member(ob)))
	{
		tell_object(ob, why);
		set_alarm(2.0, 0.0, leave_guild_race);
	}
	return 1;
}

private void
init_guild()
{
	/* This is to prevent server lookups for every 'who' command. */
	data = SERVER->query_member(shadow_who->query_real_name());
	shadow_who->add_cmdsoul(SOUL);
	shadow_who->update_hooks();
	if (data[MRACE])
	shadow_who->set_race_name("half-elf");
}

public void
init_race_shadow(string arg)
{
	setuid();  seteuid(getuid());
	set_alarm(1.0, 0.0, init_guild);
}

public int
add_race_shadow(object who)
{
	return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}

public void
set_alignment(int i)
{
	shadow_who->set_alignment(i);
	
	if (i <= ALIGN_UNTRUSTWORTHY)
	{
		shadow_who->catch_tell("You no longer reside "+
		"in harmony with the mystic vine.\nYour mark of "+
		"the mystic vine vanishes!\n");
		leave_guild_race();
	}
	
	if (i <= ALIGN_DISAGREEABLE)
	{
		shadow_who->catch_tell("The mystic vine glows hot "+
		"and you feel an intense burning pain!\nYou've been "+
		"hurt!\n");
		shadow_who->heal_hp(-25);
	}
}
