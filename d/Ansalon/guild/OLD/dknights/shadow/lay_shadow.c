/*
 * File Name        : lay_shadow.c
 * By               : Elmore.
 * Date             : April, 2001.
 * Desc             : Layman branch of the Death Knights of Krynn.
 *                    Contains the magic part of the DK's.
 */

#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE2;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_trainer_occ
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_occ()
{
    return GUILD_ROOM + "laboratory";
}
    
/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object who = query_shadow_who();

    who->add_prop(LIVE_I_SEE_DARK, 5);

    /* Update the hooks */
    who->update_hooks();

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
    /* This checks to make sure that the new guild is not lay */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    return 0;
}


/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    set_alarm(1.0, 0.0, init_guild_member);
}


/* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int
add_lay_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    /* Update the hooks */
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}


