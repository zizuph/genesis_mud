inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"
object board;
string name;

create_room() {
  set_short("The Rhovanion Idearoom.");
  set_long(break_string("This is where the members of Rhovanion announce new ideas "
			+ "for things to implement in the domain, and to give feedback "
			+ "on others' ideas. \n", 70));
  
  add_exit("/d/Rhovanion/workroom","west");
  add_prop(ROOM_I_INSIDE, 1);
  
  if (!present("board",this_object())) {
    board = clone_object("/d/Rhovanion/common/boards/idea_board");
    name = "/d/Rhovanion/common/boards";
    if (file_size(name) != -2) mkdir(name);
    board->move(this_object());
  }
}

reset_room()
{
  tell_room(this_object(), "The room shivers.\n");
}

