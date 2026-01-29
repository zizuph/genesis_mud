/*
* This is the autoloading shadow for the krynn gnome racial guild.
*
* Begun by Percy
* Completed by Dajala
*/

inherit "/std/guild/guild_race_sh";
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>

#define GUILDMASTER "/d/Krynn/gnome/guild/gmaster"

/*
* Prototypes
*/
int query_gnome_level();

/*
* Function name: query_guild_tax
* Description:   Set the initial tax
*/
int query_guild_tax_race() { return GNOME_TAX; }

/*
* Function name: query_guild_style_race
* Description:  Return the style of the guild
*/
string query_guild_style_race() { return "gnome"; }

/*
* Function name: query_guild_name_race
* Description:  Query the name of the guild
*/
string query_guild_name_race() { return GNOME_NAME; }

/*
* Function name: query_guild_keep_player
* Description:   Test if we want to keep the player in the guild.
* out the proper way later.
* Arguments:     ob - the player.
* Returns:  1 if keeping, 0 if not.
*/
int
query_guild_keep_player(object ob)
{   
   string race;
   int x;

   ob->add_subloc(KGN_SUB, this_object());

   race = (ob->query_race_name());
   if(race != "gnome")
   {
	ob->catch_msg("Suddenly, you don't understand gnomish anymore.\n");
	ob->catch_msg("Inventors are required to be gnomes.\n");
	x = strlen(race) - 1;
	if (race[x..x] == "f")
		race = race[0..x-1] + "ve";
	ob->catch_msg("We don't like " + race + "s in our guild.\n");
	set_alarm(1.0, -1.0, "kick_out", ob);
        return 1;
   }
   return 1;
}

void
kick_out(object player)
{
	player->command("ack");
	"/d/Krynn/gnome/guild/joinroom.c"->do_leave(player);
}

/*
* Function name: query_guild_not_allow_join_race
* Description:  Check if we allow that the player joins another guild.
* Arguments:     player - the player
*  type, style, name - the type, style and name of the
*		       intended guild.
* Returns:  1 if we do not allow, else 0
*/
int
query_guild_not_allow_join_race(object player, string type, string style,
   string name)
{
   if (::query_guild_not_allow_join_race(player, type, style, name))
      return 1;
    
   return 0;
}

/*
* Function name: query_def_post
* Description:   We change the default post office for our members.
* Returns:  The new postoffice
*
* string query_def_post() { return "/d/Krynn/gnome/mailroom.c"; }
*/

/*
* Function name: query_guild_title_race
* Description:   What is the title of this gnome?
* Returns:  The gnome title
*/
string
get_level(int level, int max_level)
{
    string str;
    int x;

    level = level - max_level + 1;
    str = "" + level;
    x = strlen(str) - 1;
    if(str[x..x] == "1")
	str += "st";
    else if(str[x..x] == "2")
	str += "nd";
    else if(str[x..x] == "3")
	str += "rd";
    else str += "th";
    return GNOME_TITLES[max_level] + " of the " + str + " degree";
}

string
query_guild_title_race() 
{ 
   int level, promoted;

   level = query_gnome_level();
   promoted = (shadow_who->query_skill(SS_PROMOTE));
   if(level < 8)   
	return GNOME_TITLES[level];
   if (promoted == 0)
	return get_level(level, 7);
   if(level < 11)   
	return GNOME_TITLES[level];
   if (promoted == 1)
	return get_level(level, 10);
   if(level < 13)   
	return GNOME_TITLES[level];
   if(promoted > 2 && (GUILDMASTER->highest_level(shadow_who, level)))
	return GNOME_TITLES[13];
   return get_level(level, 12);
}

/*
* Function name: query_gnome_level
* Description:   What level has the gnome achieved?
* Returns:  the level
*/
int
query_gnome_level()
{
   object ob;
   if (ob = present("k_gizmo", shadow_who))
      return ob->query_gnome_level();
   return 0;
}


/*
* Function name: query_guild_skill_name
* Description:   When a players uses the skills command he should get the
*  the skill names, not the 'special' string.
* Arguments:     type - the number of the skill
* Returns:  0 if no skill of mine, else the string.
*/

mixed
query_guild_skill_name(int type)
{
   if (type == SS_BUILD)
	return "build";
   if (type == SS_WEP_CLUB)
	return"club/hammer";
   if (type == SS_PROMOTE)
	return 0;
   return 0;
}


/*
* Function name: show_subloc
* Description:   This function is called each time someone looks at us
* Arguments:     subloc  - Our subloc
*  me      - I
*  for_obj - The looker
* Returns:  The string the looker shall see
*/
string
show_subloc(string subloc, object me, object for_obj)
{
   string str, subtitle;
   
   if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";

   if (subloc != KGN_SUB)
      return shadow_who->show_subloc(subloc, me, for_obj);

   if (for_obj == me)
      str = "You are ";
   else
      str = capitalize(me->query_pronoun(me)) + " is ";
   
   
   return str + "an Inventor.\n";
}


/*
* Function name: leave_inv
* Description:   masked from /std/container.c 
		 necessary for the springs-module
		 from here various routines in the soul are called.
* Arguments:	 (carried over)
* Returns:	 
*/

void
leave_inv(object ob, object to)
{
   if(TP->query_property("_gnome_i_springs_on"))
	if(!("/d/Krynn/dajala/kgnome_n.c"->spring_check(TP)))
		return;
		

/*
* Function name:
* Description:
* Arguments:
* Returns:
*/
