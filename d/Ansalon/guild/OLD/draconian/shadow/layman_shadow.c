#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "../guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>

// Defines
#define MANA_SHADOW         "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define SPELL_MANAGER_SOUL  "/d/Genesis/specials/guilds/souls/spell_manager_soul"
//#define CASTER_SOUL       "/d/Genesis/specials/guilds/souls/example_caster_soul"
#define MAX_GUILD_LEVEL 36
// Prototypes
public object   query_top_shadow();

string gDracType;

/* Prototypes */
void remove_layman_member();

static string *kapak_titles = ({"New Kapak Hatchling of Krynn",
    "Experienced Kapak Hatchling of Krynn",
    "Learned Kapak Hatchling of Krynn",
    "Dauntless Kapak Hatchling of Krynn",
    "Proud Kapak Hatchling of Krynn",
    "Vicious Kapak Hatchling of Krynn",
    "Victorious Kapak Hatchling of Krynn",
    "Leading Kapak Hatchling of Krynn",
    "Commanding Kapak Hatchling of Krynn",
    "New Kapak Youngling of Krynn",
    "Experienced Kapak Youngling of Krynn",
    "Learned Kapak Youngling of Krynn",
    "Dauntless Kapak Youngling of Krynn",
    "Proud Kapak Youngling of Krynn",
    "Vicious Kapak Youngling of Krynn",
    "Victorious Kapak Youngling of Krynn",
    "Leading Kapak Youngling of Krynn",
    "Commanding Kapak Youngling of Krynn",
    "New Kapak Draconian of Krynn",
    "Experienced Kapak Draconian of Krynn",
    "Learned Kapak Draconian of Krynn",
    "Dauntless Kapak Draconian of Krynn",
    "Proud Kapak Draconian of Krynn",
    "Vicious Kapak Draconian of Krynn",
    "Victorious Kapak Draconian of Krynn",
    "Leading Kapak Draconian of Krynn",
    "Commanding Kapak Draconian of Krynn",
    "New Kapak Wyrm of Krynn",
    "Experienced Kapak Wyrm of Krynn",
    "Learned Kapak Wyrm of Krynn",
    "Dauntless Kapak Wyrm of Krynn",
    "Proud Kapak Wyrm of Krynn",
    "Vicious Kapak Wyrm of Krynn",
    "Victorious Kapak Wyrm of Krynn",
    "Leading Kapak Wyrm of Krynn",
    "Commanding Kapak Wyrm of Krynn",
    "Elder Kapak Wyrm of Krynn"});
	
static string *bozak_titles =  ({"New Bozak Hatchling of Krynn",
    "Experienced Bozak Hatchling of Krynn",
    "Learned Bozak Hatchling of Krynn",
    "Dauntless Bozak Hatchling of Krynn",
    "Proud Bozak Hatchling of Krynn",
    "Vicious Bozak Hatchling of Krynn",
    "Victorious Bozak Hatchling of Krynn",
    "Leading Bozak Hatchling of Krynn",
    "Commanding Bozak Hatchling of Krynn",
    "New Bozak Youngling of Krynn",
    "Experienced Bozak Youngling of Krynn",
    "Learned Bozak Youngling of Krynn",
    "Dauntless Bozak Youngling of Krynn",
    "Proud Bozak Youngling of Krynn",
    "Vicious Bozak Youngling of Krynn",
    "Victorious Bozak Youngling of Krynn",
    "Leading Bozak Youngling of Krynn",
    "Commanding Bozak Youngling of Krynn",
    "New Bozak Draconian of Krynn",
    "Experienced Bozak Draconian of Krynn",
    "Learned Bozak Draconian of Krynn",
    "Dauntless Bozak Draconian of Krynn",
    "Proud Bozak Draconian of Krynn",
    "Vicious Bozak Draconian of Krynn",
    "Victorious Bozak Draconian of Krynn",
    "Leading Bozak Draconian of Krynn",
    "Commanding Bozak Draconian of Krynn",
    "New Bozak Wyrm of Krynn",
    "Experienced Bozak Wyrm of Krynn",
    "Learned Bozak Wyrm of Krynn",
    "Dauntless Bozak Wyrm of Krynn",
    "Proud Bozak Wyrm of Krynn",
    "Vicious Bozak Wyrm of Krynn",
    "Victorious Bozak Wyrm of Krynn",
    "Leading Bozak Wyrm of Krynn",
    "Commanding Bozak Wyrm of Krynn",
    "Elder Bozak Wyrm of Krynn"});
	
