/* This is the board in the boardroom,
 * modified by Teth, Dec 7 1996, for new VK (in board_office.)
 */

#include "../local.h"
#include <std.h>

inherit "/std/board";

public void
create_board()
{
    set_board_name(VLOG + "off_board_data");
    set_num_notes(25);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("Sorry, only certain wizards may remove notes.\n");
}

int
allow_remove()
{
  /* Allow conclave to remove notes */
  if (TP->query_knight_sublevel() == 11)
    return 1;
  return 0;
}
