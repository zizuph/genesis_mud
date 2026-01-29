inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

object board;
string name,longtxt;

create_room()
{
  set_short("This is the idearoom of the domain Gondor");
  set_long("@@long_func");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/workroom","west");
  if (!present("board",this_object()))
  {
    board = clone_object(BOARD_DIR + "idea_board");
    board->move(TO);
  }
}

long_func()
{
  longtxt = "The Gondor Idearoom.\n"+
  "This is where members of Gondor announce new ideas for things to\n"+
  "implement in the domain, and to give feedback on the others' ideas.\n"+
  "There is a bulletin board here for this use. West is the meetingroom.\n";
  return longtxt;
}

query_prevent_snoop() { return 1; }
