/* This is the board in the knightroom,
  * Actually, the board for squire applicants in the new VK
  * Teth and Morrigan Jan 11 97
 */

#include "../../local.h"
#include <std.h>

inherit "/std/board";

#ifndef ADMIN
#define ADMIN	(KADM + "admin.c")
#endif

void
create_board()
{
  set_board_name(VLOG + "sq_board_data");
  set_num_notes(35);
  set_silent(0);
  set_show_lvl(0);
  set_remove_rank(WIZ_NORMAL);
  set_remove_str("Sorry, only a wizard may remove the notes.\n");
   set_no_report(1);
}

int
allow_remove()
{
  /* Allow conclave to remove notes */
  if (TP->query_knight_sublevel() == 11)
    return 1;

  if ((ADMIN)->query_knight_team("interview", TP->query_real_name()))
    return 1;

  return 0;
}
