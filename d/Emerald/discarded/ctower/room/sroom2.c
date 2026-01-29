inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
#include <stdproperties.h> 

void
create_ctower_room()
{
  set_short("Secret room");
 
  set_long( "This room glows softly, but the most noticable feature "+
      "is the gaping pit in the center of the room.\n" );
 
  add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
      "milky crystal that is cold to the touch.\n");
 
  add_item(({"pit", "hole"}), ( "The pit is rather deep and made of " +
      "crystal.  The way doesn't look finished yet though.\n" ));
 
  add_exit(CTOWER_ROOM + "room1", "east");
  add_exit("", "down", "@@block@@");

}
 
block()
{
  write("A crystal formation blocks your way.\n");
  return 1;
}

void leave_inv(object ob, object to)
{
  object room;

  ::leave_inv(ob, to);

  if (!sizeof(filter(all_inventory(), interactive)) &&
      (room = find_object(CTOWER_ROOM + "room1")))
  {
    set_alarm(1.0, 0.0, &room->close_fireplace());
  }
}
