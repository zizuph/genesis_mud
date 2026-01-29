/*
* Created by: Luther
* Date: Dec 2001
*
* File: /d/Cirath/guilds/militia/militia_sh.c
* Comments: Militia Shadow
*/

#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "defs.h"
#include "m_spear.h"
#include "m_shield.c"

/* global variables */ 
string query_guild_style_lay() { return MILITIA_GUILD_STYLE; }
string query_guild_name_lay()  { return MILITIA_GUILD_NAME; }
            
int 
query_guild_tax_lay() 
{ 
    return MILITIA_GUILD_TAX; 
}

mixed
query_guild_skill_name(int type)
{
    if (type == SS_SPEAR) return "spear";
    if (type == SS_MIL_SHIELD) return "shield";
    return 0;
}

string 
query_guild_title_lay()
{
    	int stat, max_stat;
    	
    	if (shadow_who->query_alignment() < -100)
    	return MILITIA_DISGRACE;
          stat = (shadow_who->query_base_stat(SS_LAYMAN)) / 5;
    	max_stat = sizeof(MAIN_TITLES) - 1;
    	if (stat < 0) stat = 0;
    	else if (stat > max_stat) stat = max_stat;
 	
	    return (MAIN_TITLES[stat]) + " of " + MILITIA_GUILD_NAME;
}

string
query_guild_trainer_lay()
{
    return MILITIA_ROOM + "m_train";
}

void
init_guild_member()
{
    object who = query_shadow_who();

    setuid();
    seteuid(getuid());
    
    /* add the guild's soul to the player */
    who->add_cmdsoul(MILITIA_SOUL);
    who->update_hooks();
}

void
init_lay_shadow(string str)
{	
	::init_lay_shadow();
	set_alarm(1.0, 0.0, init_guild_member);
}

void
remove_layman_member()
{
    object who = query_shadow_who();
    
    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    /* Penalty for leaving: loose 1/10 of total combat exp */
    who->add_exp(-(who->query_exp_combat()) / 10, 1);

    /* Remove the guild soul */
    who->remove_cmdsoul(MILITIA_SOUL);
    who->update_hooks();
    
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}
