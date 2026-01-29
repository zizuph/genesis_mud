
/*
 *  Spellweavers' Guild Occupational Shadow
 *	Farlong, 3-10-1994
 *	(Based on examples supplied by Mylos)
 *
 */

inherit "/std/guild/guild_occ_sh";

#include "sw.h"
#include "/d/Genesis/login/login.h"
#include <ss_types.h>
#include <language.h>


/*
 * Guild Titles
 */

#define TITLES ({"Student of the Spellweavers", \
		"Apprentice of the Spellweavers", \
		"Acolyte of the Spellweavers", \
		"Seer of the Spellweavers", \
		"Evocator of the Spellweavers", \
		"Apprentice Diviner of the Spellweavers", \
		"Apprentice Enchanter of the Spellweavers", \
		"Apprentice Warlock of the Spellweavers", \
		"Demonist of the Spellweavers", \
		"Conjurer of the Spellweavers", \
		"Advanced Enchanter of the Spellweavers", \
		"Magician of the Spellweavers", \
		"Necromancer of the Spellweavers", \
		"Advanced Warlock of the Spellweavers", \
		"Advanced Diviner of the Spellweavers", \
		"Sorcerer of the Spellweavers", \
		"Magus of the Spellweavers", \
		"Archnecromancer of the Spellweavers", \
		"Haruspex of the Spellweavers", \
		"Archmagus of the Spellweavers", \
		"High Archmagus of the Spellweavers", \
		"Lord of the Spellweavers", \
		"Master of the Spellweavers" })
/* (23 levels) */


/*
 * Set guild tax
 */

query_guild_tax_occ()
{
   return 30;
}


/*
 * Query Your Level in the guild
 */

int
query_sw_occ_level()
{
   return shadow_who->query_base_stat(SS_OCCUP)/5;
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
query_guild_title_occ()
{
   int stat;

   stat=query_sw_occ_level();

   if(stat<0) stat=0;
   if(stat>22) stat=22;

	if(TP->test_bit("Rhovanion",0,12)
					)
		return "Lord High Magistrate of the Spellweavers";
	else if(TP->test_bit("Rhovanion",0,13)
					)
		return "Runemaster of the Spellweavers";
	else if(TP->test_bit("Rhovanion",0,14)
					)
		return "Master Patterner of the Spellweavers";
	else
   return TITLES[stat];
}


/*
 * Get guild style
 */

string
query_guild_style_occ()
{
   return GUILD_STYLE;
}


/*
 * Get guild name
 */

string
query_guild_name_occ()
{
   return GUILD_NAME;
}

