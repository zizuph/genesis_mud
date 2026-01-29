inherit "/std/guild/guild_race_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#define INSIGNIA "insignia"
/*
* Guild titles
*/

void
do_die(object killer)
{
    tell_room(E(killer),QCTNAME(shadow_who)+" gets a fevered look "+
    "in "+HIS(shadow_who)+" eye.\n",shadow_who);
    tell_object(shadow_who,"You get a fevered look in your eye.\n");
    shadow_who->command("shout Red Fang forever!!!");
    shadow_who->do_die(killer);
}

#define TITLES ({ "Grim Soldier of the Red Fang", \
      "Vicious Soldier of the Red Fang", \
      "Ferocious Soldier of the Red Fang", \
      "Fierce Soldier of the Red Fang", \
      "Grim Sergeant of the Red Fang", \
      "Vicious Sergeant of the Red Fang", \
      "Ferocious Sergeant of the Red Fang", \
      "Fierce Sergeant of the Red Fang", \
      "Grim Lieutenant of the Red Fang", \
      "Vicious Lieutenant of the Red Fang", \
      "Ferocious Lieutenant of the Red Fang", \
      "Fierce Lieutenant of the Red Fang", \
      "Grim Captain of the Red Fang", \
      "Vicious Captain of the Red Fang", \
      "Ferocious Captain of the Red Fang", \
      "Fierce Captain of the Red Fang", \
      "Ruthless Major of the Red Fang", \
      "Dreaded Lieutenant-Colonel of the Red Fang",\
      "Treacherous Colonel of the Red Fang", \
      "Merciless General of the Red Fang" })


#define SPECIAL_TITLE  "The Most Notorious Goblin in all of Kalad";

#define FANG_SUBLOC "fang_subloc"

int 
roundo(float i)
{
    int t;
    float a;
    t = ftoi(i);
    a = i - itof(t);
    if(a >= 0.5)
        return (t + 1);
    else
        return t;
}

object compare_stats(object ob1, object ob2)
{
    /* Returns the bigger stats of the two players */
    if(ob1->query_average_stat() >= ob2)
        return ob1;
    return ob2;
}
object *
others_with_same_title()
{
   int stat,i;
   object *obs;
   object *obs2 = ({});
   obs = users();
   for(i=0;i<sizeof(obs);i++)
   {
      stat = obs[i]->query_fang_level();
   
      if (stat < 0)
         stat = 0;
   
      if(obs[i]->test_bit("Kalad",1,14))
         stat = stat +1;

      if (stat > sizeof(TITLES) -1)
         obs2 += ({obs[i]});
   }
   return obs2;
}


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
   return "/d/Kalad/common/wild/pass/goblin/guild/train";
}

int
query_guild_keep_player(object ob)
{
   ob->add_subloc(FANG_SUBLOC,TO);
   set_alarm(1.0,0.0,"change_guilds",ob);
   return 1;
}

void
change_guilds(object ob)
{
    object sh;
    seteuid(getuid());
    sh = clone_object("/d/Kalad/common/guilds/red_fang/obj/fang_shadow");
    tell_object(ob,"The Red Fang Guild has been updated, and remodeld "+
    "slightly. Read the FANG BOARD for more info.\n");
    ob->remove_cmdsoul(FANG_SOUL);
call_other("/d/Kalad/common/guilds/red_fang/rooms/joinroom","ftrans",ob);
    remove_guild_race();
    remove_shadow();    
}

        

/* Function name: query_def_post
* Description:   We change the default post office for our members.
* Returns:       The new postoffice
*/

/* public string
* query_def_post()
* {
* return "/d/Kalad/common/wild/pass/goblin/guild/post";
* }
*/

/* Function name: query_fang_level
* Description:   Get the players numerical guild level
* Returns:       The numeric guild level
*/
int
query_fang_level()
{
   return roundo( (itof(shadow_who->query_base_stat(SS_RACE)) / 6.0) );
}

/* Function name: query_guild_title_race
* Description:   We change the title of our members depending on their level
* Returns:       The title
*/
string query_guild_title_race()
{
   int stat;
   object *obs,me;
   int i;
   stat = query_fang_level();
   
   if (stat < 0)
      stat = 0;
   
   
   if(shadow_who->test_bit("Kalad",1,14))
        stat = stat +1;

   if (stat > sizeof(TITLES) -1)
   {
      stat = sizeof(TITLES) -1;
      if(sizeof(obs = others_with_same_title()) )
      {
          for(i=0;i<sizeof(obs);i++)
          {
             if(compare_stats(shadow_who,obs[i]) != shadow_who)
                 return TITLES[stat];
          }
      }
      return SPECIAL_TITLE;
   }
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

public mixed
query_guild_skill_name(int type)
{
    if(type == SS_WOLF_RIDING)
        return "wolf riding";
}

