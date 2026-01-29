#pragma strict_types
#include "defs.h"
inherit "/std/workroom";

void
create_workroom()
{
  ::create_workroom();
  
    set_short("a darkened dungeon");
    set_long("This is a darkened dungeon with sparse light emanating "+
      "from torches and candles that have been placed firmly on holders "+
      "attached to the walls. There are chains placed along the walls "+
      "in various positions, styles and lengths. The floor is made "+
      "from a smooth darkened stone with reddened stains in various "+
      "places. There is a large fire placed in a pit in the center of "+
      "the room.\n");
}

object
load_board()
{
    object bb;
    string *file;
    string name;

    file = explode(MASTER + "/", "/");
    file = slice_array(file, 0, sizeof(file) - 2);

    seteuid(getuid());
    bb = clone_object("/d/" + creator(this_object()) + "/board");

    name = implode(file, "/") + "/private";
    if (file_size(name) != -2) 
        mkdir(name);

    bb->set_board_name(name + "/domain_board");
    bb->set_num_notes(50);
    bb->set_silent(0);
    bb->move(this_object());

    return bb;
}
