/*                          The Elven Guild Shadow.                        */
/*    This shadow was taken from Tulix's great grunts shadow (It smelt a   */
/*    bit, but that's besides the point). Thatnks go to tulix for helping  */
/*    compile the list of titles and for quite a few suggestions.          */
/*                      Mylos, 20.4.93                                     */ 

inherit "/std/guild/guild_race_sh";

#include "default.h"
#include "/d/Emerald/soul/elf_defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

/* The wildrunner titles			*/

#define SERF_LEVELS ({	"Serf", \
			"Trainee Guard", \
			"Blooded Guard", \
			"Promising Scout", \
			"Dashing Scout", \
			"Lead Scout", \
			"Warrior", \
			"Proud Warrior", \
			"Lightning Warrior", \
			"Experienced Warrior", \
			"Veteran Warrior", })

#define NCO_LEVELS ({	"Corporal", \
			"Knowledgeable Corporal", \
			"Rookie Sergeant", \
			"Guard Sergeant", \
			"Grizzled Sergeant", \
			"Man-at-arms", \
			"Aspiring Squire", \
			"Blooded Squire", \
			"Veteran Squire", \
			"Noble Squire", })

#define LORD_LEVELS ({	"Royal Squire", \
			"Adjutant", \
			"Noble", \
			"Baronet", \
			"Haughty Baronet", \
			"Lord", \
			"Lord Lieutentant", \
			"Regent", \
			"Commander", })

/* ************************************************************************   
               
 * Set the tax for our civilized little guild.
 */

int
query_guild_tax_race()
{
    return 2;
}

/* ************************************************************************
 * Do we want this player to join our guild?
 */

int
query_guild_not_allow_join_race(player, type, style, name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
        return 1;

    return 0;
}

/* ************************************************************************
 * Lets face it, you need to be an elf to join an elf race guild!
 */

int
query_guild_keep_player(player)
{
    if (player->query_race_name() !="elf")
    {
        write("Get out of here before an Elf decides to kill you!\n");
        return 0;
    }

    return 1;
}

/* ************************************************************************
 * Get the players guild level. This is based on INT and DEX.
 */
int
query_wildrunner_level()
{
    return shadow_who-> query_base_stat(SS_INT) / 2 +
           shadow_who-> query_base_stat(SS_DEX) / 2;
}

/* ************************************************************************
 * Give the player a title that is dependent on their level.
 */
string
query_guild_title_race()
{
   int stat;

   stat = query_wildrunner_level() / 9;

   if(stat < 0)
        stat = 0;
   if(stat > 29)
        stat = 29;
   
   if(stat > 0 && stat <= 10) {
      return SERF_LEVELS[stat] + " of the "+
      ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker") +
      " Legion";
   }
   else if((stat > 10 && stat <= 20) && 
	(shadow_who->query_skill(SS_AWARENESS) > 25) && 
	(shadow_who->query_skill(SS_TRACKING) > 10)) {
      return NCO_LEVELS[stat - 10] + " of the "+
      ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker") +
 	" Legion";
   }
   else if((stat > 20) && (shadow_who->query_skill(SS_AWARENESS) > 35) &&
        (shadow_who->query_skill(SS_TRACKING) > 15)) {
      return LORD_LEVELS[stat - 20] + " of the "+
	((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker") +
	" Legion";
   }
   else
      return SERF_LEVELS[stat % 9] + " of the "+
	((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker") +
	" Legion";
}

/* ************************************************************************
 * Get the style of the guild.
 */

string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/* ************************************************************************
 * Get the name of the guild. 
 */

string
query_guild_name_race()
{
    return GUILD_NAME;
}
