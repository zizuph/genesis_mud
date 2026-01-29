/*
 *  Shadow for the Elemental Worshippers of Calia layman guild.
 *  Coded by Bishop, June 2000, based on Jaacars old work.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"


string 
query_guild_style_lay() 
{ 
    return GUILD_STYLE; 
}


string 
query_guild_name_lay() 
{ 
    return GUILD_NAME; 
}


int 
is_worship()
{
    return 1;
}


int 
query_guild_tax_lay() 
{ 
    return GUILD_TAX; 
}


void
init_lay_shadow(string str)
{
    ::init_lay_shadow();
}


/*
 * This ensures the skills don't show up on the mortal skill list.
 */
string
query_guild_skill_name(int skill)
{
    if ((skill == SS_PATRON_ELEMENTAL) ||
        (skill == SS_GUILD_STATUS) ||
        (skill == SS_PUNISHMENT))
       return ""; 
    return 0;
}


/*
 * Sets the guild post office.
 */
string
query_def_post()
{
    return (WOR_TEMPLE+"post");
}


int
query_guild_keep_player(object ob)
{
    return 1;
}