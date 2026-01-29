/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

#define other_room TDIR + "torture_room"

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are down a hole. The walls are rough stone and it's cold. Not " +
	"much to see actually. There is a small tunnel going south. Light " +
	"comes here from the hole in the ceiling." +
	"", SL));

    add_item(({"walls", "wall"}),
	 "The wall is rough and cold. This is no natural cave.\n" +
         "There is something suspicious about the west wall.\n");

    add_exit(TDIR + "city2", "up", 0);
    add_exit(C_TUNNEL, "south", "@@block");

    door = clone_object(OBJ + "d_city2_b");
    door->move(TO);
    
    reset_room();
}

block()
{
    write("You feel this tunnel will lead somewhere under the temple.\n" +
	"But there is still some work to be done to it.\n");
    return 1;
}

reset_room()
{
    if (!present("gem", TO))
	clone_object(OBJ + "small_gem")->move(TO);
}



void remove_door(object me)
{
  tell_room(me, "The door in the west wall closes!\n");
  tell_room(other_room, "The door in the east wall closes!\n");
  me->remove_exit("west");
  find_object(other_room)->remove_exit("east");
}

int
search(string str)
{
  if(str != "west wall")
  {
    return 0;
  }
  this_player()->catch_tell("A secret door opens in the west wall!\n");
  add_exit(other_room, "west", 0, 0);
  find_object(other_room)->add_exit(TDIR+"hole2", "east", 0, 0);
  set_alarm(5.0, 0.0, &remove_door(this_object()));
  return 1;
}

public void
init()
{
  ::init();
  add_action(search, "search");
}
