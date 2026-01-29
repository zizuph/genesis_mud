/* created by Aridor 01/31/94 */
/* the Solace City board
 * but with limited writing access :)  */

inherit "/std/board";
#define C_BOARD_DIR     "/d/Krynn/solamn/hctower/spur/log/"
#include "../local.h"
#include <macros.h>
#include <std.h>

void
create_board()
{
  set_board_name(C_BOARD_DIR + "board_data");
  set_num_notes(50);
  set_silent(0);
  set_show_lvl(0);
  set_remove_rank(WIZ_LORD);
  set_remove_str("Sorry, Only a Liege may remove the notes.\n");
  set_no_report(1);
}

int
block_writer()
{
  if (TP->query_wiz_level())
    return 0;
  if ((TP->query_knight_sublevel() != 11))
    {
      write("Only members of the Conclave may post notes to this " +
            "board. You will need to find another place to post.\n");
      return 1;
    }
  return 0;
}

int 
block_reader()
{
  if (TP->query_wiz_level())
    return 0;
  if (!(MEMBER(TP) || LAYMAN(TP)))
    {
      write("The notes on this board appear to be written " +
            "in a language you cannot understand.\n");
      return 1;
    }
  return 0;
}

int
allow_remove()
{
  if (TP->query_knight_sublevel() == 11)
    return 1;
  return 0;
}
