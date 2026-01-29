
/*
** Cult of Melkor occupational guild shadow
**
** Gunther 940719
*/

inherit "/std/guild/guild_occ_sh";

#include "/d/Genesis/login/login.h"
#include <ss_types.h>
#include <language.h>
#include "guild.h"

#define TITLES ({ \
	"Fresh Slave of Melkor", \
	"Lesser Slave of Melkor", \
	"Willing Slave of Melkor", \
	"Loyal Slave of Melkor",    \
	"Favoured Slave of Melkor",  \
	"Dark Worshipper of Melkor",  \
	"Fervent Worshipper of Melkor",\
	"Occult Worshipper of Melkor", \
	"Fanatic Worshipper of Melkor",\
	"Unholy Worshipper of Melkor",\
	"Novice Initiate of Melkor",\
	"Merciless Initiate of Melkor",\
	"Righteous Initiate of Melkor",\
	"Arcane Initiate of Melkor",\
	"Priest of Melkor",\
	"Feared Priest of Melkor",\
	"Shadowpriest of Melkor",\
	"High Priest of Melkor",\
	"Overpriest of Melkor",\
	"Lord Priest of Melkor" })
	
#define GM_TITLE "Disciple of Melkor"

query_guild_tax_occ()
{
   return 27;
}

int
query_cult_occ_level()
{
   return shadow_who->query_base_stat(SS_OCCUP) / 7;
}


query_def_post()
{
   return CULT_DIR + "t_post";
}

string
query_guild_title_occ()
{
	int n;
	
	n = query_cult_occ_level();
	if(n >= sizeof(TITLES)) n = sizeof(TITLES) - 1;
	
	if(TP->test_bit(GM_BIT)) return TITLES[n];
	return GM_TITLE;
}

string
query_guild_style_occ()
{
   return CULT_STYLE;
}

string
query_guild_name_occ()
{
   return CULT_NAME;
}

notify_you_killed_me(object died)
{
	/* ok, lets tell the command object */
	object co;
	
	::notify_you_killed_me(died);
	
	co = present("_cult_command_obj", all_inventory(shadow_who));
	if(co) co->we_killed_someone(died);
	
	add_some_favor(died->query_average_stat() / 10);
}


/********************* FAVOR related functions *******************/

nomask int
query_favor_points()
{
	return shadow_who->query_skill(SS_FAVOR);
}

nomask void
add_some_favor(int n)
{
	float factor;
	int change;
	
	if(n < 0)
	{
		/* slide n a bit depending on alignment */
		factor = 1000 - shadow_who->query_alignment();
		factor /= 1000;
		change = n * factor;
	}
	else change = n;
	
	shadow_who->set_skill(SS_FAVOR, shadow_who->query_skill(SS_FAVOR) + change);
}

nomask int
calculate_max_favor(int n)
{
	int guildstat, alignstat, maxfavor;
	/* lets hope that skills are signed ints */
	
	guildstat = shadow_who->query_base_stat(SS_OCCUP);
	alignstat = shadow_who->query_alignment();
	
	maxfavor = guildstat * 10 - alignstat;
	
	return maxfavor;
}
	
	
