/*******************************************************************\
| COUNCIL.C                                                         |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 00/12/26 Manat	Fixed few typos
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up and bugfixed
 * 03/10/06 Arandir     Fixed a typo
 * 04/01/28 Arandir     Fixed a typo
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;
inherit M_VOTING_LIBS;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("council chamber");
  set_long ("This is a small, windowless room with three small " +
            "desks against each of the north, east, and south walls. " +
            "On each of the desks lies a blue tallow candle, which, " +
            "aside from the dim light that passes through the " +
            "red curtain to the west, offers the only light in " +
            "the room. A wide doorway in the north wall leads into " +
            "a small room, and an oak-framed arch leads down a small " +
            "hall to a dimly-lit room to the south.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("council_post", "north");
  add_exit ("council_meeting", "south");
  add_exit ("meeting", "west");

  dg_add_entrance ("west", "You walk through the curtain into the small, dimly lit council room.");

  add_item (({ "desk", "desks" }),
            "Which one ? Perhaps you should specify which wall " +
            "the desk you want to examine is on.\n");
  add_item (({ "north desk", "north wall" }),
            "On the north wall is desk much like the others, very " +
            "plain and simple. It is made of pine that has many " +
            "layers of beeswax rubbed in, giving the surface a " +
            "soft sheen that sets the wood aglow in the mellow " +
            "candlelight. A blue candle rests atop the desk.\n");
  add_item (({ "south desk", "south wall" }),
            "The desk on the south wall is much like the others, being " +
            "plain and simple. It is made of pine that has many " +
            "layers of beeswax rubbed in, giving the surface a " +
            "soft sheen that sets the wood aglow in the mellow " +
            "candlelight. A blue candle rests atop the desk.\n");
  add_item (({ "east desk", "east wall" }),
            "On the east wall, opposite the red curtain, is a desk " +
            "of simple construction. It is made of pine with many " +
            "layers of beeswax rubbed in, giving the surface a " +
            "soft sheen that sets the wood aglow in the mellow " +
            "candlelight. A blue candle rests atop the desk.\n");
  add_item (({ "candle", "blue candle", "candles", "blue candles" }),
            "There are three blue candles in this room. Each one " +
            "burns with a small yellow flame that casts a wavering " +
            "light along the stone walls.\n");

  add_cmd_item (({ "candle", "blue candle" }),
                ({ "light" }),
                "It is already lit.\n");
  add_cmd_item (({ "candle", "blue candle" }),
                ({ "extinguish" }),
                "Try as you might to extinguish the candle, its flame " +
                "seems to actively resist your attempts.\n");

  dg_clone_here (M_OBJ_BOARD_COUNCIL);
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();
  m_voting_hook_init ();
}


void enter_inv (object oWho, object oFrom)
{
  ::enter_inv (oWho, oFrom);
  m_voting_hook_enter_inv (oWho, oFrom);
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
      !m_is_elder_member (oWho) &&
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

