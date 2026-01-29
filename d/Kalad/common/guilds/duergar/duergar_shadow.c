inherit "/std/guild/guild_race_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/duergar/default.h"
#define SYMBOL "/d/Kalad/common/guilds/duergar/symbol"

/*
* Guild titles
*/
#define TITLES ({ "Craving Parasite of the Duergar-clan", \
      "Avid Parasite of the Duergar-clan", \
      "Inordinate Parasite of the Duergar-clan", \
      "Cupidious Parasite of the Duergar-clan", \
      "Greedy Parasite of the Duergar-clan", \
      "Voratious Scrounger of the Duergar-clan", \
      "Piggish Scrounger of the Duergar-clan", \
      "Covetous Scrounger of the Duergar-clan", \
      "Insatiable Scrounger of the Duergar-clan", \
      "Plundering Scrounger of the Duergar-clan", \
      "Villainous Hireling of the Duergar-clan", \
      "Ravenous Hireling of the Duergar-clan", \
      "Malicious Hireling of the Duergar-clan", \
      "Ransacking Hireling of the Duergar-clan", \
      "Avaricious Henchman of the Duergar-clan", \
      "Rapacius Henchman of the Duergar-clan", \
      "Predatorial Henchman of the Duergar-clan", \
      "Marauding Henchman of the Duergar-clan", \
      "Lesser Clanleader of the Dewars", \
      "Detested Clanleader of the Dewars", \
      "Feared Clanleader of the Dewars", \
      "Greater Clanleader of the Dewars", \
      "Damned Chieftain of the Duergar-clan", \
      "Lesser Tormentor of the Duergar-clan", \
      "Detested Tormentor of the Duergar-clan", \
      "Feared Tormentor of the Duergar-clan", \
      "Greater Tormentor of the Duergar-clan", \
      "Tyrant of the Duergar-clan" })

#define DUERGAR_SUBLOC "duergar_subloc"

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

public mixed query_guild_trainer_race()
{
   return "/d/Kalad/common/guilds/duergar/train";
}

int
query_guild_keep_player(object ob)
{
   ob->add_subloc(DUERGAR_SUBLOC,TO);
   return 1;
}

/* Function name: query_def_post
* Description:   We change the default post office for our members.
* Returns:       The new postoffice
*/

/* public string
* query_def_post()
* {
* return "/d/Kalad/common/wild/pass/dwarf/shop/post";
* }
*/

/* Function name: query_duergar_level
* Description:   Get the players numerical guild level
* Returns:       The numeric guild level
*/
int
query_duergar_level()
{
   return shadow_who->query_base_stat(SS_RACE) / 5;
}

/* Function name: query_guild_title_race
* Description:   We change the title of our members depending on their level
* Returns:       The title
*/
string query_guild_title_race()
{
   int stat;

   stat = query_duergar_level();

   if (stat < 0)
      stat = 0;

   if (stat > sizeof(TITLES) -1)
      stat = sizeof(TITLES) -1;

   return TITLES[stat];
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

   /* Wizards get to keep their own title */
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

   if(subloc != DUERGAR_SUBLOC)
      return shadow_who->show_subloc(subloc, me, for_obj);

   if (for_obj == me)
      str = "You have ";
   else
      str = capitalize(me->query_pronoun()) + " has ";


   return str + "an insane glint in the eyes.\n";
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

   str = TP->list_major_guilds();
   if (str)
      write("You are member of following guilds.\n" + str);
   else
      write("You are not member of any guilds.\n");

   return 1;
}