static string *sivak_titles = ({"New Sivak Hatchling of Krynn",
    "Experienced Sivak Hatchling of Krynn",
    "Learned Sivak Hatchling of Krynn",
    "Dauntless Sivak Hatchling of Krynn",
    "Proud Sivak Hatchling of Krynn",
    "Vicious Sivak Hatchling of Krynn",
    "Victorious Sivak Hatchling of Krynn",
    "Leading Sivak Hatchling of Krynn",
    "Commanding Sivak Hatchling of Krynn",
    "New Sivak Youngling of Krynn",
    "Experienced Sivak Youngling of Krynn",
    "Learned Sivak Youngling of Krynn",
    "Dauntless Sivak Youngling of Krynn",
    "Proud Sivak Youngling of Krynn",
    "Vicious Sivak Youngling of Krynn",
    "Victorious Sivak Youngling of Krynn",
    "Leading Sivak Youngling of Krynn",
    "Commanding Sivak Youngling of Krynn",
    "New Sivak Draconian of Krynn",
    "Experienced Sivak Draconian of Krynn",
    "Learned Sivak Draconian of Krynn",
    "Dauntless Sivak Draconian of Krynn",
    "Proud Sivak Draconian of Krynn",
    "Vicious Sivak Draconian of Krynn",
    "Victorious Sivak Draconian of Krynn",
    "Leading Sivak Draconian of Krynn",
    "Commanding Sivak Draconian of Krynn",
    "New Sivak Wyrm of Krynn",
    "Experienced Sivak Wyrm of Krynn",
    "Learned Sivak Wyrm of Krynn",
    "Dauntless Sivak Wyrm of Krynn",
    "Proud Sivak Wyrm of Krynn",
    "Vicious Sivak Wyrm of Krynn",
    "Victorious Sivak Wyrm of Krynn",
    "Leading Sivak Wyrm of Krynn",
    "Commanding Sivak Wyrm of Krynn",
    "Elder Sivak Wyrm of Krynn"});
	
static string *aurak_titles = ({"New Aurak Hatchling of Krynn",
    "Experienced Aurak Hatchling of Krynn",
    "Learned Aurak Hatchling of Krynn",
    "Dauntless Aurak Hatchling of Krynn",
    "Proud Aurak Hatchling of Krynn",
    "Vicious Aurak Hatchling of Krynn",
    "Victorious Aurak Hatchling of Krynn",
    "Leading Aurak Hatchling of Krynn",
    "Commanding Aurak Hatchling of Krynn",
    "New Aurak Youngling of Krynn",
    "Experienced Aurak Youngling of Krynn",
    "Learned Aurak Youngling of Krynn",
    "Dauntless Aurak Youngling of Krynn",
    "Proud Aurak Youngling of Krynn",
    "Vicious Aurak Youngling of Krynn",
    "Victorious Aurak Youngling of Krynn",
    "Leading Aurak Youngling of Krynn",
    "Commanding Aurak Youngling of Krynn",
    "New Aurak Draconian of Krynn",
    "Experienced Aurak Draconian of Krynn",
    "Learned Aurak Draconian of Krynn",
    "Dauntless Aurak Draconian of Krynn",
    "Proud Aurak Draconian of Krynn",
    "Vicious Aurak Draconian of Krynn",
    "Victorious Aurak Draconian of Krynn",
    "Leading Aurak Draconian of Krynn",
    "Commanding Aurak Draconian of Krynn",
    "New Aurak Wyrm of Krynn",
    "Experienced Aurak Wyrm of Krynn",
    "Learned Aurak Wyrm of Krynn",
    "Dauntless Aurak Wyrm of Krynn",
    "Proud Aurak Wyrm of Krynn",
    "Vicious Aurak Wyrm of Krynn",
    "Victorious Aurak Wyrm of Krynn",
    "Leading Aurak Wyrm of Krynn",
    "Commanding Aurak Wyrm of Krynn",
    "Elder Aurak Wyrm of Krynn"});
