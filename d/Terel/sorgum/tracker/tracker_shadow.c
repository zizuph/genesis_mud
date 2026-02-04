/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tracker_shadow.c
 *
 * Gypsy guild shadow
 *
 * inheritance hierarchy:
 *     /std/shadow -> /std/guild/guild_base -> /std/guild/guild_occ_sh
 *
 * static object shadow_who is in /std/shadow.c
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include "tracker_defs.h"

/*
 * Function name: query_guild_tax_occ
 * Description:   What's the tax to pay at this guild? 
 * Returns:       the tax this guild wants
 */
int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

/*
 * Function name: query_guild_style_occ
 * Description:   What style is this guild? fighter, magic, cleric or thief.
 * Returns:       string - holding the style of guild
 */
public string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:   Returns the name of the guild this shadow represents
 * Returns:	  The name of the guild
 */
public string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_title_occ
 * Description  : This function should return the occupational title off
 *                the player. Since this function is not called for wizards
 *                you do not have to distinct for them in this function.
 * Returns      : string - the title for the player.
 *                The title will be incorporated in the format
 *                "the <race title>, <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 */
public string
query_guild_title_occ()
{
    return "Experienced Bushman";
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:   Test if this guild allowed a player to join another
 * Arguments:     type  - the type of guild to join
 * 		  style - the style of the guild
 *		  name  - the name
 * Returns:       1 - I allow member to join another guild
 */
public int
query_guild_not_allow_join_occ(object player, string type, string style,
			       string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    return 0;
}

/*
 * Function name: init_occ_shadow()
 * Description: This function is called from autoload_shadow and may
 *              be used to initialize the shadow when it's loaded.
 * Arguments: The argument string sent to autoload_shadow.
 */
public void
init_occ_shadow(string arg)
{
    query_shadow_who()->catch_msg("init_occ_shadow() called.\n");
}


/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
public mixed
query_guild_skill_name(int type)
{
    switch (type) {
     case TRACKER_PSIONICS:
	return "psionics";
	break;
     case TRACKER_RANK:
	return "";
	break;
     default:
	return (string)query_shadow_who()->query_guild_skill_name(type);
	break;
    }
}

/* Function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *		  the player when the shadow is autoloading when a player
 *		  logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object player)
{
    string *banished;

    if (file_size(BANISHED) <= 0)
	return 1;

    FIX_EUID;
    banished = explode(read_file(BANISHED), "\n");
    if (member_array(player->query_real_name(), banished) != -1) {
	player->catch_msg("You have been banished from the tracker guild.\n");
	player->set_gypsy_rank(-1);
    }
    player->catch_msg("query_guild_keep_player() called.\n");
    return 1;
}

/* Function name: query_tracker_rank
 * Description:   Return the rank of the player
 * Returns:       rank as an integer
 */
nomask int
query_tracker_rank()
{
    return query_shadow_who()->query_skill(TRACKER_RANK);
}

/* Function name: set_tracker_rank
 * Description:   Set the rank of the player
 * Arguments:     rank - the new rank of the player
 */
nomask void
set_tracker_rank(int rank)
{
    query_shadow_who()->set_skill(TRACKER_RANK, rank);
}
