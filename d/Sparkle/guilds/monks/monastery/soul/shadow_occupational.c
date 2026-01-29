/*******************************************************************\
| SHADOW_OCCUPATIONAL.C                                             |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Got rid of delayed initialization
 * 03/06/24 Arandir     Minor changes to compile in the new area
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 98/??/?? Cirion	Created
 *
 */

#include "../defs.h"

inherit "/std/guild/guild_occ_sh";

#include "shadow_base.c"

//-------------------------------------------------------------------

/*
 * Function name : query_guild_title_occ
 * Description   : Returns the full occupational title of the player.
 *
 */

string query_guild_title_occ ()
{
  return (m_get_title (shadow_who));
}


int query_guild_tax_occ ()
{
  return (M_TAX_OCC);
}


string query_guild_style_occ ()
{
  return (M_STYLE_OCC);
}


string query_guild_name_occ()
{
  return (M_NAME_LONG);
}


/*
 * Function name : query_guild_trainer_occ
 * Description   : Gets a list of the training objects
 *
 */

mixed query_guild_trainer_occ ()
{
  return (M_HOOK_TRAINING_OCCUPATIONAL);
}


/*
 * Function name : query_guild_leader_occ
 * Description   : Tells whether this player is a leader
 *
 */

int query_guild_leader_occ ()
{
  return (m_is_council_member (shadow_who));
}

//-------------------------------------------------------------------

/*
 * Function name : init_occ_shadow
 * Description   : Called when the player logs in and the shadow
 *                 is added. Delegates everything to m_shadow_init.
 *
 */

void init_occ_shadow (string sArgs)
{
  set_alarm (0.0, 0.0, &m_shadow_init ());
}

//-------------------------------------------------------------------

