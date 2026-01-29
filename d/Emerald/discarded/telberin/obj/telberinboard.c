/* This is the Royal Proclamations Board for the King of Telberin*/

inherit "std/board";
#include "/d/Emerald/defs.h"
#include <std.h>

void
create_board()
{
   set_board_name(TELBERIN_DIR+"telberin_board_data");
   set_num_notes(30);
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_NORMAL);
   set_remove_str("Sorry, you can't do that");
   set_short("Common Board of Telberin") ;
   set_long ("This well-made board has a wooden rim covered with "+
      "growing ivy.  It is intended for discussion of "+
      "all events associated with Telberin, by both citizens " +
      "and visitors.\n");
}

/*
int
check_writer()
{
   return 0;
}


*/