/* 
 * Function name: query_guild_tax_layman
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_layman() 
{ 
    return LAY_GUILD_TAX; 
}

/*
 * Function name: query_guild_style_layman
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_layman()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_layman
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_layman()
{
    return GUILD_NAME_LAYMAN;
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_member(object who)
{
    return 0;
}

public nomask void
check_valid_race(object who)
{
    if((who->query_race_name() != "draconian") &&
      (!who->query_wiz_level()) &&
      (!who->query_ghost()))
    {
        who->catch_tell("You are no longer a draconian!\n");
	    set_alarm(1.0, 0.0, remove_layman_member);
    }
}
 
/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:	  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    /* Set an alarm to be sure the proper souls are loaded, then check race. */
    set_alarm(5.0, 0.0, &check_valid_race(ob));

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_layman
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_layman(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not layman */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_lay()
{
    return MIN(MAX_GUILD_LEVEL, SW->query_stat(SS_LAYMAN) /4);
}
    
/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
    return SW->query_def_post();
}

/*
 * Function name: query_guild_title_layman
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_layman()
{
	gDracType = SW->query_drac_type();
    switch (gDracType)
    {
      case "kapak":
		return kapak_titles[query_guild_level_lay()];
      case "aurak":
		return aurak_titles[query_guild_level_lay()];
      case "bozak":
		return bozak_titles[query_guild_level_lay()];
      case "sivak":
		return sivak_titles[query_guild_level_lay()];
	}
}
    
/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    return 0;
}

/*
 * Function name: query_guild_trainer_layman
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_layman()
{
    return ({ GUILD_ROOM + "joinroom" });
}

/*
 * Function name: init_kapak
 * Description:   This is called when a kapak player is initialized
 */
public void
init_kapak()
{
	return;
}

/*
 * Function name: init_aurak
 * Description:   This is called when a aurak player is initialized
 */
public void
init_aurak()
{
	return;
}

/*
 * Function name: init_bozak
 * Description:   This is called when a bozak player is initialized
 */
public void
init_bozak()
{
	
	return;
}

/*
 * Function name: init_sivak
 * Description:   This is called when a sivak player is initialized
 */
public void
init_sivak()
{
	return;
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{   
    /* add the guild's soul to the player */
    SW->add_cmdsoul(GUILD_CMDSOUL);
    
    // Make sure the command soul gets added
    //SW->add_cmdsoul(SPELL_MANAGER_SOUL);
    //SW->add_cmdsoul(CASTER_SOUL);
	
	//if (!query_top_shadow()->has_mana_shadow())
    //{
    //    clone_object(MANA_SHADOW)->shadow_me(SW);
   // }
	
    SW->update_hooks();

    //The rest will be handled by the race shadow
}

/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
}

/* 
 * Function name: add_layman_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_layman_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME_LAYMAN);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
}

/*
 * Function name: remove_layman_member
 * Description:   remove this member from the guild
 */
void
remove_layman_member()
{
    /* Clear the player's guild stat */
    SW->clear_guild_stat(SS_LAYMAN);

    SW->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
	//CASTER_SOUL->remove_spells(shadow_who);
	query_top_shadow()->remove_mana_shadow();
	::remove_shadow();    
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

/* Function name: autoload_shadow
 * Description:   Get the saved string from the autoload_shadow string.
 */
void
init_layman_shadow(mixed arg)
{
	gDracType = SW->query_drac_type();
	
    switch (gDracType)
    {
      case "kapak":
	  {
		init_kapak();
		break;
	  }
      case "aurak":
	  {
		init_aurak();
		break;
	  }
      case "bozak":
	  {
		init_bozak();
		break;
	  }
      case "sivak":
	  {
		init_sivak();
		break;
	  }
	}
}


