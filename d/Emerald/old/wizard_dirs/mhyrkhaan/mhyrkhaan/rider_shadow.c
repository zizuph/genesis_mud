inherit "/std/guild/guild_lay_sh";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/goblin/guild/riders/default.h"

/*
 * /d/Kalad/common/wild/pass/goblin/guild/riders/rider_shadow.c
 * Purpose    : This is the shadow object for the Rider's Guild
 * Located    : Red Fang Rider's Guild
 * Created By : Mhyrkhaan 15.Mar.97
 * Modified By: Sarr 20.Mar.97
 */


/*
* Guild titles
*/


#define TITLES ({ "Novice Rider of the Red Fang", \
      "Learned Rider of the Red Fang", \
      "Trained Rider of the Red Fang", \
      "Experienced Rider of the Red Fang", \
      "Expert Rider of the Red Fang", \
      "Specialist Rider of the Red Fang", \
      "Master Rider of the Red Fang", \
      "Elite Rider of the Red Fang", \
      "Wolflord of the Riders of the Red Fang" })


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

int
query_guild_tax_lay()
{
    if(shadow_who->query_guild_name_race() == "Red Fang Guild")
        return TAX;
    else
        return TAX_NON_RACE;
}

public mixed 
query_guild_trainer_lay()
{
   return "/d/Kalad/common/wild/pass/goblin/guild/riders/train";
}

int
query_guild_keep_player(object ob)
{
   return 1;
}

int
query_rider_level()
{
   return roundo( (itof(shadow_who->query_base_stat(SS_LAYMAN)) / 16.0) );
}

string 
query_guild_title_lay()
{
    int index;
    index = query_rider_level();
    if(index > 8)
        index = 8;
    return TITLES[index];
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

public mixed
query_guild_skill_name(int type)
{
    if(type == SS_WOLF_RIDING)
        return "wolf riding";

    if(type == SS_WOLF_HANDLING)
        return "wolf handling";
}

