inherit "/std/room";

#include "temple.h"

static void create_board();

create_room()
{
	object board;
    
	set_short("Board room in the Temple of Tyr");
	set_long(BSS("You have entered the inner sanctum of the "+
		"Temple of Tyr. Here there is a board used to post news about "+
		"Tyr, and to ask and answer questions.\n"));
    
	add_exit(TEMP_D+"entrance","west",0);
    

    reset_room();
}

reset_room()
{
    if (!present("board", TO))
        create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
	     board->set_board_name(TEMP_D+"temple_board");
        board->set_num_notes(30);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_lvl(15);
        board->set_remove_str("Sorry, mortals are not allowed to remove notes.")
;
	     board->set_err_log(TEMP_D+"board_err");
        board->move(TO);
    }
    return 0;
}
