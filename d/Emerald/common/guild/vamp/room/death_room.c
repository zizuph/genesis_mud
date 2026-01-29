inherit "/std/room";

#include "room.h"
#include <stdproperties.h>

void create_room()
{
  set_short("oblivion");
  set_long("You can see nothing.\n");
  add_prop(ROOM_I_INSIDE, 1);
  add_prop("_room_s_light_desc", "");
  add_prop(ROOM_M_NO_TELEPORT, 1);
}

int catch_all(string str)
{
  string cmd = query_verb();

  switch (cmd)
  {
    case "praise":
    case "commune":
    case "bug":
    case "typo":
    case "quit":
    case "reply":
    case "idea":
    case "help":
    case "sysbug":
      return 0;
    default: 
      return 1;
  }
}

void init()
{
  if (!IS_WIZ(TP))
  {
    add_action(catch_all, "", 1);
  }

  ::init();
}
