/*******************************************************************\
| BOARD.C                                                           |
\*******************************************************************/

/*
 * 06/02/21 Arandir     Created
 *
 */

#include <macros.h>

#include "defs.h"

inherit "/std/board";

//-------------------------------------------------------------------

/*
 * Function name : s_post_note
 * Description   : Posts a note on this board. Used for automated messages.
 *   sHeader       : Note header
 *   sAuthor       : Note poster
 *   sBody         : Note body
 * Returns       : Indication of success
 */

int s_post_note (string sHeader, string sAuthor, string sBody)
{
  object *aoClones;

  S_FIXUID;

  // Be careful to post the note on the clone, not on the master

  if (!IS_CLONE)
  {
    aoClones = object_clones (this_object ());
    if (sizeof (aoClones) > 0)
    {
      return (aoClones->s_post_note (sHeader, sAuthor, sBody));
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

