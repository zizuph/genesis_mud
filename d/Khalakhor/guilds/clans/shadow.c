/**********************************************************************
 * - shadow.c                                                       - *
 * - Clans of Khalakhor, human rcae guild                           - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
/*
 * Updated by Zhar, November 2012
 *
 * - cleaned up the code and formatting
 * - added Blademaster title merging
 */

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

public object query_top_shadow();

static private mixed data;

public int
query_guild_tax_race()
{
    return GUILD_TAX;
}

public string
query_guild_style_race()
{
    return GUILD_STYLE;
}

public string
query_guild_name_race()
{
    return GUILD_NAME;
}

public int
query_guild_family_name()
{
    return 1;
}

public int
is_khalakhor_clan_member()
{
    return 1;
}

public string
query_guild_title_race()
{
    string title;
    string btitle;
	
    if (!sizeof(data))
    {
        // adding blademaster check here in order to not return empty strings
        // for both guilds in case of missing surnames and clans
    	if (query_top_shadow()->is_khalakhor_blademaster())
    	{
    		btitle = query_top_shadow()->query_blademaster_title();
    		
    		if (strlen(btitle))
    		{
    	    	title = btitle + " of Khalakhor";
    		
    	    	return title;
        	}
        	else
        	{
        		return "";
        	}
    	}

	return "";
    }

    title = ((shadow_who->query_gender() == 1) ? "Nic" : "Mac");

    title += (data[SNAME][0] == 'a' ? " " : "") + data[SNAME];
	
    // check for blademaster title merging
    if (query_top_shadow()->is_khalakhor_blademaster())
    {
    	btitle = query_top_shadow()->query_blademaster_title();
    	
    	if (strlen(btitle))
    	{
	title += ", the " + btitle;
	title += (data[CNAME] ? " of " + data[CNAME] : " of Khalakhor");
		}
		else
		{
			title += (data[CNAME] ? " of " + data[CNAME] : "");
		}
    }
    else
    {
    	title += (data[CNAME] ? " of " + data[CNAME] : "");
    }
	
    return title;
}

public int
leave_guild_race()
{
    object ob = present(OBJECT_ID, shadow_who);
    
    string name = shadow_who->query_real_name();
        
    shadow_who->catch_tell("You are no longer a member of the " +
        GUILD_NAME + ".\n");     	
        
    shadow_who->remove_cmdsoul(SOUL);
    shadow_who->update_hooks();
    shadow_who->clear_guild_stat(SS_RACE);
    shadow_who->setup_skill_decay();
    shadow_who->remove_subloc(GUILD_SUBLOC);
        
    if (objectp(ob))
    {
        ob->remove_object();
    }
        
    if (shadow_who->query_default_start_location() == STARTLOC)
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }
        
    if (sizeof(data))
    {
        shadow_who->set_race_name("human");
    }
		        
    SERVER->remove_member(name);
        
    SCROLLING_LOG(LOG + "members",
        capitalize(name) +
        " left the " + GUILD_NAME + ". <--");
        
    return remove_guild_race();
}

private mixed
acceptable_member(object who)
{
    if (who->query_race() != "human")
    {
        return "Only human may join the " + GUILD_NAME + "!\n";
    }
        
    return 1;
}

public int
query_guild_keep_player(object ob)
{
    mixed why = acceptable_member(ob);
        
    if (stringp(why))
    {
        tell_object(ob, why);
        set_alarm(2.0, 0.0, leave_guild_race);
    }
        
    return 1;
}

private void
init_guild()
{
	string name = shadow_who->query_real_name();
	
    /* This is to prevent server lookups for every 'who' command. */
    data = SERVER->query_member(name);
        
    shadow_who->add_cmdsoul(SOUL);
    shadow_who->update_hooks();
}

public void
init_race_shadow(string arg)
{
    setuid();
    seteuid(getuid());

    set_alarm(1.0, 0.0, init_guild);
}

public int
add_race_shadow(object who)
{
    return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}
