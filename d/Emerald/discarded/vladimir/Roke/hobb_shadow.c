/*
 *  The Nimblefingered Hobbit shadow
 *
 *
 */

inherit "/std/guild/guild_race_sh";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/hobbit/hobbitdefs.h"
#include <ss_types.h>
 
#include <composite.h>
#include <const.h>
#include <macros.h>
#include "/sys/living_desc.h"
#include <stdproperties.h>
#include <formulas.h>
#include <std.h>
#include <language.h>
#define PIPE       "pipe"



/*
 * Guild titles
 */
#define MALE_TITLES ({  "Cotton", \
                        "Bracegirdle", \
                        "Took", \
                        "Brandybuck", \
                        "Goodbody", \
                        "Chubb", \
                        "Grubb", \
                        "Burrows", \
                        "Boffin", \
                        "Hornblower", \
                        "Proudfoot", \
                        "Brockhouse", \
                        "Whitfoot", \
                        "Brown", \
                        "Bunce", \
                        "Hayward", \
                        "Sackville", \
                        "Sandheaver", \
                        "Twofoot" })
#define FEMALE_TITLES ({  "Cotton", \
                        "Bracegirdle", \
                        "Took", \
                        "Brandybuck", \
                        "Goodbody", \
                        "Chubb", \
                        "Grubb", \
                        "Burrows", \
                        "Boffin", \
                        "Hornblower", \
                        "Proudfoot", \
                        "Brockhouse", \
                        "Whitfoot", \
                        "Brown", \
                        "Bunce", \
                        "Hayward", \
                        "Sackville", \
                        "Sandheaver", \
                        "Twofoot" })
#define HOBB_SUB        "hobbit_subloc"

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

    ob->add_subloc(HOBB_SUB, this_object());

    if ((rn = ob->query_race_name()) != "hobbit")
    {
        x = strlen(rn) - 1;
        if (rn[x..x] == "f")
            rn = rn[0..x-1] + "ve";
        write("We don't like "+rn+"s in our family, "+
              "they are lower than dirt!\n");
        call_out("goblin_leave", 1, ob);
        return 0;
    }
    setuid();
    seteuid(getuid());
    return 1;
}

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
 * Function name:   query_title
 * Description:     Gives the title of a living.
 * Returns:         The title string
 */
public nomask string
query_title()
{
    string dom, name, *titles = ({ });

    if (!strlen(title))
        title = "";

    if (this_object()->query_wiz_level())
    {
        name = (string)this_object()->query_real_name();
        dom = (string)SECURITY->query_wiz_dom(name);

        if ((string)SECURITY->query_domain_madwand(dom) == name)
        {
            return LD_MADWAND_TITLE(title, dom);
        }

        return title;
    }

    /* This MUST be with this_object()-> or it will not work for we are
     * accessing the function in the shadows of the player!
     */
    if (strlen(name = (string)this_object()->query_guild_title_race()))
        titles = titles + ({ name });
    if (strlen(name = (string)this_object()->query_guild_title_occ()))
        titles = titles + ({ name });
    if (strlen(name = (string)this_object()->query_guild_title_lay()))
        titles = titles + ({ name });

    if (this_object()->query_npc())
    {
        if (!sizeof(titles))
        {
            return title;
        }
        if (strlen(title))
            titles = ({ title }) + titles;
    }

    /* A mortal player cannot have a title set by a wizard!
     */
    if (!sizeof(titles))
        return "";

    return  "" + COMPOSITE_WORDS(titles);
}
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

    if (subloc != HOBB_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);


    if (for_obj == me)
        str = "You are ";
    else
        str = capitalize(me->query_pronoun()) + " is ";


   return str + "smoking a brown pipe.\n";
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


 
    str = this_player()->list_major_guilds();
    if (str)
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");

    return 1;
}
