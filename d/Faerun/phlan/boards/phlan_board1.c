/* /d/Faerun/phlan/boards/phlan_board1.c
 *
 *
 * Nerull, 2021
 *
 */

#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/board";

public void
create_board()
{
    set_board_name(BOARDS_DIR + "phlan_board1_notes");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("wooden discussion board");
    set_long("This is a wooden discussion board. It is set firmly " 
        +"in the center of the room. Trainees "
        +"may use this board to discuss tactics and various "
        +"other topics relevant for their day to day duty "
        +"and operations.\n");
}
