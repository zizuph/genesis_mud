inherit "/std/guild/guild_lay_sh";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"
#define KALAD_SHADOW_CONFUSED "_kalad_shadow_confused"
#define KALAD_BOMB_DELAY "_kalad_bomb_delay"
#define PTLOG  "/d/Kalad/common/guilds/shadow_walkers/PLAYER_TITLES/"

string my_title;

string
query_shadow_walker_title()
{
    return my_title;
}

void
set_shadow_walker_title(string str)
{
    my_title = str;
}


/*
* Guild titles
*/

#define TITLES ({ "Cutthroat", "Feared Cutthroat", "Pilferer", \
                   "Feared Pilferer", "Rogue", "Feared Rogue", \
                  "Arsonist", "Feared Arsonist", "Shadow Lurker", \
                  "Street Thug", "Shadow Menace", "Brigand", \
                  "Alley Brigand", "Notorious Thug", "Shadow Brute", \
                  "Shadow Walker", "Knight of the Streets", \
                  "Shadow Blazer", "Knight of the Shadows", \
                  "Lord of the Streets", "Lord of the Sewers", \
                  "Lord of the Whores", "Lord of the Thugs", \
                  "Lord of the Thieves", "Lord of the Shadows", \
                  "Lord of the Shadows of Kabal" })



int
hook_thief_steal_bonus(object victim, object place, object what)
{
    set_this_player(shadow_who);
    if(!living(victim))
    return 0;
    if(victim->query_prop(KALAD_SHADOW_CONFUSED))
    {
        TP->catch_msg("Your victim is distracted, this should "+
        "be easier....\n");
        return 500;
    }
    else
    {
        TP->catch_msg("Your victim is not distracted, this "+
        "could be very difficult....\n");
        return -500;
    }
}



query_guild_tax_lay()
{
   return TAX; /* Whatever you wish to set it to. */
}

public mixed 
query_guild_trainer_lay()
{
   return ({"/d/Kalad/common/guilds/shadow_walkers/train",
            "/d/Kalad/common/guilds/shadow_walkers/train2"});
}

void
bomb_attack_delay(object ob)
{
    int dex;
    float mtime;
    dex = ob->query_stat(1);
    mtime = itof(dex) / 10.0;
    mtime = 25.0 - mtime;
    ob->add_prop(KALAD_BOMB_DELAY,1);
    set_alarm(mtime,0.0,"bomb_attack_delay2",ob);
}

void
bomb_attack_delay2(object ob)
{
    tell_object(ob,"You feel ready to throw another bomb again.\n");
    ob->remove_prop(KALAD_BOMB_DELAY);
}


int
query_guild_keep_player(object ob)
{
   set_alarm(2.0,0.0,"get_souls",ob);
   return 1;
}

void
get_souls(object ob)
{
   int i;
   string *souls;
   object *wizs;
   seteuid(getuid());
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
       ob->remove_cmdsoul(souls[i]);
   ob->add_cmdsoul(SW_SOUL);
   for(i = 0; i < sizeof(souls); i++)
       if(souls[i] != SW_SOUL)
           ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
   restore_object(PTLOG+lower_case(ob->query_name()));
   wizs = users();
   for(i=0;i<sizeof(wizs);i++)
   {            
   if(wizs[i]->query_guild_name_lay() == "Shadow Walkers" && 
      wizs[i]->query_wiz_level())
   {
       tell_object(wizs[i],ob->query_name()+" has "+
       "entered the realms.\n");
   }
   }
}

int
query_mad_level()
{
    return shadow_who->query_base_stat(SS_LAYMAN) / 6;
}

string 
query_guild_title_lay()
{
   string ptitle;
   ptitle = query_shadow_walker_title();
   if(ptitle == "off")
      return "";
   if(!ptitle)
       ptitle = "Dinky Thief";
   return ptitle+" of the Shadow Walkers";
}

string
query_guild_style_lay()
{
   return GUILD_STYLE;
}

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
