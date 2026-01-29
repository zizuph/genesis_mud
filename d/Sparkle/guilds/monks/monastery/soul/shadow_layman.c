/*******************************************************************\
| SHADOW_LAYMAN.C                                                   |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Got rid of delayed initialization
 * 03/09/14 Arandir     Fixed trainer bug pointed out by Eowul
 * 03/06/24 Arandir     Minor changes to compile in the new area
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 98/??/?? Cirion	Created
 *
 */

#include "../defs.h"

inherit "/std/guild/guild_lay_sh";

#include "shadow_base.c"

//-------------------------------------------------------------------

/*
 * Function name : query_guild_title_lay
 * Description   : Returns the full layman title of the player.
 *
 */

string query_guild_title_lay ()
{
  return (m_get_title (shadow_who));
}


int query_guild_tax_lay ()
{
  return (M_TAX_LAY);
}


string query_guild_style_lay ()
{
  return (M_STYLE_LAY);
}


string query_guild_name_lay()
{
  return (M_NAME_LONG);
}


/*
 * Function name : query_guild_trainer_lay
 * Description   : Gets a list of the training objects
 *
 */

mixed query_guild_trainer_lay ()
{
  return (M_HOOK_TRAINING_LAYMAN);
}


/*
 * Function name : query_guild_leader_lay
 * Description   : Tells whether this player is a leader
 *
 */

int query_guild_leader_lay ()
{
  return (m_is_council_member (shadow_who));
}

//-------------------------------------------------------------------

/*
 * Function name : init_lay_shadow
 * Description   : Called when the player logs in and the shadow
 *                 is added. Delegates everything to m_shadow_init.
 *
 */

void init_lay_shadow (string sArgs)
{
  set_alarm (0.0, 0.0, &m_shadow_init ());
}

//-------------------------------------------------------------------

