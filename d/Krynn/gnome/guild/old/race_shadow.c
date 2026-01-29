/*
* This is the autoloading shadow for the krynn gnome racial guild.
*
* Made by Percy
*/

inherit "/std/guild/guild_race_sh";
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>

#define KGN_SUB "kgnome_subloc"

/*
* Prototypes
*/
int update_level(int stat);
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
  /* Shouldn't be any reason that they are not a "gnome" gnome */
  /* if they are a member we want to keep */
   if(ob->query_race_name() == "gnome")
	return 1;
   return 0;
}

/*
* Function name: query_guild_not_allow_join_race
* Description:  Check if we allow that the player joins another guild.
* Arguments:     player - the player
*  type, style, name - the type, style and name of the
*intended guild.
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
* Function name: query_gnome_level
* Description:   What level has the gnome achieved?
* Returns:  the level
*/
int
query_gnome_level()
{
   object ob;
   if (ob = present("k_gizmo", query_shadow_who()))
      return ob->query_gnome_level();
   return 0;
}

/*
* Function name: query_gnome_modules
* Description:   gets the gnomes modules for his gizmo.
* Returns:  an array of int flags for the modules
*/
query_gnome_modules()
{ 
   object ob;
   if (ob = present("k_gizmo", query_shadow_who()))
      return ob->query_modules();
} 

/*
* Function name: set_gnome_level
* Description:   sets the gnomes level in the guild.
* Returns:  the level
*/
set_gnome_level(level)
{
   object ob;
   if (ob = present("k_gizmo", query_shadow_who(lower_case(this_object()->query_name()))))
   {
	ob->set_gnome_level(level);
	return 1;
   }
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
query_guild_title_race() 
{ 
   return GNOME_TITLES[query_gnome_level()];
}


/*
* Function name: query_guild_skill_name
* Description:   When a players uses the skills command he should get the
*  the skill names, not the 'special' string.
* Arguments:     type - the number of the skill
* Returns:  0 if no skill of mine, else the string.
   *
mixed
query_guild_skill_name(int type)
{
   if (type >= SS_PRESTIGE_ACC && type <= SS_CHARITY)
      return "";
   
   if ((type < SS_RESCUE) || (type > SS_KICK))
      return 0;
   
   return KNIGHT_SKILL_DESC[type - SS_RESCUE];
}

*/


int
update_level(int stat)
{
	int level;

	level = 1;
	if (stat >= L2) level = 2;
	if (stat >= L3) level = 3;
	if (stat >= L4) level = 4;
	if (stat >= L5) level = 5;
	if (stat >= L6) level = 6;
	if (stat >= L7) level = 7;
	if (stat >= L8) level = 8;
	if (stat >= L9) level = 9;
	if (stat >= L10)
	{
		level = (stat/5)+2;
	}
	return level;
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
      return query_shadow_who()->show_subloc(subloc, me, for_obj);
   
   if (for_obj == me)
      str = "You are ";
   else
      str = capitalize(me->query_pronoun()) + " is ";
   
   
   return str + "a member of Krynn gnomes.\n";
}



/*
* Function name:
* Description:
* Arguments:
* Returns:
*/
