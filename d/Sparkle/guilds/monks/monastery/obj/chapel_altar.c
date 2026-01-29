/*******************************************************************\
| CHAPEL_ALTAR.C                                                    |
\*******************************************************************/

/*
 * 98/06/07 Cirion	Created
 * 03/05/17 Arandir	Ported to new area and bugfixed
 *
 */

#include <macros.h>
#include <language.h>

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

#define M_PROP_TMP_NO_SPAM      "_monk_tmp_no_altar"

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  set_name ("altar");
  set_adj (({ "simple", "wood", "hardwood", "wooden" }));

  set_short ("simple altar");
  set_long ("It is a simple altar, made from some dark " +
            "hardwood. Carved all along the altar's surface " +
            "are images of birds and dragons. The surface of " +
            "the altar is smooth and unadorned, save for " +
            "a small inscription carved delicately into the wood.\n");

  dg_set_description_prefix ("Upon a wide, semi-circular marble dais " +
                             "filling the western half of the room is " +
                             "a simple altar made from dark wood");
}

//-------------------------------------------------------------------

/*
 * Function name : m_remove_spam_block
 * Description   : Removes spam block set by prevent_leave.
 *
 */

void m_remove_spam_block (object oWho)
{
  oWho->remove_prop (M_PROP_TMP_NO_SPAM);
}

/*
 * Function name : prevent_leave
 * Description   : Called when an object is trying to leave this
 *                 container. We use this to prevent people other
 *                 than monks from removing things from the altar.
 *
 */

int prevent_leave (object oItem)
{
  object oHim = this_player ();

  if(!m_is_monk (oHim))
  {
    // We have to do this because trying to get multiple things
    // from the altar will result in a message for each one. To
    // prevent spam, we only send one message per command.

    if (!oHim->query_prop (M_PROP_TMP_NO_SPAM))
    {
      write ("As you reach out for the altar, the room suddenly " +
             "seems to lurch and shift, and you find yourself " +
             "facing the opposite direction.\n");
      say (QCTNAME (oHim) + " reaches out for the " +
           "altar, but then suddenly lurches away and " +
           "stumbles around blindly.\n");
      oHim->add_prop (M_PROP_TMP_NO_SPAM, TRUE);
      set_alarm (0.0, 0.0, &m_remove_spam_block (oHim));
    }

    return (TRUE);
  }

  return (FALSE);
}

//-------------------------------------------------------------------

