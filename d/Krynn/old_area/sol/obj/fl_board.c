/* created by Aridor 01/31/94 */
/* copy of the flame board of Palanthas, 
 * but without writing access :)  */

inherit "/std/board";
#define FLAME_BOARD_DIR     "/d/Krynn/solamn/palan/log/"
#include "/d/Krynn/common/defs.h"

void
create_board()
{
    set_board_name(FLAME_BOARD_DIR + "board_data");
    set_short("flame board");
    set_num_notes(20);
    set_silent(1);
    set_show_lvl(0);
    set_remove_lvl(35);
    set_remove_str("Sorry, Only a Lord may remove the notes");
    set_err_log(FLAME_BOARD_DIR + "board_error");
}

int
check_writer()
{
    if (E(TP) == E(TO))
      {
	  write("You try to get hold of the board to write on it, but you " +
		"realize quickly that this is just an image of a board and " +
		"not a real one, providing no means to write. You can go to " +
		"the original board in Palanthas, though, and write there.\n");
	  return 1;
      }
    return 0;
}


int
check_reader()
{
    load_headers();
    return ::check_reader();
}
