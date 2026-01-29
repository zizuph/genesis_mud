#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Common board room");
  set_long("This shadowy room seems to have no walls,"
	+" no floor, and no ceiling.  It is the room of the common board,"
	+" an insubstantial and mist-like creation, woven & drawn"
	+" from the fabric of time and space.  You sense that you may"
	+" somehow travel <back> to the"
	+" room from whence you came.\n");

  add_exit(RHUN_DIR+"ltown_ne/bldgs/boardroom","back",0);

  seteuid(getuid());
  clone_object("/d/Genesis/obj/board")->move(TO,1);
}
