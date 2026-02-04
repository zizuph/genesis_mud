#pragma save_binary

inherit "/std/board.c";

create_board()
{
	set_short("The Minstrel Board");
	set_board_name("/d/Terel/cedric/guild/board");
	set_num_notes(30);
	set_anonymous(1);
	set_silent(0);
	set_show_lvl(0);
	set_remove_lvl(1);
	set_remove_str("Sorry, you can't do that.");
}