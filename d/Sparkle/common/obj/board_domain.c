/*******************************************************************\
| BOARD_DOMAIN.C                                                    |
|                                                                   |
| Note: The board contains update messages of files that have been  |
|       updated in the Sparkle domain. If you wish to have the      |
|       logger ignore files in a certain directory, just add it to  |
|       /d/Sparkle/var/update_ignore.o. The code for the update     |
|       logging is in /d/Sparkle/lib/libs_development.c             |
\*******************************************************************/

/*
 * 06/02/21 Arandir     Created
 *
 */

#include <std.h>
#include <macros.h>

#include "defs.h"

inherit S_BASE_BOARD;

inherit S_LIB_PLAYER;

//-------------------------------------------------------------------

void create_board ()
{
  set_board_name (S_DOMAIN_BOARD_DIR);
  set_num_notes (100);
  set_silent (1);
  set_show_lvl (0);
  set_keep_discarded (0);
  set_remove_str ("Only archwizards may remove notes from this board.\n");

  set_name ("board");
  set_adj (({ "message" }));
  add_adj (({ "private" }));
  set_short ("message board");
  set_long ("It is the message board for the domain. This is " +
            "where notes of interest for the domain may " +
            "be written and read.\n");
}

//-------------------------------------------------------------------

int block_access ()
{
  if (s_is_wizard (TP))
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
  return (s_is_wizard (TP, WIZ_ARCH));
}

//-------------------------------------------------------------------

