#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit TANTALLON_INSIDE;

#define other_room TDIR + "hole2"

create_tantallon_room()
{
    set_short("Inside a secret room in the tunnel.");
    set_long("You are inside a hidden room in the small tunnel. "+
             "It is a little damp down here, and the cold stones "+
             "makes you shiver a little.\n");

    add_item(({"walls", "wall"}),
	 "The wall is rough and cold. This is no natural cave.\n" +
         "There is something suspicious about the east wall.\n");

    add_exit(TDIR + "torture_room2", "northwest", 0);
    add_exit(TDIR + "torture_room3", "southwest", 0);
}


void remove_door(object me)
{
  tell_room(me, "The door in the west wall closes!\n");
  tell_room(other_room, "The door in the east wall closes!\n");
  me->remove_exit("east");
  find_object(other_room)->remove_exit("west");
}

int
search(string str)
{
  if(str != "east wall")
  {
    return 0;
  }
  this_player()->catch_tell("A secret door opens in the east wall!\n");
  find_object(other_room)->add_exit(TDIR+"torture_room", "west", 0, 0);
  add_exit(other_room, "east", 0, 0);
  set_alarm(5.0, 0.0, &remove_door(this_object()));
  return 1;
}

public void
init()
{
  ::init();
  add_action(search, "search");
}
