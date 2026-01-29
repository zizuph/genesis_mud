inherit "/std/guild/guild_race_sh";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>

#define CHAIN "chain"

/*
* Guild titles
*/
#define MALE_TITLES ({ "Newly Ordained Follower of Thanar", \
      "Follower of Thanar", \
      "Rising Follower of Thanar", \
      "Fervent Follower of Thanar", \
      "Great Follower of Thanar", \
      "Fanatical Follower of Thanar", \
      "Apprentice Disciple of Thanar", \
      "Disciple of Thanar", \
      "Rising Disciple of Thanar", \
      "Fervent Disciple of Thanar", \
      "Great Disciple of Thanar", \
      "Fanatical Disciple of Thanar", \
      "Noviciate Worshipper of Thanar", \
      "Worshipper of Thanar", \
      "Rising Worshipper of Thanar", \
      "Fervent Worshipper of Thanar", \
      "Great Worshipper of Thanar", \
      "Fanatical Worshipper of Thanar", \
      "Minor Inquisitor of Thanar", \
      "Inquisitor of Thanar", \
      "General Inquisitor of Thanar", \
      "Great Inquisitor of Thanar", \
      "Grand Inquisitor of Thanar", \
      "Chosen One of Thanar and bane of Goblins", \
      "Chosen One of Thanar and bane of Hobbits", \
      "Chosen One of Thanar and bane of Gnomes", \
      "Chosen One of Thanar and bane of Dwarves", \
      "Chosen One of Thanar and bane of Elves", \
      "Lesser Avatar of Thanar", \
      "Intermediate Avatar of Thanar", \
      "Greater Avatar of Thanar" })

#define FEMALE_TITLES ({ "Newly Ordained Follower of Thanar", \
      "Follower of Thanar", \
      "Rising Follower of Thanar", \
      "Fervent Follower of Thanar", \
      "Great Follower of Thanar", \
      "Fanatical Follower of Thanar", \
      "Apprentice Disciple of Thanar", \
      "Disciple of Thanar", \
      "Rising Disciple of Thanar", \
      "Fervent Disciple of Thanar", \
      "Great Disciple of Thanar", \
      "Fanatical Disciple of Thanar", \
      "Noviciate Worshipper of Thanar", \
      "Worshipper of Thanar", \
      "Rising Worshipper of Thanar", \
      "Fervent Worshipper of Thanar", \
      "Great Worshipper of Thanar", \
      "Fanatical Worshipper of Thanar", \
      "Minor Inquisitor of Thanar", \
      "Inquisitor of Thanar", \
      "General Inquisitor of Thanar", \
      "Great Inquisitor of Thanar", \
      "Grand Inquisitor of Thanar", \
      "Chosen one of Thanar and bane of Goblins", \
      "Chosen one of Thanar and bane of Hobbits", \
      "Chosen one of Thanar and bane of Gnomes", \
      "Chosen one of Thanar and bane of Dwarves", \
      "Chosen one of Thanar and bane of Elves", \
      "Lesser Avatar of Thanar", \
      "Intermediate Avatar of Thanar", \
      "Greater Avatar of Thanar" })
#define THANAR_SUBLOC "thanar_subloc"

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
   return THANAR(train);
}

int try_to_move(object ob);

int
query_guild_keep_player(object ob)
{
   if(try_to_move(ob)) return 0; // return zero if successful

   ob->add_subloc(THANAR_SUBLOC,TO);
   set_alarm(1.0,0.0,"entrance_message",ob);
   return 1;
}

void
entrance_message(object ob)
{
   ob->catch_msg("The voice of Thanar himself tells you:\n"+
      "Welcome Thanarian! Now go forth and fulfill your destiny!\n");
   return;
}

/* Function name: query_def_post
* Description:   We change the default post office for our members.
* Returns:       The new postoffice
*/

/* public string 
* query_def_post()
* {
* return "/d/Kalad/common/central/plaza/post_office.c";
* }
*/

/* Function name: query_thanar_level
* Description:   Get the players numerical guild level
* Returns:       The numeric guild level
*/
int
query_thanar_level()
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
   
   stat = query_thanar_level();
   
   if (stat < 0)
      stat = 0;
   
   if (stat > sizeof(MALE_TITLES) -1)
      stat = sizeof(MALE_TITLES) -1;
   
   if (shadow_who->query_gender() == G_FEMALE)
      if(shadow_who->query_prop("THANAR_SPECIAL_TITLE"))
          return FEMALE_TITLES[stat]+" and Savior of Thanar";
      else
          return FEMALE_TITLES[stat];
   else
      if(shadow_who->query_prop("THANAR_SPECIAL_TITLE"))
          return MALE_TITLES[stat]+" and Savior of Thanar";
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
   string pos;

   if(subloc != THANAR_SUBLOC)
      return shadow_who->show_subloc(subloc, me, for_obj);

   if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   
   if(!me->query_armour(A_NECK))
       return "";
   if(MASTER_OB(me->query_armour(A_NECK)) != "/d/Kalad/common/guilds/thanar/symbol")
       return "";
   if (for_obj == me)
      pos = "your";
   else
      pos = HIS(me);
   
   return "The emblem of Thanar gleams brightly on "+pos+ 
   " platinum chain necklace.\n";
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

public void
remove_thanar_without_checking_auto()
{
   remove_shadow();
}

#define MOVE_AGENT "/d/Raumdor/guilds/thanar/move"
#define MOVE_LOG_FILE "/d/Kalad/common/guilds/thanar/move_log"
#define MOVE_LOG(x) write_file(MOVE_LOG_FILE, ctime(time()) + " " + (x))

// returns 1 if the move was successful

private int
try_to_move(object ob)
{
  mixed err;
  string who = capitalize(ob->query_real_name());

  setuid();
  seteuid(getuid());

  MOVE_LOG("Move shadow loaded for player " + ob->query_real_name() + "\n");

  err =
    catch(MOVE_AGENT->log("Moving shadow loaded for player " + who + "\n"));

  if(err)
  {
      MOVE_LOG("Cannot communicate with the move agent, reason: " + err);
      return 0;
  }
  
  // try to call move agent in the other domain
  // zero return value means it is not possible to move
  if (!(MOVE_AGENT->move(ob)))
  {
      MOVE_LOG("Move attempt not successful for player " + who);
      return 0;
  }

  // here try to purge all old guild things if some still exist

  MOVE_AGENT->log("Old Thanar shadow was removed from " + who + "\n");

  return 1;
}
