/*******************************************************************\
| LIBS_TOKEN.C                                                      |
\*******************************************************************/

/*
 * 07/05/19 Arandir     Merged with extraneous include
 * 03/07/09 Arandir	Created
 *
 */

#include "../defs.h"

//-------------------------------------------------------------------

// Data file definitions

#define M_ACCESS_MONK_TOKENS            mapping mMonkTokens = M_MONK_SRVR->m_get_monk_tokens ()
#define M_DELETE_MONK_TOKENS(sKey)      mMonkTokens = M_MONK_SRVR->m_delete_monk_tokens (sKey)

#define M_SAVE_ACCESSED                 M_MONK_SRVR->m_save_object ()


#define M_MONK_TOKENS_LOCATION          0
#define M_MONK_TOKENS_DESC_SHORT        1
#define M_MONK_TOKENS_DESC_LONG         2

//-------------------------------------------------------------------

/*******************************************************************\
| Basic token manipulation functions                                |
\*******************************************************************/

/*
 * Function name : m_add_token
 * Description   : Adds a token as per the arguments.
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_add_token (string sName, int iLocation, string sDescShort, string sDescLong)
{
  M_ACCESS_MONK_TOKENS;

  // Note that the order of items in the structure must
  // correspond with the constants defined in the
  // include file.

  if (member_array (sName, m_indices (mMonkTokens)) >= 0)
  {
    // The token already exists, change the entry.

    mMonkTokens [sName] = ({ iLocation, sDescShort, sDescLong });
  }
  else
  {
    // The token does not exist yet, create a new entry.

    mMonkTokens += ([ sName : ({ iLocation, sDescShort, sDescLong }) ]);
  }

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_remove_token
 * Description   : Removes a token as per the arguments.
 * Returns       : Zero as an indication of success or an error message
 *
 */

mixed m_remove_token (string sName)
{
  M_ACCESS_MONK_TOKENS;

  if (member_array (sName, m_indices (mMonkTokens)) < 0)
    return ("A token of this councillor does not exist.\n");

  M_DELETE_MONK_TOKENS (sName);

  M_SAVE_ACCESSED;
  return (FALSE);
}


/*
 * Function name : m_get_token_location
 *
 */

int m_get_token_location (string sName)
{
  M_ACCESS_MONK_TOKENS;

  if (member_array (sName, m_indices (mMonkTokens)) >= 0)
  {
    return (mMonkTokens [sName][M_MONK_TOKENS_LOCATION]);
  }
  else return (0);
}


/*
 * Function name : m_get_token_desc_short
 *
 */

string m_get_token_desc_short (string sName)
{
  M_ACCESS_MONK_TOKENS;

  if (member_array (sName, m_indices (mMonkTokens)) >= 0)
  {
    return (mMonkTokens [sName][M_MONK_TOKENS_DESC_SHORT]);
  }
  else return (NULL);
}


/*
 * Function name : m_get_token_desc_long
 *
 */

string m_get_token_desc_long (string sName)
{
  M_ACCESS_MONK_TOKENS;

  if (member_array (sName, m_indices (mMonkTokens)) >= 0)
  {
    return (mMonkTokens [sName][M_MONK_TOKENS_DESC_LONG]);
  }
  else return (NULL);
}

//-------------------------------------------------------------------

