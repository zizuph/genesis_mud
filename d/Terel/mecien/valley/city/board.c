inherit "std/board.c";

#include <std.h>

public void
create_board(){
 seteuid(getuid(this_object()));
 add_name("board");
add_name("scroll");
  set_board_name("/d/Terel/mecien/valley/city/board");
 set_num_notes(30);
 set_silent(0);
 set_show_lvl(0);
 set_remove_rank(WIZ_NORMAL);
 set_remove_str("You have no such power.\n");
}
