
/*
 *  Spellweavers' Guild Layman Shadow
 *	Farlong, 3-10-1994
 *	(Based on examples supplied by Mylos)
 *
 */

inherit "/std/guild/guild_lay_sh";

#include "sw.h"
#include "/d/Genesis/login/login.h"
#include <ss_types.h>
#include <language.h>


/*
 * Guild Titles
 */

string *TITLES = ({ "Associate Student of the Spellweavers",
    "Associate Apprentice of the Spellweavers",
    "Associate Acolyte of the Spellweavers",
    "Associate Seer of the Spellweavers",
    "Associate Evocator of the Spellweavers",
    "Associate Diviner of the Spellweavers",
    "Associate Magician of the Spellweavers"});
/* (7 levels) */


/*
 * Set guild tax
 */

int
query_guild_tax_lay()
{
   return 12;
}


/*
 * Query Your Level in the guild
 */

int
query_sw_lay_level()
{
   return shadow_who->query_base_stat(SS_LAYMAN)/9;
}


/*
 * Set default post office to the Guild
 */
query_def_post()
{
    return SWG+"post";
}


/*
 * Find guild title
 */

string
query_guild_title_lay()
{
   int stat;

   stat=query_sw_lay_level();

   if(stat<0) stat=0;
   if(stat>6) stat=6;

   return TITLES[stat];
}


/*
 * Get guild style
 */

string
query_guild_style_lay()
{
   return GUILD_STYLE;
}


/*
 * Get guild name
 */

string
query_guild_name_lay()
{
   return GUILD_NAME;
}



