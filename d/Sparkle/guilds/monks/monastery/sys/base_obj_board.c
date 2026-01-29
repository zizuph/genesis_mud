/*******************************************************************\
| BASE_OBJ_BOARD.C                                                  |
\*******************************************************************/

/*
 * 03/06/10 Arandir     Factored from the original boards
 *
 */

#include <macros.h>

#include "../defs.h"

inherit "/std/board";

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : m_post_note
 * Description   : Posts a note on this board. Used for automated messages.
 *   sHeader       : Note header
 *   sAuthor       : Note poster
 *   sBody         : Note body
 * Returns       : Indication of success
 */

int m_post_note (string sHeader, string sAuthor, string sBody)
{
  object *aoClones;

  DG_FIXUID;

  // Be careful to post the note on the clone, not on the master

  if (!IS_CLONE)
  {
    aoClones = object_clones (this_object ());
    if (sizeof (aoClones) > 0)
    {
      return (aoClones->m_post_note (sHeader, sAuthor, sBody));
    }
    else
    {
      return (FALSE);
    }
  }
  else
  {
    create_note (sHeader, sAuthor, sBody);
    return (TRUE);
  }
}

//-------------------------------------------------------------------

