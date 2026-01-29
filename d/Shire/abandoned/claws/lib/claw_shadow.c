/*
 * /d/Shire/claws/shadow.c
 * The shadow for the Black Claw Clan.
 * Turgon, October 1996
 * 
 * Modification log:
 *
 */
//#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <const.h>
#include "/d/Shire/defs.h"
#include "/d/Shire/guild/claws/claw_defs.h"
#include "/d/Shire/skills.h"

#define QSW query_shadow_who()
#define JOINROOM "/d/Shire/guild/claws/rooms/join"
#define PL_SAVE 	"/d/Shire/guild/claws/log/save/"
#define CLAW_SUBLOC "_claw_subloc_"

#define PROUDNESS ({ \
			"trainee", "fresh", "adept", "renowned", \
			"widely known", "grand", "blood hungry", "skull breaking", \
			"legendary", "superior" })

public int     claw_rank;
static object me;

object
qme()
{
	return me;
}

public int
query_guild_tax_occ()
{
	return GUILD_TAX;
}

public string
query_guild_style_occ()
{
	return GUILD_STYLE;
}

public string
query_guild_name_occ()
{
	return GUILD_NAME;
}

/*
 * Function name: rank
 * Description:   Find out at what rank the player is.
 * Returns:       The rank.
 * Arguments:     player - The player to test.
 */
int
query_claw_rank()
{

	return claw_rank;
}

void
set_claw_rank(int n)
{
    claw_rank = n;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:   Test Whether we allow the player into our guild.
 * Returns:       1 - If not.
 *                0 - If we do allow it.
 */
int
query_guild_not_allow_join_occ(object player, string type, string style, string name)
{
	/* There are currently no restrictions, besides from being orc :) */
	/* This is a redefinition, so we call the original. All tests will 
	 * be done in the joinroom before we allow player to join.
	 */
	return ::query_guild_not_allow_join_occ(player, type, style, name);
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test whether we want to keep a player when he logs in.
 * Arguments:     player
 * Returns:       1 - If we keep him
 *                0 - If we kick him out.
 */
public int
query_guild_keep_player(object player)
{
	string race;
	race = player->query_race_name();
	
	// If player has changed his race, we kick him out!

   if (race != "goblin")
	{
		write("Only true Orcs can serve our clan!\n");
		call_other(JOINROOM, "remove_player_changed_race", player);
		return 0;
	}

	player->add_subloc(CLAW_SUBLOC, this_object());
	return 1;
}

/*
 * Function name: query_guild_title_occ
 * Description:   Returns the title for the member.
 * Returns:       string - the title.
 */
nomask public string
query_guild_title_occ()
{
	int level, new_level;
	string title;
	object tp = QSW;
	level = tp->query_stat(SS_OCCUP);
	if (level >= 150)
	    level = 150;
	if (tp->query_wiz_level())
		return tp->query_title();

   if (claw_rank == SLAVE)
	{
	  new_level = level/50;
	  if (new_level >= sizeof(SLAVE_TITLES))
	  new_level = sizeof(SLAVE_TITLES) -1;
	  title = SLAVE_TITLES[new_level] + " of the Black Claw Clan";
	}
   else if (claw_rank == SCOUT)
	{
	  new_level = level/10;
	  if (new_level >= sizeof(SCOUT_TITLES))
		new_level = sizeof(SCOUT_TITLES) - 1;
	  title = SCOUT_TITLES[new_level] + " of the Black Claw Clan";
	}
   else if (claw_rank == WARRIOR)
	{
	  new_level = level/5;
	  if (new_level >= sizeof(WARRIOR_TITLES))
	    new_level = sizeof(WARRIOR_TITLES) - 1;
	  title = WARRIOR_TITLES[new_level] + " of the Black Claw Clan";
	}
   else if (claw_rank == CAPTAIN)
	  title = MASTER_TITLE + " of the Black Claw Clan";

	return title;
}

void
init_occ_shadow(string str)
{
	string name, fname;
	seteuid(getuid());
    
    me = query_shadow_who();
    name = me->query_real_name();
	//claw_rank = THRONE->query_rank(name);
	fname = PL_SAVE + name;

	restore_object(fname);
}

string
show_subloc(string subloc, object who, object for_obj)
{
	string str;
	int tmp;

	if (subloc != CLAW_SUBLOC)
		return query_shadow_who()->show_subloc(subloc, who, for_obj);

	if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";

	if (for_obj == who)
		str = "You are ";
	else
		str = CAP(who->query_pronoun()) + " is ";

	if (who->query_wiz_level())
		str += "a Guru";
	else
	{
		tmp = who->query_base_stat(SS_OCCUP) / 10;
		if (tmp > 9)
			tmp = 9;
			str += LANG_ADDART(PROUDNESS[tmp]);	
	}

	return str += " member of the Black Claw Clan.\n";
}
