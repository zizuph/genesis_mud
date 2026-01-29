/*
 *  The Gladiator-guild shadow
 *                        
 *  By Mylos and Anton 10-8-93
 */

inherit "/std/guild/guild_occ_sh";

#include "guild.h"
#include <ss_types.h>
#include <language.h>
#include <const.h>
#include <stdproperties.h>

#define COLLAR_ID        "glad_collar"

/*
 * Guild titles
 */

#define MALE_TITLES ({   "Fresh ",  "Slave ", \
                         "Trainee ",  "Blooded ", \
                         "Apprentice ",  "Lesser ", \
			 "Sun Scarred ",  "Minor ", \
			 "Prized ",  "Grim ", \
			 "Venomous ",  "Brutal ", \
                         "Deadly ",  "High ", \
			 "Fierce ",  "Famous ", \
			 "True ",  "Powerful ", \
			 "Ferocious ",  "Feared ", \
                         "Glorious ",  "Lord ", \
			 "Renowned ",  "Battle Hardened ", \
			 "Champion ",  "Master ", \
			 "Legendary Master ", \
			 "Imperial Master ", \
			 "Supreme Master " })

#define FEMALE_TITLES ({ "Fresh ",  "Slave ", \
                         "Trainee ",  "Blooded ", \
                         "Apprentice ",  "Lesser ", \
			 "Sun Scarred ",  "Minor ", \
			 "Prized ",  "Grim ", \
			 "Venomous ",  "Brutal ", \
                         "Deadly ",  "High ", \
			 "Fierce ",  "Famous ",  \
			 "True ",  "Powerful ", \
                         "Ferocious ",  "Feared ", \
                         "Glorious ",  "Lady ", \
			 "Renowned ",  "Battle Hardened ", \
			 "Champion ",  "Mistress ", \
			 "Legendary Mistress ", \
			 "Imperial Mistress ", \
			 "Supreme Mistress ", })

#define GLAD_SUB        "gladiator_subloc"

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
query_guild_tax_occ()
{
   return TAX; /* Whatever you wish to set it to. */
}
public mixed query_guild_trainer_occ() { return
({"/d/Roke/Athas/gladiator/train1", "/d/Roke/Athas/gladiator/train2",
 "/d/Roke/Athas/gladiator/train3"}); }

/* Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a fighter or thief, we will throw
 *                him out
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc(GLAD_SUB, this_object());

    return 1;
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       The new postoffice
 */
string query_def_post()
{
    return "/d/Roke/Athas/room/tyr/common/post";
}

/* Function name: query_gladiator_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_gladiator_level()
{
    return shadow_who->query_base_stat(SS_OCCUP) / 4;      
}

/*
 * Function name: query_guild_title_occ
 * Description:   Gives the guild title.
 * Returns:       Guess what.
 */
string query_guild_title_occ()
{
   int stat;

   stat = query_gladiator_level();

   if (stat < 0)
       stat = 0;

   if (stat > 28)
       stat = 28;

   if (shadow_who->query_gender() == G_FEMALE)
       return FEMALE_TITLES[stat] + "Gladiator of Athas";
   else
       return MALE_TITLES[stat] + "Gladiator of Athas";
}

#ifdef THIS_IS_OBSOLETE_NOW
/* Function name: query_title
 * Description:   We change the title of our members depending on their level
 * Returns:       The new title
 */
query_title()
{
   string o_title;

   o_title = shadow_who->query_title();

   /*
    * Wizards get to keep their own title
    */
   if (shadow_who->query_wiz_level())
        return o_title;

   if (strlen(o_title))
       return o_title + " and " + query_guild_title_occ();
   else
       return query_guild_title_occ();
}
#endif

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != GLAD_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
        str = "You have ";
    else
        str = capitalize(me->query_pronoun()) + " has ";

     return str + "the brutal look of a Gladiator.\n";
}

/*
 * Function name: query_guild_style_occ
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/* Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_CHARGE) return "charge";
    if (type == SS_BERSERK) return "berserk";
    return 0;
}
