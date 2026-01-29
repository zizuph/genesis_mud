/*
 * File:     layman_shadow.c
 * Created:  Cirion
 * Purpose:  The layman shadow for the monks. Most of
 *           the functions reside in the MONKLIB/monklib.c file.
 * Modification Log:
 *
 */
#pragma strict_types
#include "defs.h"

inherit "/std/guild/guild_lay_sh";
inherit MONKLIB;

#include <ss_types.h>
#define LAY_SH
#include "defs.h"
#include "shadow.h"



/*
 * Function name: query_monk
 * Description:   Returns 1 if the player has the monk
 *                shadow.
 * Arguments:     The type of monk to check for.
 * Returns:       1 if they are a monk of that type.
 */
varargs int
query_monk(int type = -1)
{
    if((type == SS_LAYMAN) || (type == -1))
        return 1;
    else
        return 0;
}

/*
 * Function name: query_guild_title_lay
 * Description:   Returns the full layman title
 *                of the player.
 * Arguments:     none
 * Returns:       the string title of the player
 */
string
query_guild_title_lay()
{
    return m_query_title (shadow_who);
}

int
query_guild_tax_lay() 
{
    return MONK_LAY_TAX;
}

string
query_guild_style_lay()
{
    return MONK_LAY_STYLE;
}

string
query_guild_name_lay()
{
    return MONK_LAY_NAME;
}

/*
 * Function name:  query_guild_trainer_lay
 * Description:    a list of all the training objects for this player.
 * Returns:        an array of training objects
 */
public mixed
query_guild_trainer_lay()
{
    return MONK_LIB + "train_layman";
}

/*
 * Function name: init_lay_shadow
 * Description:   Called when the player logs in and the shadow
 *                is added. Calls m_login after a delay, which will
 *                handle the checking for being banished, add the
 *                command soul, etc.
 * Arguments:
 * Returns:
 */
void
init_lay_shadow(string arg)
{
    set_alarm(1.0, 0.0, &m_login(shadow_who, SS_LAYMAN, this_object()));
}

/*
 * Function name: query_guild_leader_lay
 * Description  : Returns whether this player is considered to be a leader
 *                in one of his/her guilds. 
 * Returns      : int 1/0 - guild leader or not.
 */
public int
query_guild_leader_lay()
{
    // a council member is a guild leader
    return m_query_council_member (shadow_who);
}


