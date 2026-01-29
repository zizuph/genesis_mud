
/*******************************************************************\
| MASTER.C                                                          |
+-------------------------------------------------------------------+
| A master object for the smith guild. The purpose of this object   |
| is to provide a place where all guild wide data are kept.         |
\*******************************************************************/

/*
 * 01/11/15 Arandir	Created
 * 02/04/09 Arandir	Added sm_remove_forged
 *
 */

#pragma save_binary;

inherit "/std/object.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"

//-------------------------------------------------------------------

/*
 * 01/11/15 Arandir
 *
 * The format of the forged items log is impractical in that
 * it indexes primarily by the item and secondarily by the player.
 *
 * Because count queries are either for a specific player and item,
 * or for a specific player and any item, it would be more efficient
 * if the indexes were reversed.
 *
 */

//-------------------------------------------------------------------

/*
 * Variable name : SM_ForgedItems
 * Description   : A mapping that keeps information on the number of
 *                 items forged by each player. The primary index is
 *                 by item name, the secondary is by player name.
 *
 */
 
mapping SM_ForgedItems = ([]);

//-------------------------------------------------------------------

/*
 * Function name : create_object
 * Description   : Restores the master data from the log.
 *
 */

void create_object () 
{
    setuid(); seteuid(getuid());
    set_name("smiths_master");
    restore_object(SMITHS_MASTER_LOG);
}


int query_forged_item(string sPlayer, string sItem)
{
  mapping mPlayerRecord;

  // Return 0 if the item or the player is not in the log.

  if (member_array(sItem, m_indexes(SM_ForgedItems)) == -1) return (0);
  mPlayerRecord = SM_ForgedItems[sItem];
  if (member_array(sPlayer, m_indexes(mPlayerRecord)) == -1) return (0);
  
  return (mPlayerRecord[sPlayer]);

}

/*
 * Function name : sm_query_forged_item
 * Description   : Returns the number of times a specific item was forged.
 *
 */

int sm_query_forged_item(object oPlayer, string sItem)
{
  string sPlayer = oPlayer->query_name();

  return query_forged_item(sPlayer, sItem);
}


//-------------------------------------------------------------------

/*
 * Function name : sm_query_forged_total
 * Description   : Returns the number of times a forging was done.
 *
 */

int sm_query_forged_total(object oPlayer)
{
  string sPlayer = oPlayer->query_name();
  string *aItems = m_indexes(SM_ForgedItems);
  int iCount = 0;
  mapping mPlayerRecord;
  int i;

  // Iterate over all items of the forge log and add up data for the
  // specific player that the function arguments refer to. To make
  // everything simpler, this code relies on the fact that access to a
  // nonexistent mapping item returns 0.

  for (i = 0 ; i < sizeof (aItems) ; i ++)
  {
    mPlayerRecord = SM_ForgedItems[aItems[i]];
    if (member_array(sPlayer, m_indexes(mPlayerRecord)) != -1)
    {
      iCount += SM_ForgedItems[aItems[i]][sPlayer];
    };
  };

  return (iCount);
}


/*
 * Function name : sm_increment_forged_item
 * Description   : Increments the number of times a specific item was forged.
 *
 */

void sm_increment_forged_item (object oPlayer, string sItem)
{
  string sPlayer = oPlayer->query_name();
  mapping mPlayerRecord = ([]);
  int ttl;
  
  // The count is set to 1 if the item or the player is not in the log.

  mPlayerRecord[sPlayer] = 1;

  if (member_array(sItem, m_indexes(SM_ForgedItems)) == -1)
  {
    SM_ForgedItems[sItem] = mPlayerRecord;
  }
  else
  {
    if (member_array(sPlayer, m_indexes(mPlayerRecord)) == -1)
    {
      SM_ForgedItems[sItem] += mPlayerRecord;
    };
    SM_ForgedItems[sItem][sPlayer] ++;
  };
  save_object(SMITHS_MASTER_LOG);
  // Increment ttl items forged in player prop.
  // We keep it there because its faster checking
  // it than going through the entire mapping when
  // determining titles etc
  // REMOVE THIS COMMENT AFTER REBOOT ON ~Aug 19 2006
  //ttl = oPlayer->query_prop(SMITHS_ITEMS_FORGED);
  ttl = sm_query_forged_total(oPlayer);
  oPlayer->add_prop(SMITHS_ITEMS_FORGED, ttl);
}



/*
 * Function name : remove_player_records
 * Description   : Removes a forging record for a player.
 *
 */

void remove_player_records(string player_name)
{
  mapping mPlayerRecord;
  int     i;
  string *aItems = m_indexes(SM_ForgedItems);

  // Iterate over all items of the forge log and remove data for the
  // specific player that the function arguments refer to.

  for (i = 0 ; i < sizeof (aItems) ; i ++)
  {
    SM_ForgedItems[aItems [i]] = m_delete(SM_ForgedItems[aItems[i]], player_name);
  };

  save_object(SMITHS_MASTER_LOG);
}

/*
 * Function name : sm_remove_forged
 * Description   : Removes a forging record for a player.
 *
 */

void sm_remove_forged(object oPlayer)
{
  string  sPlayer = oPlayer->query_name();
  remove_player_records(sPlayer);
}

