/*******************************************************************\
| LIBS_PLAYER.C                                                     |
\*******************************************************************/

/*
 * 06/02/13 Arandir	Created
 * 06/02/21 Arandir     Added querying position
 *
 */

#include <std.h>

#include "defs.h"

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to names and descriptions                       |
\*******************************************************************/

/*
 * Function name : s_get_name
 * Function name : s_get_Name
 *
 */

varargs string s_get_name (object oWho = this_player ())
{
  return (lower_case (oWho->query_real_name ()));
}

varargs string s_get_Name (object oWho = this_player ())
{
  return (capitalize (oWho->query_real_name ()));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions related to position                                     |
\*******************************************************************/

/*
 * Function name : s_is_player
 *
 */

int s_is_player (mixed xWho)
{
  string sWho = objectp (xWho) ? s_get_name (xWho) : xWho;
  return (SECURITY->exist_player (sWho));
}

/*
 * Function name : s_is_junior
 *
 */

int s_is_junior (mixed xWho)
{
  string sWho = objectp (xWho) ? s_get_name (xWho) : xWho;
  return (wildmatch ("*jr", sWho));
}

/*
 * Function name : s_is_wizard
 *
 */

varargs int s_is_wizard (mixed xWho, int iLevel = WIZ_APPRENTICE)
{
  string sWho = objectp (xWho) ? s_get_name (xWho) : xWho;
  return (SECURITY->query_wiz_level (sWho) >= iLevel);
}

//-------------------------------------------------------------------

