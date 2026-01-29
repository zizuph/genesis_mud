inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
 
void
create_ctower_room()
{
  set_short("Stairwell");
 
  set_long( "This is a circular stairwell that goes up as "+
      "well as down.  Due to the nature of the lighting it is impossible "+
      "to tell how far the stairs extend in either direction.\n" );
 
  add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
      "milky crystal that is cold to the touch.\n");
 
  add_item(({"stairs"}), "You still can't tell how far the stairs go.\n");

  add_exit(CTOWER_ROOM + "stair2", "up", 0, 4);
  add_exit(CTOWER_ROOM + "stair5", "down", "@@walk_down@@", 3);
  add_exit(CTOWER_ROOM_MAZE + "maze1", "south");

}

int walk_down()
{
  this_player()->add_prop("_live_i_walked_down", 1);

  return 0;
}
