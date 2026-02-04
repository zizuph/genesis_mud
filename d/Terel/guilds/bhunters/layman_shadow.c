/*
	Guild shadow for bounty hunters
	by Udana 05/06
 */
inherit "/std/guild/guild_lay_sh";

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "./bhunters.h"

int rank = -1; 

/*
 */
nomask public int query_guild_tax_lay()
{
	return BHTAX;
}
/*
 */
nomask public string query_guild_style_lay()
{
	return BHSTYLE;
}
 
/*
 */
nomask public string query_guild_name_lay()
{
	return BHNAME;
}

/*
 */
public mixed
query_guild_skill_name(int type)
{
	if (type == SS_SET_TRAP)
		return "set traps";
	return 0;
}

/*
 */
nomask public string query_guild_title_lay()
{
	if(rank == -1)
		return "Bounty Hunter of Last";
	if(shadow_who->query_gender())
		return BHTITLES2[rank];
	return BHTITLES1[rank];
}

public int increase_hunter_rank()
{
	if(shadow_who->query_skill(BHRANK) < sizeof(BHTITLES1))
	{
		shadow_who->set_skill(BHRANK, shadow_who->query_skill(BHRANK) + 1);
		return 1;
	}
	return 0;
	
}

public int query_hunter_rank()
{
	return shadow_who->query_skill(BHRANK);
}

/* 
 */
public string
query_def_post()
{
	return shadow_who->query_def_post();
}

/*
 */
nomask public mixed
query_guild_trainer_lay()
{
    return ({BHROOM + "boris_room",
	BHROOM + "karl_room",
	BHROOM + "ivan_room"});
}

/*
 */
public int cleanup_hunter()
{
	/* Clear the player's layman guild stat */
	shadow_who->clear_guild_stat(SS_LAYMAN);
 
	/* Remove the guild soul and update the commands. */
	shadow_who->remove_cmdsoul(BHSOUL);
	shadow_who->update_hooks();
 
	object *guild_items = filter(all_inventory(shadow_who), &->is_hunters_belt());
	guild_items->remove_object();
	shadow_who->catch_msg("You've lost your belt!\n");
	
	if(shadow_who->query_default_start_location() == BHROOM + "start_room")
		shadow_who->set_default_start_location(shadow_who->query_def_start());
	
	shadow_who->add_exp_combat(- 1 * (shadow_who->query_exp_combat() / 8));
	shadow_who->remove_skill(SS_SET_TRAP);
	
	/* Remove the guild shadow last.  This also resets tax to 0. */
	int ret = remove_guild_lay();
	
	return ret;
}

 
/*
 * Function name : query_guild_keep_player
 * Description   : Standard function to test if we want to keep the
 *                 player in the guild when the shadow is autoloading
 *                 upon login.
 * Arguments     : who - the player to test
 * Returns       : 1 if keeping, 0 if not
*/
public int query_guild_keep_player(object who)
{
    return 1;
}

int have_components(object trap)
{
	string *req = trap->query_component_list();
	string *comps = all_inventory(shadow_who)->query_component_id() + ({""});
	for(int i = 0; i < sizeof(req); ++i)
	{
		if(member_array(req[i], comps) == -1)
			return 0;
	}
	return 1;
}

public void set_trap(string file)
{
	FIX_EUID;
	object trap = clone_object(file);
	if(!have_components(trap))
		shadow_who->catch_msg("You don't have required components.\n");
	else
		trap->arm_attempt(shadow_who);
}

public int pay_coins(int nr)
{
	object *blood_coins = filter(all_inventory(shadow_who), &->is_blood_money());
	if(sizeof(blood_coins) < nr)
		return 0;
	for(int i = 0; i < nr; ++i)
		blood_coins[i]->remove_object();
	return 1;
}

public mixed remove_component(string element)
{
	if(!strlen(element))
		return 1;
	object *inv = all_inventory(shadow_who);
	for(int i = 1; i < sizeof(inv); ++i)
	{
		if(inv[i]->query_component_id() == element)
		{
			if(inv[i]->query_multiple_use())
				return 1;
			else
				return inv[i];			
		}
	}
	return 0;
}
/*
 */
public nomask void init_member()
{
	if(!objectp(shadow_who))
		return;	
	/* Add the guild's soul to the player. */
	shadow_who->add_cmdsoul(BHSOUL);
	shadow_who->update_hooks();
	(BHROOM + "join")->telegnigasanka();
	(BHROOM + "join")->pay_hunter(shadow_who);
}


/*
 * Function name: init_lay_shadow
 * Description  : This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments    : The argument string sent to autoload_shadow.
 */
void
init_lay_shadow(string arg)
{
	rank = shadow_who->query_skill(BHRANK);
	/* delay so that player completes login before we continue */
	set_alarm(1.0, 0.0, &init_member());
}

