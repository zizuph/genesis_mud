/*
  Guild shadow for the Calian warriors guild
  
  Created by Glykron & Nick
  New titles & team-title additions added to query_guild_title_occ() 
  by Maniac 3/94
  Council additions added by Maniac 5/94
*/



inherit "/std/guild/guild_occ_sh";
#include <ss_types.h>
#include <const.h>
#include <stdproperties.h>
#include "defs.h"
#include COUNCIL_DEFS


static string *rewards 
           = ({ "the colours of Caliana",
                "insignia of the Silver War Hammer",
                "insignia of the Golden Axe",
                "insignia of the Steel Spear",
                "insignia of the Mithril Halberd",
                "insignia of the Crystalline Sword" }); 
                  

/*
 *
 * Added by Nick
 */
string query_guild_style_occ() { return "fighter"; }
string query_guild_name_occ() { return "Calian warrior's guild"; }


/* Give greeting when a Calian logs on */
void greet()
{
    shadow_who->catch_msg("Greetings, " + query_guild_title_occ() +
                  "!\n");
}



/* Function to check for punishments or rewards set by the council
   for this player, carries them out if there are any.  Returns 1
   if player still in guild, 0 if not. */

int council_check(object pl)
{
  seteuid(getuid());
  COUNCIL_CODE->carry_out_punishments(pl);
  if (COUNCIL_CODE->is_expelled(pl))
    return 0;
  else return 1;
}


void init_occ_shadow(string str)
{
  ::init_occ_shadow(str);
  if (council_check(shadow_who))
  {
    set_alarm(1.5, 0.0, "greet");
    shadow_who->add_subloc(CALIA_REWARD, THIS);
  }
}



public string
show_subloc(string subloc, object on, object for_obj)
{
  string data;
  int lvl;

  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  return "";

  if (subloc != CALIA_REWARD)
  return on->show_subloc(subloc, on, for_obj);
    
  lvl = shadow_who->query_skill(REWARD);
  if (lvl > (sizeof(rewards) - 1)) lvl = sizeof(rewards) - 1;    

  if (for_obj != on)
    data = capitalize(on->query_pronoun()) + 
         " is wearing " + rewards[lvl] + ".\n";
  else
    data = "You are wearing " + rewards[lvl] + ".\n";

  return data;
  
}



int query_guild_tax_occ() { return GUILD_TAX; }

int query_guild_not_allow_join_occ(object player, string type, string style,
        string name)
{
    if(::query_guild_not_allow_join_occ(player, type, style, name))
	return 1;
    notify_fail("We brave fighters don't like to mess with magic.\n");
    if(style == "magic") return 1;
    return 0;
}


private string query_gender_title()
{
    switch(THIS->query_gender())
    {
	case G_MALE:	return "man";
	case G_FEMALE:	return "woman";
	case G_NEUTER:	return "monster";
    }
}



/*
  This next function, query_guild_title_occ(), added due to changes
  to way titles are called, 17/2/94, by Maniac
*/

string query_guild_title_occ()
{
    int occ_level, str, dex, con, dis, avg, title_level;
    object medallion, leader;
    string team_title, team_name;


    occ_level = THIS->query_stat(SS_OCCUP);
    
    str = THIS->query_stat(SS_STR);
    dex = THIS->query_stat(SS_DEX);
    con = THIS->query_stat(SS_CON);
    dis = THIS->query_stat(SS_DIS);


    /* Only the stats that make for a good warrior are considered */

    avg = (str + dex + con + dis) / 4; 

/* Now work out the Calian team title, if any */

  if (THIS->query_team_others() == ({})) team_title = "";
  else {

     if (sizeof(THIS->query_team()) > 0)
      {
        medallion = present("Calia_medallion", shadow_who);

       if (!medallion) team_title = "";
       else {
            team_name = medallion->query_team_title();

            if (team_name != "")
                 team_title = ", Proud Leader of " +
                               team_name;
            else team_title = "";
       }
      }
    else
      {
       leader = THIS->query_leader();
       medallion = present("Calia_medallion", leader);

       if (!medallion) team_title = "";
       else {
             team_name = medallion->query_team_title(); 

             if (team_name != "")
                   team_title = ", Trusted Member of " +
                               team_name;
             else team_title = "";
       }
      }
   }


    /* Title now reflects the effectiveness of the warrior, as well 
       as the level of SS_OCCUP */

    title_level = (occ_level + avg) / 2;
  
    if (title_level < 12) return "Calian Trainee" + team_title;
    if (title_level < 23) return "Calian Adventurer" + team_title;
    if (title_level < 34) return "Warrior of Calia" + team_title;
    if (title_level < 45) return "Swords"+query_gender_title()+
                                    " of Calia" + team_title;
    if (title_level < 56) return "Swashbuckler of Calia" + team_title;
    if (title_level < 67) return "Comrade in Arms of Calia" + team_title;
    if (title_level < 78) return "Cavalier of Calia" + team_title;
    if (title_level < 89) return "Paladin of Calia" + team_title;
    if (title_level < 100) return "Defender of Calia" + team_title;
    if (title_level < 111) return "Noble"+query_gender_title()
                                  +" of Calia" + team_title;
    if (title_level < 122) return "Calian Champion" + team_title;
    if (title_level < 133) return "Weapon Master of Calia" 
                                  + team_title;
    if ((title_level < 144) && (THIS->query_gender() == 1)) return 
        "Battle Heroine of Calia" + team_title;
    if ((title_level < 144) && (THIS->query_gender() != 1)) return
        "Battle Hero of Calia" + team_title;
    if (title_level < 155) return "War Legend of Calia" + team_title; 
    if (title_level >= 155) return 
          "Exalted Member of Caliana's Elite Guard" + team_title; 
}



string query_guild_skill_name(int skill)
{
    if(skill==SS_SWARM) return "swarm";
    if(skill==SS_MOVE_BEHIND) return "move behind";
    return (string) query_shadow_who()->query_guild_skill_name(skill);
}
