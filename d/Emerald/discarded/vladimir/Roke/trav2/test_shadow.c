/*
 *  The Traveller-guild shadow
 *
 *
 */

inherit "/std/guild/guild_race_sh";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/varl/atuan/cape/guild/default.h"
#include "/d/Roke/Athas/default.h"
#include <ss_types.h>
#include <language.h>

#define COUNCIL_FILE CAPE+"guild/secret"
#define INSIGNIA       "insignia"


/*
 * Guild titles
 */
#define MALE_TITLES ({  "Uninitiated Traveller", \
                        "Errand Runner of the Travellers", \
                        "Inexperienced Escort of the Travellers", \
                        "Esteemed Escort of the Travellers", \
                        "Understudy Wanderer of the Travellers", \
                        "Rising Wanderer of the Travellers", \
                        "Learned Wanderer of the Travellers", \
                        "Hardened Wanderer of the Travellers", \
                        "Lauded Wanderer of the Travellers", \
                        "Understudy Explorer of the Travellers", \
                        "Rising Explorer of the Travellers", \
                        "Learned Explorer of the Travellers", \
                        "Hardened Explorer of the Travellers", \
                        "Lauded Explorer of the Travellers", \
                        "Understudy Trailblazer of the Travellers", \
                        "Rising Trailblazer of the Travellers", \
                        "Learned Trailblazer of the Travelers", \
                        "Hardened Trailblazer of the Travellers", \
                        "Lauded Trailblazer of the Travellers", \
                        "Understudy Surveyor of the Travellers", \
                        "Rising Surveyor of the Travellers", \
                        "Learned Surveyor of the Travellers", \
                        "Hardened Surveyor of the Travellers", \
                        "Lauded Surveyor of the Travellers", \
                        "Understudy Cartographer of the Travellers", \
                        "Rising Cartographer of the Travellers", \
                        "Learned Cartographer of the Travellers", \
                        "Hardened Cartographer of the Travellers", \
                        "Lauded Cartographer of the Travellers", \
                        "Understudy Talespinner of the Travellers", \
                        "Rising Talespinner of the Travellers", \
                        "Learned Talespinner of the Travellers", \
                        "Hardened Talespinner of the Travellers", \
                        "Lauded Talespinner of the Travellers", \
                        "Understudy Historian of the Travellers", \
                        "Rising Historian of the Travellers", \
                        "Learned Historian of the Travellers", \
                        "Understudy Elder of the Travellers", \
                        "Rising Elder of the Travellers", \
                        "Learned Elder of the Travellers", \
                        "Hardened Elder of the Travellers", \
                        "Lauded Elder of the Travellers", \
                        "Traveller of Legend" })

#define FEMALE_TITLES ({ "Uninitiated Traveller", \
                        "Errand Runner of the Travellers", \
                        "Inexperienced Escort of the Travellers", \
                        "Esteemed Escort of the Travellers", \
                        "Understudy Wanderer of the Travellers", \
                        "Rising Wanderer of the Travellers", \
                        "Learned Wanderer of the Travellers", \
                        "Hardened Wanderer of the Travellers", \
                        "Lauded Wanderer of the Travellers", \
                        "Understudy Explorer of the Travellers", \
                        "Rising Explorer of the Travellers", \
                        "Learned Explorer of the Travellers", \
                        "Hardened Explorer of the Travellers", \
                        "Lauded Explorer of the Travellers", \
                        "Understudy Trailblazer of the Travellers", \
                        "Rising Trailblazer of the Travellers", \
                        "Learned Trailblazer of the Travellers", \
                        "Hardened Trailblazer of the Travellers", \
                        "Lauded Trailblazer of the Travellers", \
                        "Understudy Surveyor of the Travellers", \
                        "Rising Surveyor of the Travellers", \
                        "Learned Surveyor of the Travellers", \
                        "Hardened Surveyor of the Travellers", \
                        "Lauded Surveyor of the Travellers", \
                        "Understudy Cartographer of the Travellers", \
                        "Rising Cartographer of the Travellers", \
                        "Learned Cartographer of the Travellers", \
                        "Hardened Cartographer of the Travellers", \
                        "Lauded Cartographer of the Travellers", \
                        "Understudy Talespinner of the Travellers", \
                        "Rising Talespinner of the Travellers", \
                        "Learned Talespinner of the Travellers", \
                        "Hardened Talespinner of the Travellers", \
                        "Lauded Talespinner of the Travellers", \
                        "Understudy Historian of the Travellers", \
                        "Rising Historian of the Travellers", \
                        "Learned Historian of the Travellers", \
                        "Understudy Elder of the Travellers", \
                        "Rising Elder of the Travellers", \
                        "Learned Elder of the Travellers", \
                        "Hardened Elder of the Travellers", \
                        "Lauded Elder of the Travellers", \
                        "Traveller of Legend" })
#define TRAV_SUB        "traveller_subloc"

private mixed stat_names, title, badge;
public string *cmembers;
/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
query_guild_tax_race()
{
   return TAX; /* Whatever you wish to set it to. */
}

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
    string rn;
    int x;

    ob->add_subloc(TRAV_SUB, this_object());

    if ((rn = ob->query_race_name()) != "human")
    {
        x = strlen(rn) - 1;
        if (rn[x..x] == "f")
            rn = rn[0..x-1] + "ve";
        write("We don't like "+rn+"s in the Traveller Guild, they smell.\n");
        call_out("goblin_leave", 1, ob);
        return 0;
    }
    setuid();
    seteuid(getuid());
    restore_object(COUNCIL_FILE);
    return 1;
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       The new postoffice
 */
/* string query_def_post()
* {
* return "/d/Genesis/start/human/town/post";
* }
*/

/* Function name: query_traveller_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_traveller_level()
{
      return shadow_who->query_base_stat(SS_RACE) / 3;
}

/* Function name: query_guild_title_race
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
string query_guild_title_race()
{
   int stat;

     if (member_array(shadow_who->query_name(), cmembers) != -1)
       return "Supreme Traveller of the Realms";
   stat = query_traveller_level();

   if (stat < 0)
       stat = 0;

   if (stat > sizeof(MALE_TITLES) -1)
 stat = sizeof(MALE_TITLES) -1;

   if (shadow_who->query_gender() == G_FEMALE)
   return FEMALE_TITLES[stat];
   else
   return MALE_TITLES[stat];
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
        return o_title + " and " + query_guild_title_race();
    else
        return query_guild_title_race();
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

    if (subloc != TRAV_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
        str = "You are ";
    else
        str = capitalize(me->query_pronoun()) + " is ";

 
   return str + "carrying a weather beaten walking stick.\n";
}

/*
 * Function name: query_guild_style_race
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_race()
{
    return GUILD_NAME;
}

list()
{
    string str;

    str = this_player()->list_mayor_guilds();
    if (str)
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");

    return 1;
}
