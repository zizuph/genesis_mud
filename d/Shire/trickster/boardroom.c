/* The Trickster board and start room */
/* Dunstable March 23, 1995     */
/* Split into 2 room so that the board will be more user friendly */
/* The is the Trickster bulletin board half of the old file */
/* Igneous Feb. 21, 1996     */


#pragma save_binary

inherit "/d/Shire/room";
#include "trickster.h"
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>

void reset_room();
static void create_board();

void
create_room()
{
   object board;
   
   set_short("Discussion board room");
   set_long("This moist, poorly lit room is where fellow " +
      "Tricksters come from all over the land to discuss their " +
      "ideas and share some of the mischeivous pranks which they have " +
      "played on some poor soul.  The main feature of the room would " +
      "have to be the bulletin board, though, if you are indeed able to read.  " +
      "You can leave this room by either going northest, through a medium-" +
      "sized hole or head west towards a dim, dark room.\n");
   
   add_exit(TRICK_DIR + "train","northeast",0,1);
   add_exit(TRICK_DIR + "start","west",0,1);
   add_prop(ROOM_I_INSIDE,1);
   
   reset_room();
}

void
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
      board->set_board_name("/d/Shire/trickster/newboard");
      board->set_num_notes(30);
      board->set_silent(1);
      board->set_show_lvl(0);
      board->set_remove_rank(WIZ_NORMAL);
      board->set_remove_str("Sorry, mortals are not allowed to remove notes.\n");
      board->move(TO);
   }
   return 0;
}
