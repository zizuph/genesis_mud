inherit "/std/guild/guild_lay_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/guild/default.h"
#define CHAIN "chain"

/*
* Guild titles
*/
#define MALE_TITLES ({ "Student Merchant", \
      "Noviciate Merchant of Kabal", \
      "Apprentice Merchant of Kabal", \
      "Travelling Merchant of Kabal", \
      "Striving Merchant of Kabal", \
      "Independant Merchant of Kabal", \
      "Established Merchant of Kabal", \
      "Successful Merchant of Kabal", \
      "Fabulous Merchant of Kabal", \
      "Extravagant Merchant of Kabal", \
      "Affluent Merchant of Kabal", \
      "Wealthy Merchant of Kabal", \
      "Patron Merchant of Kabal", \
      "Noble Merchant of Kabal", \
      "Lord Merchant of Kabal", \
      "Master Merchant of Kabal" })

#define FEMALE_TITLES ({ "Student Merchant", \
      "Noviciate Merchant of Kabal", \
      "Apprentice Merchant of Kabal", \
      "Travelling Merchant of Kabal", \
      "Striving Merchant of Kabal", \
      "Independant Merchant of Kabal", \
      "Established Merchant of Kabal", \
      "Successful Merchant of Kabal", \
      "Fabulous Merchant of Kabal", \
      "Extravagant Merchant of Kabal", \
      "Affluent Merchant of Kabal", \
      "Wealthy Merchant of Kabal", \
      "Matron Merchant of Kabal", \
      "Noble Merchant of Kabal", \
      "Lady Merchant of Kabal", \
      "Mistress Merchant of Kabal" })
#define MERCHANT_SUBLOC "merchant_subloc"

private mixed stat_names, title, badge;
public string *cmembers;
/*
* Function name: query_guild_tax
* Description  : Set the initial tax
*/
query_guild_tax_lay()
{
   return TAX; /* Whatever you wish to set it to. */
}


/* Function name: query_def_post
* Description:   We change the default post office for our members.
* Returns:       The new postoffice
*/
string query_def_post()
{
   return "/d/Kalad/common/caravan/guild/post";
}

/* Function name: query_merchant_level
* Description:   Get the players numerical guild level
* Returns:       The numeric guild level
*/
int
query_merchant_level()
{
   return shadow_who->query_base_stat(SS_LAYMAN) / 10;
}

/* Function name: query_guild_title_lay
* Description:   We change the title of our members depending on their level
* Returns:       The title
*/
string query_guild_title_lay()
{
   int stat;
   
   stat = query_merchant_level();
   
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
   
   if(subloc != MERCHANT_SUBLOC)
      return shadow_who->show_subloc(subloc, me, for_obj);
   
   if (for_obj == me)
      str = "You have ";
   else
      str = capitalize(me->query_pronoun()) + " has ";
   
   
   return str + "the slick look of a Merchant.\n";
}

/*
* Function name: query_guild_style_race
* Description:   Get the style of this guild
* Returns:       String describing guild style
*/
string
query_guild_style_lay()
{
   return GUILD_STYLE;
}

/*
* Function name: query_guild_name_race
* Description:   Get the name of this guild
* Returns:       String naming guild
*/
string
query_guild_name_lay()
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
