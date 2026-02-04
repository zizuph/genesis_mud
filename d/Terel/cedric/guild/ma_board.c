#pragma save_binary

inherit "/std/board.c";

create_board()
{
   set_short("The Inner Board");
   set_board_name("/d/Terel/cedric/guild/ma_board");
   set_num_notes(50);
   set_no_report(1);
}