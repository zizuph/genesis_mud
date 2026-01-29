/* This is the board in the knightroom,
* /d/Krynn/guilds/knights/guildhall/rooms/knightroom.c
 */

#include "../../local.h"
#include <std.h>

inherit "/std/board";


public void
create_board()
{
  set_board_name(VLOG + "kn_board_data");
  set_num_notes(100);
  set_silent(1);
  set_show_lvl(0);
  set_remove_rank(WIZ_MAGE);
  set_remove_str("Sorry, Only a Mage or higher may remove the notes");
}

int
allow_remove()
{
  /* Allow conclave to remove notes */
  if (TP->query_knight_sublevel() == 11)
    return 1;
  return 0;
}
