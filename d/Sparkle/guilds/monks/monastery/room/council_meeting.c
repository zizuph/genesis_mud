/*******************************************************************\
| COUNCIL_MEETING.C                                                 |
\*******************************************************************/

/*
 * 04/08/15 Arandir     Added the missing inside property
 * 03/10/06 Arandir     Fixed a typo
 * 03/04/25 Arandir     Polished up
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 01/09/18 Manat	Moved the table and logbook
 * 00/12/26 Manat	Fixed few things about sitting down
 * 98/06/14 Cirion	Created
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

private object oTable;
private object oBook;

//-------------------------------------------------------------------

void m_council_sit (object oWho)
{
  object oRoom = this_object ();

  if ((environment(oWho) == oRoom) &&
      !(oWho->query_prop (M_PROP_TMP_I_SITTING)))
  {
    oWho->catch_tell ("You take your seat at the small table.\n");
    tell_room (oRoom, QCTNAME (oWho) + " sits down " +
               "in one of the chairs around the small " +
               "table.\n", oWho);
    oWho->add_prop (M_PROP_TMP_I_SITTING, TRUE);
  }
}

int m_council_leave (void)
{
  object oRoom = this_object ();
  object oMe = this_player ();

  if (oMe->query_prop (M_PROP_TMP_I_SITTING))
  {
    oMe->catch_tell ("You rise from your seat.\n");
    tell_room (oRoom, QCTNAME (oMe) + " rises from " +
               QPOS (oMe) + " seat.\n", oMe);
    oMe->remove_prop (M_PROP_TMP_I_SITTING);
  }

  return (FALSE);
}

void enter_inv (object oWho, object oFrom)
{
  ::enter_inv (oWho, oFrom);

  if (m_is_council_member (oWho))
  {
    set_alarm (1.0, 0.0, &m_council_sit (oWho));
  }
}

//-------------------------------------------------------------------

void create_room ()
{
  oTable = dg_clone_here (M_PATH_OBJ + "/council_table");
  oBook = clone_object (M_PATH_OBJ + "/council_tome");
  oBook->move (oTable, MOVE_SUBLOC_ALWAYS);

  set_short ("council meeting room");
  set_long ("This is a quiet, private location for council " +
            "members only. Three comfortable wooden chairs " +
            "are arranged around a small round hardwood table. " +
            "The room is lit by a single blue candle kept burning " +
            "in a depression in the center of the table.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_item (({ "candle", "light" }),
            "It is a wide, blue stump candle that sits in the " +
            "center of the table and burns with a bluish grey " +
            "light that casts soft shadows on the walls.\n");

  add_exit ("council", "north", &m_council_leave ());

  dg_add_entrance ("north", "You enter the council meeting room.");
}

//-------------------------------------------------------------------

/*
 * Function name : prevent_enter
 * Description   : Check to see if the interactive trying
 *                 to gain access to this room is
 *                 authorized.
 *
 */

int prevent_enter (object oWho)
{
  if (living (oWho) &&
      !m_is_council_member (oWho) &&
      !m_is_authorized_wizard (oWho))
  {
    oWho->catch_tell ("You may not enter there.\n");

    // Log wizards trying to snoop on the council debates.

    if (dg_is_wizard (oWho))
    {
      s_log (M_LOG_WIZARD,
             capitalize (dg_get_name (oWho)) + " tried to enter " + MASTER + ".");
    }

    return (TRUE);
  }
  return (FALSE);
}

/*
 * Function name : query_prevent_snoop
 * Description   : Wizards should not snoop on council affairs.
 *
 */

int query_prevent_snoop ()
{
  return (TRUE);
}

//-------------------------------------------------------------------

