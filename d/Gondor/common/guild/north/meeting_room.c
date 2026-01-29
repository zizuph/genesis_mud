#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void add_stuff();

object board, jar;
string name;

public void
create_room()
{
    set_short("The meeting room of the Rangers of the North");
    set_long(BSN("You have entered the meeting room. There is a table in "+
   "the centre of the room. Around the table are high-backed chairs. "+
    "In this room plans are made and discussions held. One "+
    "doorway opens to the north, where many dusty shelves can be "+
    "seen, and another doorway leads back west to a pleasant room."));

    add_item(({ "chairs", "high-backed chairs", "table", "furniture" }),
    "The furniture is finely carved with leaves and woodland animals.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(RANGER_NORTH_DIR+"song_room","west",0,0);
    add_exit(RANGER_NORTH_DIR + "nrlibrary", "north", 0, 0);

    if (!present("board",TO))
      {
          board = clone_object("/std/board");
          name = "/d/Gondor/common/guild/north/boards";
          if (file_size(name) != -2)  mkdir(name);
          board->set_board_name(name + "/public");
          board->set_num_notes(40);
          board->set_silent(0);
          board->set_show_lvl(0);
          board->set_remove_rank(WIZ_NORMAL);
          board->set_remove_str("The note is stuck, you can't do that.");
          board->move(TO);
      } 
    add_stuff();  
}

public void
add_stuff()
{
    if (!objectp(jar))
    {
        jar = clone_object(RANGER_DIR + "obj/herbjar");
        jar->add_prop(OBJ_M_NO_GET, "The jar seems to be stuck to the floor!\n");
        jar->move(TO);
    }
}
