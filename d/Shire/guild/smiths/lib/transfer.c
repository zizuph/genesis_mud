/*******************************************************************\
| transfer.c
+-------------------------------------------------------------------+
| The purpose of this object is to store a mapping of Smith's
| and their lay guild experience when transferring to craft
|
| Palmer 15 July 2006
|
\*******************************************************************/


#pragma save_binary;

inherit "/std/object.c";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"


//-------------------------------------------------------------------

/*
 * Variable name : players
 * Description   : A mapping that keeps information on the number of
 *                 items forged by each player. The primary index is
 *                 by item name, the secondary is by player name.
 *
 */
 
mapping players = ([]);

//-------------------------------------------------------------------

/*
 * Function name : create_object
 * Description   : Restores the master data from the log.
 *
 */

void
create_object () 
{
    setuid (); seteuid (getuid ());
    set_name("transfer_master");
    restore_object(SMITHS_TRANSFER_LOG);
}

//-------------------------------------------------------------------

/*
 * Function name : add_player
 * Description   : Add player who left lay guild to mapping
 *
 */

void
add_player(string player_name, int guild_exp)
{
    players[player_name] = guild_exp;
    save_object(SMITHS_TRANSFER_LOG);
}

void
remove_player(string player_name)
{
    if (players[player_name])
    {
        players = m_delete(players, player_name);
        save_object(SMITHS_TRANSFER_LOG);
    }

}

/*
 * Function name : query_lay_exp
 * Description   : Returns the lay experience a player had
 *
 */

int
query_player(string player_name)
{
    int guild_exp;

    if (member_array(player_name, m_indexes(players)) == -1)
        return 0;

    guild_exp = players[player_name];

    return guild_exp;
}

