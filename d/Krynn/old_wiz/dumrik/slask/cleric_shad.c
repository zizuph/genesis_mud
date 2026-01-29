//               Autoloading shadow for layman clerics of
//               the Occupational Solamnian Knight Guild   
// creator(s):   Grace  10 Aug 1994
// last update: 
// purpose:      occ knight layman-slot shadow
// note:         modified from /d/Krynn/solamn/guild/obj/lay_shadow.c
// bug(s):
// to-do:

inherit "/std/guild/guild_lay_sh";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>
#define SPUR "/d/Krynn/solamn/hctower/spur/room/"

/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
string *
query_guild_trainer_lay()
{
    return ({ SPUR + "train3" });
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int 
query_guild_tax_lay()
{ 
    return shadow_who->query_learn_pref(SS_LAYMAN); 
}

/*
 * Function name: query_guild_style_lay
 * Description:  Return the style of the guild
 */
string 
query_guild_style_lay() 
{ 
    return "cleric"; 
} 

/*
 * Function name: query_guild_name_lay
 * Description:  Query the name of the guild
 */
string 
query_guild_name_lay() 
{ 
    return GUILD_NAME_CLERIC; 
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    set_alarm(10.0,0.0,"delayed_query_guild_keep_player",ob);
    return 1;
    if (ob->query_guild_name_occ() != "Solamnian Knights" ||
	ob->query_knight_level() < 4)
      return 0; 
    return 1;
}

void
delayed_query_guild_keep_player(object ob)
{
    if (ob->query_guild_name_occ() != "Solamnian Knights" ||
	ob->query_knight_level() < 4)
      ob->remove_guild_lay();
}


// DO WE NEED THIS FOLLOWING CHECK?
/*
 * Function name: query_guild_not_allow_join_lay
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
			       string name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
      return 1;
    
    NF("You cannot join another guild. You have dedicated your life to Paladine!\n");
    if (player->query_guild_name_occ() != "Solamnian Knights")
      return 1;  
    
    return 0;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
