/*
    This is the club board of the Prestigious Knights' Club
    Only clubmembers are allowed to write here, everyone can read.
*/

inherit  "/std/board";

#include "clubdefs.h"
#include <macros.h>
#include <std.h>
#define PATH    CLUB + "board_data"


create_board()
{
  set_long("This is the bulletin board of the Prestigious Knights' Club. " +
	   "It is intended for the use among members, and to keep non-" +
	   "members informed.\n");
   set_board_name(PATH);
   set_num_notes(15);
  //set_err_log(CLUB + "boarderrors");
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_LORD);
   set_remove_str("You can't remove anything here.");
   //set_fuse(1);

}


int
block_writer()
{    
    if (TP->query_wiz_level() || IS_CLUB_MEMBER(TP))
      return 0;
    if (present(TP,E(TO)))
      {
	write("You are not allowed to write here.\n");
	say(QCTNAME(TP) + " tries to write a note but fails.\n");
      }
    return 1;
}

/* i don't think we need this anymore...
int
allow_remove()
{
    if (TP->query_wiz_level() || IS_CLUB_MEMBER(TP))
      return 0;
    if (present(TP,E(TO)))
      {
	write("You are not allowed to remove notes here.\n");
	say(QCTNAME(TP) + " tried to remove a note but failed.\n");
      }
    return 1;
}
*/
