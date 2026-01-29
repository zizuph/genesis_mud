inherit "/d/Shire/room";
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
object board;
string name;

void create_room()
{
  set_short("The Middle-Earth discussion room");
  set_long("This room is an expansive one, with plenty of room for "+
   "all who want to discuss the works of J.R.R. Tolkien.  Upon the northern "+
   "wall is a painting of the sun rising over Tol Eressea.  In the center of "+
   "the room is a bulletin board, lit from above by a very bright jewel. East "+
   "is the Shire domain room.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_exit(SHIRE_DIR + "workroom","east");
  if (!present("board",this_object())) {
    board = clone_object("/std/board");
    name = "/d/Shire/boards/";
    if (file_size(name) != -2)
         mkdir(name);
      board->set_board_name(name + "mediscuss");
      board->set_num_notes(50);
      board->set_silent(0);
      board->set_show_lvl(1);
      board->set_remove_lvl(15);
      board->set_remove_str("The note sticks to the board.");
      board->move(this_object());
    }
}

 
