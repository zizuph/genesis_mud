#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

object woman;

void reset_room()
{
/*
  if(!objectp(woman))
  {
    seteuid(getuid());
    woman = clone_object(RHUN_DIR + "npc/naga");
    woman->move(TO, 1);
  }
*/
}

void create_room()
{
  object board;

  set_short("Board room");
  set_long("This is the public board of this"
	 + " large town in Rhun.  Anyone is free to post here."
	 + "  You may head back out onto the street to the east,"
	 + " or approach the common board area.\n");

  add_exit(RHUN_DIR + "ltown_ne/bldgs/com_board", "common", 0);
  add_exit(RHUN_DIR + "ltown_ne/streets/st5", "east", 0);

  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

  seteuid(getuid());
  board = clone_object("/d/Rhovanion/lib/board");
  board->set_board_name(RHUN_DIR + "rhun_board");
  board->set_num_notes(30);
  board->move(TO);

  reset_room();
}

