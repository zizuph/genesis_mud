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
 
  add_exit(CTOWER_ROOM + "stair1", "up", "@@walk_up@@", 4);
  add_exit("@@exit_where@@", "down", "@@walk_down@@", 3);

}

string exit_where()
{
  return (this_player()->query_prop("_live_i_walked_down") >= 0 ? 
         CTOWER_ROOM + "room4" : CTOWER_ROOM + "stair1");
}

int walk_up()
{
  int down = this_player()->query_prop("_live_i_walked_down");

  this_player()->add_prop("_live_i_walked_down", --down);
  
  return 0;
}

int walk_down()
{
  int down = this_player()->query_prop("_live_i_walked_down");

  if (++down)
  {
    this_player()->add_prop("_live_i_walked_down", down);
  }
  else
  {
    this_player()->remove_prop("_live_i_walked_down");
  }

  return 0;
}
