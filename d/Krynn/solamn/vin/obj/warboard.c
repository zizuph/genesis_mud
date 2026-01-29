/* Board for discussing the war */

#include "../local.h"
#include <std.h>

inherit "/std/board";


void
create_board()
{
  set_board_name(VLOG + "war_board_data");
  set_num_notes(75);
  set_silent(0);
  set_show_lvl(0);
  set_remove_rank(WIZ_NORMAL);
  set_remove_str("Sorry, only a wizard may remove the notes.\n");
}

int
allow_remove()
{
  /* Allow conclave to remove notes */
  if (TP->query_knight_sublevel() == 11)
    return 1;
  return 0;
}
