/*
 * File:     occupational_shadow.c
 * Created:  Cirion
 * Purpose:  The occupational shadow for the monks. Most of
 *           the functions reside in the MONKLIB/monklib.c file.
 * Modification Log:
 *
 */
#pragma strict_types
#include "defs.h"

inherit "/std/guild/guild_occ_sh";
inherit MONKLIB;

#include <ss_types.h>
#define OCC_SH
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
    if((type == SS_OCCUP) || (type == -1))
        return 1;
    else
        return 0;
}


/*
 * Function name: query_guild_title_occ
 * Description:   Returns the full occupational title
 *                of the player.
 * Arguments:     none
 * Returns:       the string title of the player
 */
string
query_guild_title_occ()
{
    return m_query_title (shadow_who);
}

int
query_guild_tax_occ() 
{
    return MONK_OCC_TAX;
}

string
query_guild_style_occ()
{
    return MONK_OCC_STYLE;
}

string
query_guild_name_occ()
{
    return MONK_OCC_NAME;
}


/*
 * Function name:  query_guild_trainer_occ
 * Description:    a list of all the training objects for this player.
 * Returns:        an array of training objects
 */
public mixed
query_guild_trainer_occ()
{
    return MONK_LIB + "train_occupational";
}


/*
 * Function name: init_occ_shadow
 * Description:   Called when the player logs in and the shadow
 *                is added. Calls m_login after a delay, which will
 *                handle the checking for being banished, add the
 *                command soul, etc.
 * Arguments:
 * Returns:
 */
void
init_occ_shadow(string arg)
{
    set_alarm(1.0, 0.0, &m_login(shadow_who, SS_OCCUP, this_object()));
}

/*
 * Function name: query_guild_leader_occ
 * Description  : Returns whether this player is considered to be a leader
 *                in one of his/her guilds. 
 * Returns      : int 1/0 - guild leader or not.
 */
public int
query_guild_leader_occ()
{
    // a council member is a guild leader
    return m_query_council_member (shadow_who);
}


