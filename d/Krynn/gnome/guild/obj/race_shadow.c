/*
* This is the autoloading shadow for the Krynn gnome racial guild.
*
* Begun by Percy
* Completed by Dajala
*/

#pragma save_binary

inherit "/std/guild/guild_race_sh";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

#define GUILDMASTER "/d/Krynn/gnome/guild/gmaster.c"

/*
* Prototypes
*/
int query_gnome_level();


/*
 * Function name: query_guild_trainer
 * Description:   The member is still in training, no skill-decay
 * Returns:       The path(s) to the trainroom(s)
 */
string *
query_guild_trainer_race()
{
    return ({ GGUILD + "trainroom" });
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int 
query_guild_tax_race() 
{ 
    return GNOME_TAX;
}

/*
 * Function name: query_guild_style_race
 * Description:  Return the style of the guild
 */
string 
query_guild_style_race() 
{ 
    return "gnome"; 
}

/*
* Function name: query_guild_name_race
* Description:  Query the name of the guild
*/
string 
query_guild_name_race() 
{
    return GNOME_NAME; 
}

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
    setuid();
    seteuid(getuid());
    "/d/Krynn/gnome/guild/joinroom.c"->do_leave(player);
}

/*
 * Function name: query_guild_not_allow_join_race
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *                     intended guild.
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
 * Returns:       The new postoffice
 *
 */

string
query_def_post() { return "/d/Krynn/gnome/mailroom.c"; }

/*
 * Function name: query_guild_title_race
 * Description:   What is the title of this gnome?
 * Returns:  The gnome title
 */
string
get_level(int level, int max_level)
{
    string str, *titles;
    int x;

    if(shadow_who->query_gender() == 1)
	titles = GNOME_TITLES_F;
    else
	titles = GNOME_TITLES;
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
    if(level > 5)
	return "Advanced " + titles[max_level];
    return titles[max_level] + " of the " + str + " degree";
}

string
query_guild_title_race() 
{ 
    int level, promoted;
    string *titles;

    if(shadow_who->query_gender() == 1)
	titles = GNOME_TITLES_F;
    else
	titles = GNOME_TITLES;
    level = query_gnome_level();
    promoted = (shadow_who->query_skill(SS_PROMOTE));
    setuid();seteuid(getuid());
    if(GUILDMASTER->highest_level(shadow_who, level, promoted) && promoted> 5)
	return titles[14];
    if(level < 8)   
	return titles[level];
    if (promoted == 0)
	return get_level(level, 7);
    if(level < 11)   
	return titles[level];
    if(promoted == 1)
	return get_level(level, 10);
    if(level < 13)
	return titles[level];
    if(promoted == 2)   
	return get_level(level, 12);
    if(level == 13)
	return titles[13];
    return get_level(level, 13);
}

/*
 * Function name: query_gnome_level
 * Description:   What level has the gnome achieved?
 * Returns:       The level
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
	return "club/hammer";
    if (type == SS_PROMOTE)
	return "";
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
    string str, str_add = "", subtitle;

    if (subloc != KGN_SUB)
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (for_obj == me)
	str = "You are an "; 
    else
	str = C(me->query_pronoun(me)) + " has the clever eyes of an ";

    if(shadow_who->query_skill(SS_PROMOTE))
	str_add = "active ";

    return str + str_add + "Inventor.\n";
}

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

void
gnome_move()
{
    object joinroom;
    
    joinroom = safely_load_master_file("/d/Krynn/guilds/gnomes/rooms/joinroom.c");
    
    if (objectp(joinroom) && joinroom->fix_member(shadow_who))
    {
        shadow_who->catch_msg("\n" +
        "***************************************************************\n" +
        "The gnomes guild has moved your research, if you encounter any \n" +
        "issues, please mail Carnak. Hope you enjoy the changes.\n" +
        "***************************************************************\n");
    } else
    {
        shadow_who->catch_msg("\n" +
        "***************************************************************\n" +
        "The gnomes guild has changed the structure of their facilities \n" +
        "and therefore need you to return there to move your research.  \n" +
        "***************************************************************\n");
    }
}

/*
 * Function name:   init_race_shadow()
 * Description:     This function is called from autoload_shadow and may
 *                  be used to initialize the shadow when it's loaded.
 * Arguments:       The argument string sent to autoload_shadow.
 */
public void
init_race_shadow(string arg)
{
/*    shadow_who->catch_msg("You were recalled to the inventor guild to " +
    "move your research due to a change in the custodial handling of the " +
    "facilities.\n");
    
    shadow_who->move_living("M", 
                            "/d/Krynn/guilds/gnomes/rooms/joinroom.c", 1, 0);
        
    shadow_who->command("join! the inventor guild");
*/
    set_alarm(3.0, 0.0, &gnome_move());
}

/*
* Function name:
* Description:
* Arguments:
* Returns:
*/


/**************************************************************************
 ******************** Functions for Modules *******************************
 **************************************************************************/

/* Don't fight back while operating the GnomishGestureMaker
 */

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 *		    We are unable to fight back if the GestureMatic is
 *		    operational.
 * Arguments:	    ob: The attacker
 */

public void
attacked_by(object ob)
{
    if(shadow_who->query_prop("_gnome_i_gmaker_on_"))
    {
	shadow_who->command("eeks");
	shadow_who->catch_msg("You cannot defend yourself with the GestureMatic "
	  + "being operational.\n");
    }
    shadow_who->attacked_by(ob);
    return;
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 *		    We are unable to fight if the GestureMatic is operational.
 * Arguments:	    The object to attack
 */
public void
attack_object(object ob)
{
    if(!(shadow_who->query_prop("_gnome_i_gmaker_on_")))
    {
	shadow_who->attack_object(ob);
	return;
    }
    shadow_who->catch_msg("You cannot fight with the GestureMatic "
      + "being operational.\n");
    return;
}



/* Spilling liquid while moving with an open funnel
 * For the Distillationapparatus
 */

void
enter_env(object dest, object old)
{
    if(shadow_who->query_prop("_gnome_i_funnel_open"))
	shadow_who->spill_liquid();
    shadow_who->enter_env(dest, old);
}
