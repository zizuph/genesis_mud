/*******************************************************************\
| BOARD_RECODE.C                                                    |
\*******************************************************************/

#include <std.h>
#include <macros.h>

#include "../defs.h"

inherit M_OBJ_BOARD_BASE;

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

void create_board ()
{
    set_board_name (M_PATH_BOARD_RECODE);
    set_num_notes (80);
    set_silent (1);
    set_show_lvl (0);
    set_keep_discarded (1);
    set_remove_str ("Only monk council members, guildmasters and " +
                    "archwizards may remove notes from this board.\n");

    set_name ("board");
    set_adj (({ "message" }));
    set_short ("message board");
    set_long ("This is the message board for the monks to discuss the "
        + "future recode of the guild.\n");
}

//-------------------------------------------------------------------

int block_access ()
{
  object oHim = this_player ();

  if (m_is_monk (oHim) ||
      dg_is_wizard (oHim))
  {
    return (FALSE);
  }
  else
  {
    write ("You are not authorized to access notes on this board.\n");
    return (TRUE);
  }
}

int block_reader () { return (block_access ()); }
int block_writer () { return (block_access ()); }


int allow_remove ()
{
  object oHim = this_player ();

  return (m_is_council_member (oHim) ||
          m_is_authorized_wizard (oHim) ||
          dg_is_wizard (oHim, WIZ_ARCH));
}

//-------------------------------------------------------------------

