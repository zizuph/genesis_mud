/*
   steed_office.c

   aBoard / discussion room for the steeds

   Fysix, March 1997

 */
#include "/d/Gondor/defs.h"
#include <std.h>

inherit "/std/room";

#define MY_BOARD BOARD_DIR + "steed"

void
create_room()
{
object board;

   set_short("Steed board / discussion room");
   set_long("This is steed board and discussion room. " +
    "Coding steeds is very nasty and it needs a lot of " +
    "thinking and people to work along with it. " +
    "\n");

   add_exit("/d/Gondor/workroom", "gondor");

    if (!present("board",this_object()))
    {
	board = clone_object("/std/board");
   board->set_board_name(MY_BOARD);
	board->set_num_notes(30);
	board->set_silent(0);
	board->set_show_lvl(1);
	board->set_remove_rank(WIZ_NORMAL);
	board->set_remove_str("Nope, you cannot remove that note.");
	board->move(this_object());
    }
}
