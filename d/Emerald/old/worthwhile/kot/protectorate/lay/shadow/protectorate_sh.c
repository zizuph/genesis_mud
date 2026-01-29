#include "../guild.h"

inherit "/std/guild/guild_lay_sh";
inherit PROT_SHADOW_DIR + "protectorate_shadow_common";

#include "/d/Emerald/sys/skills.h"

#include <ss_types.h>

#define SW shadow_who
#define MAX_GUILD_LEVEL 3

static string *titles = ({ "1", "2", "3" });

/* 
 * Function name: query_guild_tax_lay
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_lay() 
{ 
    return LAY_PROT_TAX; 
}

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return LAY_PROT_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return PROT_GUILD_NAME;
}

/*
 * Function name: query_guild_not_allow_join_lay
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
				string name)
{
    /* Wizards can join anything they want.  Note that this allows multiple lay
     * guilds, which can lead to some conflicts.
     */
    if (IS_WIZ(player))
    {
        return 0;
    }

    /* This checks to make sure that the new guild is not layman */
    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_lay()
{
    return min(MAX_GUILD_LEVEL, SW->query_stat(SS_LAYMAN) / 50);
}
    
/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
#if defined(GUILD_POST) && defined(GUILD_STARTLOC)
string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    if (this_player()->query_default_start_location() == GUILD_STARTLOC)
    {
        return GUILD_POST;
    }

    return SW->query_def_post();
}
#endif

/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_lay()
{
    return titles[query_guild_level_lay()];
}
    
/*
 * Function name: query_guild_trainer_lay
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_lay()
{
    return ({ LAY_PROT_OBJ_DIR + "protectorate_train" });
}

/*
 * Function name: start_player
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
start_player()
{
    SW->start_player();

    if (!start_kot_member(SW))
    {
        return;
    }

#ifdef GUILD_EMBLEM
    object guild_emblem;

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());
    
    if (guild_emblem = clone_object(GUILD_EMBLEM))
    {    
        guild_emblem->move(SW, 1);
    }
#endif

#ifdef GUILD_CMDSOUL
    /* add the guild's soul to the player */
    SW->add_cmdsoul(GUILD_CMDSOUL);
    SW->update_hooks();
#endif
}

/* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_lay_shadow(object who)
{
    return shadow_me(who, "layman", LAY_PROT_STYLE, PROT_GUILD_NAME);
}

mixed
wield(object wep)
{
    return protectorate_wield(wep, SW);
}

void
remove_kot_member(object who)
{
    ::remove_kot_member(who);

    /* Remove post */
    /* Remove startloc */

    SW->clear_guild_stat(SS_LAYMAN);
    remove_guild_lay();
}

int
query_kot_lay_member()
{
    return 1;
}

